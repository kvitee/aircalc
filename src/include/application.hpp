#ifndef APPLICATION_HPP_INCLUDED_
#define APPLICATION_HPP_INCLUDED_


#include <QtCore/QObject>

#include <QtWidgets/QApplication>

#include "mainwindow.hpp"


class Application : public QApplication {
  Q_OBJECT

  public:
    Application(int &argc, char **argv);

    ~Application();

  private:
    MainWindow *m_mainWindow;
};


#endif  /* APPLICATION_HPP_INCLUDED_ */ 
