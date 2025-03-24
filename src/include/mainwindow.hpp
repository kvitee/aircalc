#ifndef MAINWINDOW_HPP_INCLUDED_
#define MAINWINDOW_HPP_INCLUDED_


#include <QtCore/Qt>
#include <QtCore/QObject>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

#include <QtGui/QCloseEvent>


class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow(
      QWidget *parent = nullptr,
      Qt::WindowFlags flags = Qt::WindowFlags()
    );

  protected:
    void closeEvent(QCloseEvent *event);

    void setup();

    void saveSettings();
    void restoreSettings();
};


#endif  /* MAINWINDOW_HPP_INCLUDED_ */ 
