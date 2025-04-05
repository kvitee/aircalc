#ifndef FORMULAS_CALCULATOR_HPP_INCLUDED_
#define FORMULAS_CALCULATOR_HPP_INCLUDED_


#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QSet>
#include <QtCore/QMap>

#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QPushButton>

#include "QtCore/qset.h"
#include "formula.hpp"


class FormulasCalculator : public QWidget {
  Q_OBJECT

  public:
    FormulasCalculator(QWidget *parent = nullptr);

    void addFormula(const QString &expr);

    void addParamField(const QString &id);
    void addResultField(const QString &id);

  public slots:
    void calculate();

  signals:
    void calculated(const Formula &f);

  protected:
    QWidget *m_paramsForm;
    QWidget *m_resultsForm;

    QSplitter *m_splitter;
    QPushButton *m_calcButton;

    QMap<QString, double> m_args;
    QMap<QString, double> m_results;

    QSet<QString> m_params;
    QVector<Formula> m_formulas;

    void composeWidgets();
    void connectWidgets();
};


#endif  /* FORMULAS_CALCULATOR_HPP_INCLUDED_ */ 
