#ifndef LABELED_LINE_EDIT_HPP_INCLUDED_
#define LABELED_LINE_EDIT_HPP_INCLUDED_


#include <QtCore/QObject>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include <QtGui/QPixmap>
#include <QtGui/QResizeEvent>


class LabeledLineEdit : public QWidget {
  Q_OBJECT

  public:
    LabeledLineEdit(
      QPixmap icon,
      QWidget *parent = nullptr
    );

    QLineEdit *lineEdit() const;

  protected:
    QLabel *m_label;
    QLineEdit *m_lineEdit;

    QPixmap m_icon;

    void setupWidgets();
    void composeWidgets();

    void resizeEvent(QResizeEvent *event) override;
};


#endif  /* LABELED_LINE_EDIT_HPP_INCLUDED_ */ 
