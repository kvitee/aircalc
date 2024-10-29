#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <string>

#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QMap>
#include <QtCore/QStack>

#include "formula.hpp"


Formula::Formula(const QString &expr)
  : m_expr(expr) {}

const QMap<QString, double> Formula::m_consts = {
  { "pi", M_PI },
  { "e", M_E },
};

const QMap<QChar, QPair<quint8, Formula::fn_t>> Formula::m_ops = {
  { '+', { 1, [](double a, double b) { return a + b; } }},
  { '-', { 1, [](double a, double b) { return a - b; } }},
  { '*', { 2, [](double a, double b) { return a * b; } }},
  { '/', { 2, [](double a, double b) { return a / b; } }},
  { '^', { 3, [](double a, double b) { return std::pow(a, b); } }},
};

const QMap<QString, Formula::fn_t> Formula::m_fns = {
  { "sqrt", [](double _, double x) { return std::sqrt(x); } },
  { "abs",  [](double _, double x) { return std::abs(x); } },
  { "ln",   [](double _, double x) { return std::log(x); } },
  { "sin",  [](double _, double x) { return std::sin(x); } },
  { "cos",  [](double _, double x) { return std::cos(x); } },
  { "tan",  [](double _, double x) { return std::tan(x); } },
};

double Formula::calculate(const QMap<QString, double> &args) {
  auto vals = QStack<double>();
  auto ops = QStack<QPair<quint32, fn_t>>();

  const auto reduce = [&vals, &ops](quint32 mpr = 0U) {
    while (!ops.empty() && ops.top().first >= mpr) {
      double b = vals.pop();
      double a = vals.pop();

      vals.push(ops.pop().second(a, b));
    }
  };

  auto ids = QMap<QString, double>();

  ids.insert(args);
  ids.insert(m_consts);

  quint32 bp = 0U;

  const std::string s_expr = m_expr.toLower().toStdString();
  for (const char *ch = s_expr.c_str();;) {
    while (*ch == '(') {
      bp += 4U; ++ch;
    }

    char *end;
    double num = strtod(ch, &end);

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
