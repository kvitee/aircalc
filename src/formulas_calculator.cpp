#include <QtCore/Qt>
#include <QtCore/QString>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>

#include <QtGui/QDoubleValidator>

#include "formulas_calculator.hpp"
#include "labeled_line_edit.hpp"


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

void FormulasCalculator::addParamField(const QString &id) {
  auto field = new LabeledLineEdit(
    QPixmap(QString("icons/icon_id.png").replace("icon_id", id))
  );
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
}

void FormulasCalculator::addResultField(const QString &id) {
  auto field = new LabeledLineEdit(
    QPixmap(QString("icons/icon_id.png").replace("icon_id", id))
  );

  field->lineEdit()->setReadOnly(true);
  field->setFocusPolicy(Qt::ClickFocus);

  m_resultsForm->layout()->addWidget(field);
}

void FormulasCalculator::calculate() {
}

void FormulasCalculator::composeWidgets() {
  m_paramsForm->setLayout(new QVBoxLayout());
  m_paramsForm->layout()->setAlignment(Qt::AlignTop);

  m_resultsForm->setLayout(new QVBoxLayout());
  m_resultsForm->layout()->setAlignment(Qt::AlignTop);

  m_splitter->addWidget(m_paramsForm);
  m_splitter->addWidget(m_resultsForm);
  m_splitter->setHandleWidth(5);

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
