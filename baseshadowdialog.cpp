#include "baseshadowdialog.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>

BaseShadowDialog::BaseShadowDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowModality(Qt::WindowModal);

    setFocusPolicy(Qt::StrongFocus);
}

void BaseShadowDialog::setTitleWidget(QWidget *title)
{
    m_titleWidget = title;
    m_titleWidget->installEventFilter(this);
}

bool BaseShadowDialog::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == m_titleWidget)
    {
        if (e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *event = static_cast<QMouseEvent *>(e);
            m_pressPoint = event->globalPos() - pos();
            m_bPressed = true;

        }
        if (e->type() == QEvent::MouseMove)
        {
            QMouseEvent *event = static_cast<QMouseEvent *>(e);
            move(event->globalPos() - m_pressPoint);
        }
        if (e->type() == QEvent::MouseButtonRelease)
        {
            m_bPressed = false;
        }
    }
    return QDialog::eventFilter(obj, e);
}

void BaseShadowDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    qreal alphaStep = 100.0 / m_shadowWidth;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < m_shadowWidth; i++)
    {
        QRect rect(m_shadowWidth - i, m_shadowWidth - i, this->width() - (m_shadowWidth - i) * 2, this->height() - (m_shadowWidth - i) * 2);
        //int alpha = 150 - qSqrt(i) * 50;
        color.setAlpha(100 - i * alphaStep);
        painter.setPen(color);
        painter.drawRoundedRect(rect, i, i);
    }
}
