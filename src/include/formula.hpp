#ifndef FORMULA_HPP_INCLUDED_
#define FORMULA_HPP_INCLUDED_


#include <functional>

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QPair>


class Formula {
  public:
    Formula(const QString &expr);

    double calculate(const QMap<QString, double> &args);

  protected:
    const QString m_expr;

    using fn_t = std::function<double (double, double)>;

    static const QMap<QString, double> m_consts;
    static const QMap<QChar, QPair<quint8, fn_t>> m_ops;
};


#endif /* FORMULA_HPP_INCLUDED_ */
