#include "textbutton.h"
#include <QPainter>

TextButton::TextButton(QWidget *parent) :
    BaseButton(parent)
{

}

void TextButton::drawBackground(QPainter &painter)
{
    Q_UNUSED(painter)
}

void TextButton::drawText(QPainter &painter)
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
        break;
    }
    QFont font = painter.font();
    font.setPixelSize(height() / 2);
    painter.setFont(font);
    painter.setPen(color);
    painter.drawText(rect(), Qt::AlignCenter, text());
    painter.restore();
}
