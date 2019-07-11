#include "capsulestock.h"
#include <QPainter>
#include <QMouseEvent>
#include "mainwindow.h"

CapsuleStock::CapsuleStock(const QString &strName, QWidget *parent) :
    QWidget(parent),
    m_strName(strName)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(120, 60);
}

void CapsuleStock::updateStockInfo(StockInfo *info)
{
    m_strName = info->name();
    m_value = info->value();
    m_increase = info->increase();
    m_percent = info->percent();

    if (m_percent < 0)
    {
        m_mainColor = QColor("#00A000");
    }
    else if (m_percent > 0)
    {
        m_mainColor = QColor("#A00000");
    }

    update();
}

void CapsuleStock::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_state = StateHover;
    update();
}

void CapsuleStock::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_state = StateNormal;
    update();
}

void CapsuleStock::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    m_pressDistance = event->globalPos() - pos();
}

void CapsuleStock::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    m_isPressed = false;
}

void CapsuleStock::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        move(event->globalPos() - m_pressDistance);
    }
}

void CapsuleStock::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    m_mainRoundRect = QRect(m_shadowWidth, m_shadowWidth, width() - 2 * m_shadowWidth, height() - 2 * m_shadowWidth);
}

void CapsuleStock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawMainRoundRectShadow(painter);
    drawMainRoundRect(painter);
    drawValue(painter);
}

void CapsuleStock::drawMainRoundRect(QPainter &painter)
{
    painter.save();
    //
    painter.setPen(Qt::NoPen);
    QLinearGradient linearGradient(QPointF(m_mainRoundRect.center().x(), m_mainRoundRect.top()), QPointF(m_mainRoundRect.center().x(), m_mainRoundRect.bottom()));
    linearGradient.setColorAt(0, QColor("#F5F5F5"));
    linearGradient.setColorAt(1, QColor("#D8D8D8"));
    painter.setBrush(linearGradient);
    painter.drawRoundedRect(m_mainRoundRect, m_mainRoundRect.height() / 2, m_mainRoundRect.height() / 2);
    //
    painter.restore();
}

void CapsuleStock::drawMainRoundRectShadow(QPainter &painter)
{
    painter.save();
    qreal alphaStep = 80.0 / m_shadowWidth;
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < m_shadowWidth; i++)
    {
        QRect rc = m_mainRoundRect.marginsAdded(QMargins(i, i, i, i));
        color.setAlpha(80 - i * alphaStep);
        painter.setPen(color);
        painter.drawRoundedRect(rc, m_mainRoundRect.height() / 2 + i, m_mainRoundRect.height() / 2 + i);
    }
    if (m_state == StateHover)
    {
        QRect rc = m_mainRoundRect.marginsAdded(QMargins(2, 2, 2, 2));
        QColor color = m_mainColor;
        color.setAlpha(100);
        painter.setPen(QPen(color, 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(rc, rc.height() / 2, rc.height() / 2);
    }
    painter.restore();
}

void CapsuleStock::drawValue(QPainter &painter)
{
    //
    if (m_state == StateHover)
    {
        QRect rcTopLeft = m_mainRoundRect;
        rcTopLeft.setRight(m_mainRoundRect.center().x());
        rcTopLeft.setBottom(m_mainRoundRect.center().y());

        QRect rcBottomLeft = m_mainRoundRect;
        rcBottomLeft.setTop(m_mainRoundRect.center().y());
        rcBottomLeft.setRight(m_mainRoundRect.center().x());

        painter.save();
        QFont font = painter.font();
        font.setPixelSize(rcTopLeft.height() / 2);
        painter.setFont(font);
        painter.setPen(m_mainColor);
        painter.drawText(rcTopLeft, Qt::AlignCenter, m_strName);
        painter.drawText(rcBottomLeft, Qt::AlignCenter, QString("%1%").arg(m_percent, 0, 'f', 2));
        painter.restore();
    }
    else
    {
        QRect rcLeft = m_mainRoundRect;
        rcLeft.setRight(m_mainRoundRect.center().x());

        painter.save();
        QFont font = painter.font();
        font.setPixelSize(rcLeft.height() / 3);
        painter.setFont(font);
        painter.setPen(m_mainColor);
        painter.drawText(rcLeft, Qt::AlignCenter, QString("%1%").arg(m_percent, 0, 'f', 2));
        painter.restore();
    }
    //
    QRect rcTopRight = m_mainRoundRect;
    rcTopRight.setLeft(m_mainRoundRect.center().x());
    rcTopRight.setBottom(m_mainRoundRect.center().y());

    QRect rcBottomRight = m_mainRoundRect;
    rcBottomRight.setTop(m_mainRoundRect.center().y());
    rcBottomRight.setLeft(m_mainRoundRect.center().x());

    painter.save();
    QFont font = painter.font();
    font.setPixelSize(rcTopRight.height() / 2);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(rcTopRight, Qt::AlignCenter, QString("%1").arg(m_increase, 0, 'f', 2));
    painter.drawText(rcBottomRight, Qt::AlignCenter, QString("%1").arg(m_value, 0, 'f', 2));
    painter.restore();
}

void CapsuleStock::onMainColorChanged(const QColor &color)
{
    m_mainColor = color;
    update();
}
