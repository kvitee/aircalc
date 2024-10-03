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
    "l_vpp-l_otk",
    {
      { "l_vpp", "<i>L</i><sub>ВПП</sub>" },
      { "l_otk", "<i>L</i><sub>ОТК'</sub>" },
    }
  ), "L_РАСП");
  tw->addTab(new FormulaWidget(
    "7170-10.34*m+4.067*v_otk+0.0035*m^2+0.00518-v_otk*m-0.017*v_otk^2",
    {
      { "m", "m" },
      { "v_otk", "<i>V</i><sub>ОТК</sub>" },
    }
  ), "L_ТОРМ");
  tw->addTab(new FormulaWidget(
    "v_otr^2/(2*j_avg)",
    {
      { "v_otr", "<i>V</i><sub>отр</sub>" },
      { "j_avg", "<i>j</i><sub>ср</sub>" },
    }
  ), "L_1");
}
