#ifndef ROUNDEDBUTTON_H
#define ROUNDEDBUTTON_H

#include "basebutton.h"

class RoundedButton : public BaseButton
{
    Q_OBJECT

public:
    explicit RoundedButton(QWidget *parent = nullptr);
    ~RoundedButton();

protected:
    void paintEvent(QPaintEvent *) override;

signals:

private:

};

#endif // ROUNDEDBUTTON_H
