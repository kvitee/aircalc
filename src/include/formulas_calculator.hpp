#ifndef FORMULAS_CALCULATOR_HPP_INCLUDED_
#define FORMULAS_CALCULATOR_HPP_INCLUDED_


#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QPushButton>


class FormulasCalculator : public QWidget {
  Q_OBJECT

  public:
    FormulasCalculator(QWidget *parent = nullptr);

    void addParamField(const QString &id);
    void addResultField(const QString &id);

  public slots:
    void calculate();

  protected:
    QWidget *m_paramsForm;
    QWidget *m_resultsForm;

    QSplitter *m_splitter;
    QPushButton *m_calcButton;

    QMap<QString, double> m_args;

    void composeWidgets();
    void connectWidgets();
};


#endif  /* FORMULAS_CALCULATOR_HPP_INCLUDED_ */ 
