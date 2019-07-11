#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "menubutton.h"

class TextButton : public BaseButton
{
    Q_OBJECT
public:
    TextButton(QWidget *parent = nullptr);

protected:
    void drawBackground(QPainter &painter) override;
    void drawText(QPainter &painter) override;
};

#endif // TEXTBUTTON_H
