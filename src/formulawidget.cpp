#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>

#include "formulawidget.hpp"


FormulaWidget::FormulaWidget(
  const QString &expression,
  const QList<Parameter> &params,
  QWidget *parent
)
  : QWidget(parent),
    m_formula(expression),
    m_args()
{
  QFormLayout *rootLayout;

  QLineEdit *paramField;
  QPushButton *calcButton;
  QLineEdit *resultField;

  rootLayout = new QFormLayout(this);

  for (auto param : params) {
    paramField = new QLineEdit("0");
    rootLayout->addRow(param.name, paramField);

    m_args.insert(param.id, 0.0);

    QObject::connect(
      paramField, &QLineEdit::editingFinished,
      this, [this, param, paramField]() {
        m_args[param.id] = paramField->text().toDouble();
      }
    );
  }

  calcButton = new QPushButton("Calculate");

  resultField = new QLineEdit("0");
  resultField->setDisabled(true);

  rootLayout->addRow(calcButton);
  rootLayout->addRow(resultField);

  QObject::connect(
    calcButton, &QPushButton::clicked,
    this, [this, resultField]() {
      resultField->setText(QString::number(
        m_formula.calculate(m_args)
      ));
    }
  );
}
