#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QMap>
#include <QtCore/QStack>

#include "formula.hpp"


Formula::Formula(const QString &expr)
  : m_expr(expr) {}

const QMap<QString, double> Formula::m_consts = {
  { "pi", M_PIl },
  { "e", M_El },
};

const QMap<QChar, QPair<quint8, Formula::fn_t>> Formula::m_ops = {
  { '+', { 1, [](double a, double b) { return a + b; } }},
  { '-', { 1, [](double a, double b) { return a - b; } }},
  { '*', { 2, [](double a, double b) { return a * b; } }},
  { '/', { 2, [](double a, double b) { return a / b; } }},
  { '^', { 3, [](double a, double b) { return std::pow(a, b); } }},
};

double Formula::calculate(const QMap<QString, double> &args) {
  auto vals = QStack<double>();
  auto ops = QStack<QPair<quint32, fn_t>>();

  const auto reduce = [&vals, &ops](quint32 mpr = 0) {
    while (!ops.empty() && ops.top().first >= mpr) {
      double b = vals.pop();
      double a = vals.pop();

      vals.push(ops.pop().second(a, b));
    }
  };

  auto ids = QMap<QString, double>();

  ids.insert(args);
  ids.insert(m_consts);

  quint32 bp = 0;

  const std::string s_expr = m_expr.toLower().toStdString();
  for (const char *ch = s_expr.c_str();; ++ch) {
    while (*ch == '(') {
      bp += 3; ++ch;
    }

    char *end;
    double num = strtod(ch, &end);

    if (ch == end) {
      while (QChar(*end).isLetterOrNumber() || *end == '_') ++end;

      num = ids.value(QString::fromUtf8(ch, end - ch));
    }

    ch = end;
    vals.push(num);

    while (*ch == ')') {
      bp -= 3; ++ch;
    }

    if (!*ch) break;

    auto op = m_ops.value(*ch);

    quint32 p = bp + op.first;
    reduce(p);

    ops.push({p, op.second});
  }

  reduce();

  return vals.pop();
}
