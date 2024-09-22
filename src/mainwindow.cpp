#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QSize>

#include <QtWidgets/QWidget>

#include "mainwindow.hpp"


MainWindow::MainWindow(
  QWidget *parent,
  Qt::WindowFlags flags
)
  : QMainWindow(parent, flags)
{
  setup();
  initializeWidgets();
  composeWidgets();
  connectWidgets();
}

MainWindow::~MainWindow() {}


void MainWindow::setup() {
  move(QPoint(300, 200));
  resize(QSize(780, 480));

  setWindowTitle("AirCalc");
}

void MainWindow::initializeWidgets() {
  QWidget *central_widget = new QWidget(this);
  setCentralWidget(central_widget);
}

void MainWindow::composeWidgets() {}

void MainWindow::connectWidgets() {}
