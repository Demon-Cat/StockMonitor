#include "roundedbutton.h"
#include <QPainter>
#include "mainwindow.h"

RoundedButton::RoundedButton(QWidget *parent) :
    BaseButton(parent)
{

}

RoundedButton::~RoundedButton()
{

}

void RoundedButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_mainColor);
    painter.drawRoundedRect(rect(), height() / 2, height() / 2);
    switch (m_state) {
    case StateNormal:
        break;
    case StateHover:
        painter.setBrush(QColor("#20FFFFFF"));
        painter.drawRoundedRect(rect(), height() / 2, height() / 2);
        break;
    case StatePressed:
        break;
    }
    painter.restore();

    //文字
    painter.save();
    QFont font = painter.font();
    font.setPixelSize(height() / 2);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, text());
    painter.restore();
}
