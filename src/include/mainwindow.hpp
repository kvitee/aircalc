#ifndef MAINWINDOW_HPP_INCLUDED_
#define MAINWINDOW_HPP_INCLUDED_


#include <QtCore/Qt>
#include <QtCore/QObject>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>


class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow(
      QWidget *parent = nullptr,
      Qt::WindowFlags flags = Qt::WindowFlags()
    );

    ~MainWindow();

  private:
    void setup();
    void initializeWidgets();
    void composeWidgets();
    void connectWidgets();
};


#endif  /* MAINWINDOW_HPP_INCLUDED_ */ 
