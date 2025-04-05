#include <QtCore/Qt>
#include <QtCore/QFile>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QSettings>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

#include <QtGui/QCloseEvent>

#include "mainwindow.hpp"
#include "formulas_calculator.hpp"


MainWindow::MainWindow(
  QWidget *parent,
  Qt::WindowFlags flags
)
  : QMainWindow(parent, flags)
{
  setup();
  initWidgets();

  restoreSettings();
}

void MainWindow::closeEvent(QCloseEvent *event) {
  saveSettings();

  event->accept();
}

void MainWindow::setup() {
  move(QPoint(300, 200));
  resize(QSize(680, 480));

  setWindowTitle("Калькулятор формул");
}

void MainWindow::initWidgets() {
  auto cw = new FormulasCalculator();
  setCentralWidget(cw);

  QFile f("config/formulas.json");
  f.open(QIODevice::ReadOnly);

  QJsonDocument doc = QJsonDocument::fromJson(f.readAll());

  f.close();

  for (auto expr : doc.array()) {
    cw->addFormula(expr.toString());
  }
}

void MainWindow::saveSettings() {
  QSettings settings;
  settings.setValue("mainwindow/geometry", saveGeometry());
}

void MainWindow::restoreSettings() {
  QSettings settings;
  settings.beginGroup("mainwindow");

  const auto geometry = settings.value("geometry").toByteArray();
  if (!geometry.isEmpty()) {
    restoreGeometry(geometry);
  }

  settings.endGroup();
}
