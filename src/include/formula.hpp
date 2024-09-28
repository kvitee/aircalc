#ifndef FORMULA_HPP_INCLUDED_
#define FORMULA_HPP_INCLUDED_


#include <QtCore/QString>
#include <QtCore/QMap>


class Formula {
  public:
    Formula(const QString &expression);

    double calculate(const QMap<QString, double> &args);

  protected:
    const QString m_expression;
};


#endif /* FORMULA_HPP_INCLUDED_ */
