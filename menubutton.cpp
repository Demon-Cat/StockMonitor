#include "menubutton.h"
#include <QPainter>

MenuButton::MenuButton(QWidget *parent) :
    BaseButton(parent)
{

}

void MenuButton::drawBackground(QPainter &painter)
{
    painter.save();
    switch (m_state) {
    case StateNormal:
    {
        painter.setPen(QColor("#E2E2E2"));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rect());
        break;
    }
    case StateHover:
    {
        QColor colorBackground = m_mainColor;
        QColor colorBorder = m_mainColor;
        colorBackground.setAlpha(20);
        colorBorder.setAlpha(100);
        painter.setPen(colorBorder);
        painter.setBrush(colorBackground);
        painter.drawRect(rect());
        break;
    }
    case StatePressed:
    {
        QColor colorBackground = m_mainColor;
        QColor colorBorder = m_mainColor;
        colorBackground.setAlpha(60);
        colorBorder.setAlpha(100);
        painter.setPen(colorBorder);
        painter.setBrush(colorBackground);
        painter.drawRect(rect());
        break;
    }
    default:
        break;
    }
    painter.restore();
}

void MenuButton::drawText(QPainter &painter)
{
    painter.save();
    QColor color = Qt::black;;
    switch (m_state) {
    case StateNormal:
        break;
    case StateHover:
        color = m_mainColor;
        break;
    case StatePressed:
        color = m_mainColor;
        break;
    }
    QFont font = painter.font();
    font.setPixelSize(height() / 4);
    painter.setFont(font);
    painter.setPen(color);
    painter.drawText(rect(), Qt::AlignCenter, text());
    painter.restore();
}
