#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QSize>

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

#include "mainwindow.hpp"
#include "vtabwidget.hpp"


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

  tw->addTab(new QPushButton("Calc 1"), QIcon(":/icons/qt.ico"), "Formula 1");
  tw->addTab(new QPushButton("Calc 2"), QIcon(":/icons/qt.ico"), "Formula 2");
  tw->addTab(new QPushButton("Calc 3"), QIcon(":/icons/qt.ico"), "Formula 3");
}
