#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "basebutton.h"

class MenuButton : public BaseButton
{
    Q_OBJECT
public:
    explicit MenuButton(QWidget *parent = nullptr);

protected:
    void drawBackground(QPainter &painter) override;
    void drawText(QPainter &painter) override;

signals:

public slots:
};

#endif // MENUBUTTON_H
