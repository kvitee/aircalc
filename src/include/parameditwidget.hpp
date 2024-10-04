#ifndef PARAMEDITWIDGET_HPP_INCLUDED_
#define PARAMEDITWIDGET_HPP_INCLUDED_


#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include <QtGui/QPixmap>
#include <QtGui/QResizeEvent>


class ParamEditWidget : public QWidget {
  Q_OBJECT

  public:
    struct Parameter {
      QString id;
      QString name;
    };

    ParamEditWidget(
      const Parameter &param,
      QWidget *parent = nullptr
    );

  signals:
    void valueChanged(double value) const;

  protected:
    QLabel *m_labelWidget;
    QLineEdit *m_fieldWidget;

    QPixmap m_icon;

    void setupWidgets();
    void composeWidgets();
    void connectWidgets();

    void resizeEvent(QResizeEvent *event) override;
};


#endif  /* PARAMEDITWIDGET_HPP_INCLUDED_ */ 
