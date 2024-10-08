#include <QtCore/Qt>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QFile>
#include <QtCore/QPoint>
#include <QtCore/QSize>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

#include "mainwindow.hpp"
#include "vtabwidget.hpp"
#include "formulawidget.hpp"


MainWindow::MainWindow(
  QWidget *parent,
  Qt::WindowFlags flags
)
  : QMainWindow(parent, flags)
{
  setup();
  initializeWidgets();
}

void MainWindow::setup() {
  move(QPoint(300, 200));
  resize(QSize(680, 480));

  setWindowTitle("Калькулятор");
}

void MainWindow::initializeWidgets() {
  VTabWidget *tw = new VTabWidget(this);
  setCentralWidget(tw);

  QFile f(":/config/formulas.json");
  f.open(QIODevice::ReadOnly);

  QJsonDocument doc = QJsonDocument::fromJson(f.readAll());

  f.close();

  for (auto formula : doc.array()) {
    if (!formula.isObject()) continue;

    auto f_obj = formula.toObject();

    FormulaWidget *tab = new FormulaWidget(f_obj["expr"].toString());

    tw->addTab(
      tab,
      QIcon(QString(":/icons/") + f_obj["id"].toString() + QString(".png")),
      f_obj["name"].toString()
    );

    for (auto p : f_obj["params"].toArray()) {
      if (!p.isObject()) continue;

      auto p_obj = p.toObject();

      tab->addParam({
        p_obj["id"].toString(),
        p_obj["name"].toString()
      });
    }
  }
}
