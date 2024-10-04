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
  const QList<ParamEditWidget::Parameter> &params,
  QWidget *parent
)
  : QWidget(parent),
    m_formula(expression),
    m_args()
{
  QVBoxLayout *rootLayout;

  ParamEditWidget *paramEdit;
  QPushButton *calcButton;
  QLineEdit *resultField;

  rootLayout = new QVBoxLayout(this);
  rootLayout->setAlignment(Qt::AlignTop);

  for (auto param : params) {
    paramEdit = new ParamEditWidget(param);
    rootLayout->addWidget(paramEdit);

    m_args.insert(param.id, 0.0);

    QObject::connect(
      paramEdit, &ParamEditWidget::valueChanged,
      this, [this, param](double value) {
        m_args[param.id] = value;
      }
    );
  }

  calcButton = new QPushButton("Рассчитать");

  resultField = new QLineEdit("0");
  resultField->setDisabled(true);

  rootLayout->addWidget(calcButton);
  rootLayout->addWidget(resultField);

  QObject::connect(
    calcButton, &QPushButton::clicked,
    this, [this, resultField]() {
      resultField->setText(QString::number(
        m_formula.calculate(m_args)
      ));
    }
  );
}
