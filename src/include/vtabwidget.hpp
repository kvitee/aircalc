#ifndef VTABWIDGET_HPP_INCLUDED_
#define VTABWIDGET_HPP_INCLUDED_


#include <QtCore/QObject>

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>


class VTabWidget : public QTabWidget {
  Q_OBJECT

  public:
    VTabWidget(QWidget *parent = nullptr);
};


#endif  /* VTABWIDGET_HPP_INCLUDED_ */ 
