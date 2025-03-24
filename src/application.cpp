#include <QtCore/QCoreApplication>

#include <QtWidgets/QApplication>

#include "application.hpp"
#include "mainwindow.hpp"


Application::Application(int &argc, char **argv)
  : QApplication(argc, argv)
{
  QCoreApplication::setOrganizationName("kvsoft");
  QCoreApplication::setApplicationName("aircalc");

  m_mainWindow = new MainWindow();
  m_mainWindow->show();
}

Application::~Application() {
  delete m_mainWindow;
}
