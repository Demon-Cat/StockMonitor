#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <QToolButton>

class BaseButton : public QToolButton
{
    Q_OBJECT

protected:
    enum State
    {
        StateNormal,
        StateHover,
        StatePressed
    };

public:
    explicit BaseButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;

    virtual void drawBackground(QPainter &painter);
    virtual void drawText(QPainter &painter);

signals:

private slots:
    void onMainColorChanged(const QColor &color);

protected:
    QColor m_mainColor = QColor("#A00000");

    State m_state = StateNormal;
};

#endif // BASEBUTTON_H
