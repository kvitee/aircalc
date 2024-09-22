#include <QtWidgets/QApplication>

#include <QtGui/QIcon>

#include "application.hpp"
#include "mainwindow.hpp"


Application::Application(int &argc, char **argv)
  : QApplication(argc, argv)
{
  setWindowIcon(QIcon(":/icons/qt.ico"));

  m_mainWindow = new MainWindow();
  m_mainWindow->show();
}

Application::~Application() {
  delete m_mainWindow;
}
