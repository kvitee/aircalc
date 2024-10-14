#include <QtCore/Qt>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>

#include <QtGui/QPixmap>
#include <QtGui/QResizeEvent>
#include <QtGui/QDoubleValidator>
#include <QtGui/QFont>

#include "parameditwidget.hpp"


ParamEditWidget::ParamEditWidget(
  const Parameter &param,
  QWidget *parent
)
  : QWidget(parent),
    m_labelWidget(new QLabel(param.name)),
    m_fieldWidget(new QLineEdit("0")),
    m_icon(QString(":/icons/") + param.id + QString(".png"))
{
  setupWidgets();
  composeWidgets();
  connectWidgets();
}

void ParamEditWidget::setupWidgets() {
  m_labelWidget->setMinimumWidth(50);
  m_labelWidget->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  m_labelWidget->setToolTip(m_labelWidget->text());

  m_fieldWidget->setMinimumHeight(40);
  m_fieldWidget->setValidator(new QDoubleValidator());

  QFont font = m_fieldWidget->font();
  font.setPointSize(12);

  m_fieldWidget->setFont(font);
}

void ParamEditWidget::composeWidgets() {
  QHBoxLayout *layout = new QHBoxLayout(this);

  layout->addWidget(m_labelWidget);
  layout->addWidget(m_fieldWidget);
}

void ParamEditWidget::connectWidgets() {
  QObject::connect(
    m_fieldWidget, &QLineEdit::editingFinished,
    this, [this]() {
      emit valueChanged(m_fieldWidget->text().toDouble());
    }
  );
}

void ParamEditWidget::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);

  if (m_icon.isNull()) return;

  QPixmap scaledIcon = m_icon.scaledToHeight(
    m_fieldWidget->height() / 2,
    Qt::SmoothTransformation
  );

  m_labelWidget->setPixmap(scaledIcon);
}
