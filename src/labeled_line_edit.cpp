#include <QtCore/Qt>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>

#include <QtGui/QPixmap>
#include <QtGui/QResizeEvent>

#include "labeled_line_edit.hpp"


LabeledLineEdit::LabeledLineEdit(
  QPixmap icon,
  QWidget *parent
)
  : QWidget(parent),
    m_label(new QLabel()),
    m_lineEdit(new QLineEdit()),
    m_icon(icon)
{
  setupWidgets();
  composeWidgets();
}

QLineEdit *LabeledLineEdit::lineEdit() const {
  return m_lineEdit;
}

void LabeledLineEdit::setupWidgets() {
  m_label->setMinimumWidth(50);
  m_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  m_lineEdit->setMinimumHeight(30);
}

void LabeledLineEdit::composeWidgets() {
  setLayout(new QHBoxLayout());

  layout()->addWidget(m_label);
  layout()->addWidget(m_lineEdit);
}

void LabeledLineEdit::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);

  if (m_icon.isNull()) return;

  QPixmap scaledIcon = m_icon.scaledToHeight(
    m_lineEdit->height() * 0.8,
    Qt::SmoothTransformation
  );

  m_label->setPixmap(scaledIcon);
}
