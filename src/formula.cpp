#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>

#include <QtCore/QtTypes>
#include <QtCore/QString>
#include <QtCore/QChar>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QStack>

#include "formula.hpp"


Formula::Formula(const QString &expr) {
  auto r = expr.split("=");

  m_id = r[0];
  m_expr = r[1];

  validate();
}

const QMap<QString, qreal> Formula::m_consts = {
  { "pi", M_PI },
  { "e", M_E },
};

const QMap<QChar, QPair<quint8, Formula::fn_t>> Formula::m_ops = {
  { '+', { 1, [](qreal a, qreal b) { return a + b; } }},
  { '-', { 1, [](qreal a, qreal b) { return a - b; } }},
  { '*', { 2, [](qreal a, qreal b) { return a * b; } }},
  { '/', { 2, [](qreal a, qreal b) { return a / b; } }},
  { '^', { 3, [](qreal a, qreal b) { return std::pow(a, b); } }},
};

const QMap<QString, Formula::fn_t> Formula::m_fns = {
  { "sqrt", [](qreal _, qreal x) { return std::sqrt(x); } },
  { "abs",  [](qreal _, qreal x) { return std::abs(x); } },
  { "ln",   [](qreal _, qreal x) { return std::log(x); } },
  { "sin",  [](qreal _, qreal x) { return std::sin(x); } },
  { "cos",  [](qreal _, qreal x) { return std::cos(x); } },
  { "tan",  [](qreal _, qreal x) { return std::tan(x); } },
};

bool Formula::isValid() const {
  return m_valid;
}

qreal Formula::calculate(const QMap<QString, qreal> &args) const {
  if (!isValid()) return 0.0;

  auto vals = QStack<qreal>();
  auto ops = QStack<QPair<quint32, fn_t>>();

  const auto reduce = [&vals, &ops](quint32 mpr = 0U) {
    while (!ops.empty() && ops.top().first >= mpr) {
      qreal b = vals.pop();
      qreal a = vals.pop();

      vals.push(ops.pop().second(a, b));
    }
  };

  auto ids = QMap<QString, qreal>();

  ids.insert(args);
  ids.insert(m_consts);

  quint32 bp = 0U;

  const auto s_expr = m_expr.toLower().toStdString();
  for (const char *ch = s_expr.c_str();;) {
    while (*ch == '(') {
      bp += 4U; ++ch;
    }

    char *end;
    qreal num = strtod(ch, &end);

    if (ch == end) {
      while (QChar(*ch).isLetterOrNumber() || *ch == '_') ++ch;

      QString id = QString::fromUtf8(end, ch - end);

      auto fn = m_fns.find(id);
      if (fn != m_fns.end()) {
        vals.push(0.0);
        ops.push({ bp + 4U, fn.value() });

        continue;
      }

      num = ids.value(id);
    } else {
      ch = end;
    }

    vals.push(num);

    while (*ch == ')') {
      bp -= 4U; ++ch;
    }

    if (!*ch) break;

    auto op = m_ops.find(*ch++);
    if (op == m_ops.end()) break;

    quint32 p = bp + op.value().first;
    reduce(p);

    ops.push({ p, op.value().second });
  }

  reduce();

  return vals.pop();
}

void Formula::validate() {
  m_valid = true;

  quint32 nl = 0U;

  const auto s_expr = m_expr.toLower().toStdString();
  for (const char *ch = s_expr.c_str();;) {
    while (*ch == '(') {
      ++nl; ++ch;
    }

    char *end;
    strtod(ch, &end);

    if (ch == end) {
      while (QChar(*ch).isLetterOrNumber() || *ch == '_') ++ch;

      QString id = QString::fromUtf8(end, ch - end);

      if (id.isEmpty()) {
        m_valid = false;
        break;
      }

      if (m_fns.contains(id)) {
        continue;
      }

      if (!m_consts.contains(id)) {
        if (!m_params.contains(id)) {
          m_params.push_back(id);
        }
      }
    } else {
      ch = end;
    }

    while (*ch == ')') {
      --nl; ++ch;
    }

    if (!*ch) break;

    if (m_ops.find(*ch++) == m_ops.end()) {
      m_valid = false;
      break;
    };
  }

  if (nl > 0) {
    m_valid = false;
  }
}

const QString &Formula::id() const {
  return m_id;
}

const QString &Formula::expr() const {
  return m_expr;
}

const QStringList &Formula::params() const {
  return m_params;
}
