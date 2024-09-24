#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

#include "vtabwidget.hpp"
#include "vtabbar.hpp"


VTabWidget::VTabWidget(QWidget *parent)
  : QTabWidget(parent)
{
  setTabBar(new VTabBar());
  setTabPosition(QTabWidget::West);
}
