#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QSize>

#include <QtWidgets/QWidget>
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

  setWindowTitle("AirCalc");
}

void MainWindow::initializeWidgets() {
  VTabWidget *tw = new VTabWidget(this);
  setCentralWidget(tw);

  tw->addTab(new FormulaWidget(
    "1/2*b*h",
    {
      { "b", "Base" },
      { "h", "Height" },
    }
  ), QIcon(":/icons/qt.ico"), "Triangle Area");
  tw->addTab(new FormulaWidget(
    "pi*r^2",
    {
      { "r", "Radius" },
    }
  ), QIcon(":/icons/qt.ico"), "Circle Area");
}
