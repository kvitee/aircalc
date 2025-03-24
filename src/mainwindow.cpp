#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QSize>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

#include "mainwindow.hpp"


MainWindow::MainWindow(
  QWidget *parent,
  Qt::WindowFlags flags
)
  : QMainWindow(parent, flags)
{
  setup();
}

void MainWindow::setup() {
  move(QPoint(300, 200));
  resize(QSize(680, 480));

  setWindowTitle("Калькулятор формул");
}
