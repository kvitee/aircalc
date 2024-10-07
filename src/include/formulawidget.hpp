#ifndef FORMULAWIDGET_HPP_INCLUDED_
#define FORMULAWIDGET_HPP_INCLUDED_


#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "formula.hpp"
#include "parameditwidget.hpp"


class FormulaWidget : public QWidget {
  Q_OBJECT

  public:
    FormulaWidget(
      const QString &expression,
      QWidget *parent = nullptr
    );

    FormulaWidget(
      const QString &expression,
      const QList<ParamEditWidget::Parameter> &params,
      QWidget *parent = nullptr
    );

    void addParam(const ParamEditWidget::Parameter &param);

  protected:
    QPushButton *m_calcButton;
    QLineEdit *m_resultField;

    Formula m_formula;
    QMap<QString, double> m_args;
};


#endif  /* FORMULAWIDGET_HPP_INCLUDED_ */ 
