#include <QtCore/QCoreApplication>

#include <QtWidgets/QApplication>

#include "application.hpp"
#include "mainwindow.hpp"


Application::Application(int &argc, char **argv)
  : QApplication(argc, argv)
{
  QCoreApplication::setOrganizationName("kvsoft");
  QCoreApplication::setApplicationName("aircalc");

  auto f = font();
  f.setPointSizeF(f.pointSizeF() * 1.2);
  setFont(f);

  m_mainWindow = new MainWindow();
  m_mainWindow->show();
}

Application::~Application() {
  delete m_mainWindow;
}
