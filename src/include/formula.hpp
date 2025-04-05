#ifndef FORMULA_HPP_INCLUDED_
#define FORMULA_HPP_INCLUDED_


#include <functional>

#include <QtCore/QtTypes>
#include <QtCore/QString>
#include <QtCore/QChar>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QPair>


class Formula {
  public:
    Formula(const QString &expr);

    bool isValid() const;

    qreal calculate(const QMap<QString, qreal> &args) const;

    const QString &id() const;
    const QString &expr() const;
    const QStringList &params() const;

  protected:
    QString m_id;
    QString m_expr;
    QStringList m_params;

    bool m_valid;

    void validate();

    using fn_t = std::function<qreal (qreal, qreal)>;

    static const QMap<QString, qreal> m_consts;
    static const QMap<QChar, QPair<quint8, fn_t>> m_ops;
    static const QMap<QString, fn_t> m_fns;
};


#endif /* FORMULA_HPP_INCLUDED_ */
