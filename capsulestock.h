#ifndef CAPSULESTOCK_H
#define CAPSULESTOCK_H

#include <QWidget>
#include "stockinfo.h"

class CapsuleStock : public QWidget
{
    Q_OBJECT

    enum State
    {
        StateNormal,
        StateHover
    };

public:
    explicit CapsuleStock(const QString &strName, QWidget *parent = nullptr);

    void updateStockInfo(StockInfo *info);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawMainRoundRect(QPainter &painter);
    void drawMainRoundRectShadow(QPainter &painter);
    void drawValue(QPainter &painter);

signals:

public slots:
    void onMainColorChanged(const QColor &color);

private:
    State m_state = StateNormal;

    bool m_isPressed = false;
    QPoint m_pressDistance;

    QColor m_mainColor = QColor("#A00000");

    int m_shadowWidth = 8;
    QRect m_mainRoundRect;

    QString m_strName;
    qreal m_value = 0;
    qreal m_increase = 0;
    qreal m_percent = 0;
};

#endif // CAPSULESTOCK_H
