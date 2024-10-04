#include <QtCore/Qt>
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

  tw->addTab(new FormulaWidget(
    "l_vpp-l_otk",
    {
      { "l_vpp", "" },
      { "l_otk", "" },
    }
  ), QIcon("icons/l_rasp.png"), "");
  tw->addTab(new FormulaWidget(
    "7170-10.34*m+4.067*v_otk+0.0035*m^2+0.00518-v_otk*m-0.017*v_otk^2",
    {
      { "m", "" },
      { "v_otk", "" },
    }
  ), QIcon("icons/l_torm.png"), "");
  tw->addTab(new FormulaWidget(
    "v_otr^2/(2*j_sr)",
    {
      { "v_otr", "" },
      { "j_sr", "" },
    }
  ), QIcon("icons/l_1.png"), "");
}
