#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>

#include <QtGui/QDoubleValidator>

#include "formulas_calculator.hpp"
#include "labeled_line_edit.hpp"
#include "formula.hpp"


FormulasCalculator::FormulasCalculator(QWidget *parent)
  : QWidget(parent),
    m_paramsForm(new QWidget()),
    m_resultsForm(new QWidget()),
    m_splitter(new QSplitter()),
    m_calcButton(new QPushButton("Рассчитать"))
{
  composeWidgets();
  connectWidgets();
}

void FormulasCalculator::addFormula(const QString &expr) {
  auto formula = Formula(expr);

  if (!formula.isValid()) return;

  m_formulas.push_back(formula);
  addResultField(formula.id());

  for (auto paramId : formula.params()) {
    bool paramIsResult = false;
    for (const auto &f : m_formulas) {
      if (f.id() == paramId) {
        paramIsResult = true;
        break;
      }
    }

    if (paramIsResult) continue;

    addParamField(paramId);
  }
}

void FormulasCalculator::addParamField(const QString &id) {
  if (m_params.contains(id)) return;

  auto field = new LabeledLineEdit(
    QPixmap(QString(":/icons/icon_id.png").replace("icon_id", id))
  );

  field->lineEdit()->setClearButtonEnabled(true);
  field->lineEdit()->setValidator(new QDoubleValidator());

  m_paramsForm->layout()->addWidget(field);

  QObject::connect(
    field->lineEdit(), &QLineEdit::textChanged,
    this, [this, id](const QString &text) {
      bool ok;
      m_args[id] = QString(text).replace(',', '.').toDouble(&ok);

      if (!ok) {
        m_args.remove(id);
      }
    }
  );

  m_params.insert(id);
}

void FormulasCalculator::addResultField(const QString &id) {
  auto field = new LabeledLineEdit(
    QPixmap(QString(":/icons/icon_id.png").replace("icon_id", id))
  );

  field->lineEdit()->setReadOnly(true);
  field->setFocusPolicy(Qt::ClickFocus);

  QObject::connect(
    this, &FormulasCalculator::calculated,
    field, [this, field, id](const Formula &f) {
      if (id != f.id()) return;

      if (m_results.contains(id)) {
        field->lineEdit()->setText(QString::number(m_results[id]));
        field->lineEdit()->setEnabled(true);
      } else {
        field->lineEdit()->clear();
        field->lineEdit()->setEnabled(false);
      }
    }
  );

  m_resultsForm->layout()->addWidget(field);
}

void FormulasCalculator::calculate() {
  for (auto f : m_formulas) {
    bool paramsEnough = true;
    for (auto p : f.params()) {
      if (!m_args.contains(p)) {
        paramsEnough = false;
        break;
      }
    }

    if (paramsEnough) {
      double result = f.calculate(m_args);

      m_results[f.id()] = result;
      m_args[f.id()] = result;
    } else {
      m_results.remove(f.id());
      m_args.remove(f.id());
    }

    emit calculated(f);
  }
}

void FormulasCalculator::composeWidgets() {
  m_paramsForm->setLayout(new QVBoxLayout());
  m_paramsForm->layout()->setAlignment(Qt::AlignTop);

  m_resultsForm->setLayout(new QVBoxLayout());
  m_resultsForm->layout()->setAlignment(Qt::AlignTop);

  m_splitter->addWidget(m_paramsForm);
  m_splitter->addWidget(m_resultsForm);

  setLayout(new QVBoxLayout());

  layout()->addWidget(m_splitter);
  layout()->addWidget(m_calcButton);
}

void FormulasCalculator::connectWidgets() {
  QObject::connect(
    m_calcButton, &QPushButton::clicked,
    this, &FormulasCalculator::calculate
  );
}
