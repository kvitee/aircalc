#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include "formulawidget.hpp"
#include "parameditwidget.hpp"


FormulaWidget::FormulaWidget(
  const QString &expression,
  QWidget *parent
)
  : QWidget(parent),
    m_resultField(new QLineEdit("0")),
    m_calcButton(new QPushButton("Рассчитать")),
    m_formula(expression),
    m_args()
{
  QVBoxLayout *rootLayout = new QVBoxLayout(this);
  rootLayout->setAlignment(Qt::AlignTop);
  rootLayout->setDirection(QBoxLayout::Up);

  m_resultField->setDisabled(true);

  rootLayout->addWidget(m_resultField);
  rootLayout->addWidget(m_calcButton);

  QObject::connect(
    m_calcButton, &QPushButton::clicked,
    this, [this]() {
      m_resultField->setText(QString::number(
        m_formula.calculate(m_args)
      ));
    }
  );
}

FormulaWidget::FormulaWidget(
  const QString &expression,
  const QList<ParamEditWidget::Parameter> &params,
  QWidget *parent
)
  : FormulaWidget(expression, parent)
{
  for (const auto &param : params) {
    addParam(param);
  }
}

void FormulaWidget::addParam(const ParamEditWidget::Parameter &param) {
  ParamEditWidget *paramEdit = new ParamEditWidget(param);
  static_cast<QHBoxLayout *>(layout())->insertWidget(2, paramEdit);

  m_args.insert(param.id, 0.0);

  QObject::connect(
    paramEdit, &ParamEditWidget::valueChanged,
    this, [this, param](double value) {
      m_args[param.id] = value;
    }
  );
}
