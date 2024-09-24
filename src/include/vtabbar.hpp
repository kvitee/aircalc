#ifndef VTABBAR_HPP_INCLUDED_
#define VTABBAR_HPP_INCLUDED_


#include <QtCore/QObject>
#include <QtCore/QSize>

#include <QtWidgets/QTabBar>
#include <QtWidgets/QWidget>

#include <QtGui/QPaintEvent>


class VTabBar : public QTabBar {
  Q_OBJECT

  public:
    QSize tabSizeHint(int index) const;

  protected:
    void paintEvent(QPaintEvent *event);
};


#endif  /* VTABBAR_HPP_INCLUDED_ */ 
