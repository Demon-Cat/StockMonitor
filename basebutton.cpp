#include "basebutton.h"
#include <QPainter>
#include "mainwindow.h"

BaseButton::BaseButton(QWidget *parent) :
    QToolButton(parent)
{
    connect(MainWindow::instance(), &MainWindow::mainColorChanged, this, &BaseButton::onMainColorChanged);
}

void BaseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBackground(painter);
    drawText(painter);
}

void BaseButton::mousePressEvent(QMouseEvent *event)
{
    m_state = StatePressed;
    update();

    QToolButton::mousePressEvent(event);
}

void BaseButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_state = StateHover;
    update();

    QToolButton::mouseReleaseEvent(event);
}

void BaseButton::enterEvent(QEvent *)
{
    m_state = StateHover;
    update();
}

void BaseButton::leaveEvent(QEvent *)
{
    m_state = StateNormal;
    update();
}

void BaseButton::drawBackground(QPainter &painter)
{

}

void BaseButton::drawText(QPainter &painter)
{

}

void BaseButton::onMainColorChanged(const QColor &color)
{
    m_mainColor = color;
    update();
}
