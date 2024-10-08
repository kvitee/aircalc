#include <QtCore/QObject>
#include <QtCore/QRect>
#include <QtCore/QSize>
#include <QtCore/QPoint>

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabBar>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOptionTab>
#include <QtWidgets/QStylePainter>

#include <QtGui/QPaintEvent>

#include "vtabbar.hpp"


QSize VTabBar::tabSizeHint(int index) const {
  return QTabBar::tabSizeHint(index).transposed();
}

void VTabBar::paintEvent(QPaintEvent *event) {
  QStylePainter painter(this);
  QStyleOptionTab opt;

  for (int i = 0; i < count(); ++i) {
    initStyleOption(&opt, i);

    painter.drawControl(QStyle::CE_TabBarTabShape, opt);
    painter.save();

    QSize s(opt.rect.size());
    s.transpose();

    QRect r(QPoint(), s);
    r.moveCenter(opt.rect.center());

    opt.rect = r;

    QPoint c = tabRect(i).center();

    painter.translate(c);
    painter.rotate(90);
    painter.translate(-c);
    painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
    painter.restore();
  }

  QWidget::paintEvent(event);
}
