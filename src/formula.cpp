#include <iostream>

#include <QtCore/QString>
#include <QtCore/QMap>

#include "formula.hpp"


Formula::Formula(const QString &expression)
  : m_expression(expression) {}

double Formula::calculate(const QMap<QString, double> &args) {
  std::cout << "Calculating "
            << m_expression.toStdString()
            << " with arguments:\n";

  for (auto key : args.keys()) {
    std::cout << " - " << key.toStdString() << " = " << args[key] << '\n';
  }

  return 0.0;
}
