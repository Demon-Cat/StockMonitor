#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMap>

#include "stockinfo.h"
#include "stockitem.h"
#include "addstock.h"

namespace Ui {
class StockWidget;
}

class StockWidget : public QWidget
{
    Q_OBJECT

    enum State
    {
        StateNormal,
        StateAboutToShow,
        StateAboutToHide
    };

public:
    explicit StockWidget(QWidget *parent = nullptr);
    ~StockWidget();

    void setAboutToShow();
    void setAboutToHide();
    void updateShowOrHide();

    void setHide();

    void updateStockInfo(StockInfo *info);

protected:
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

signals:

private slots:
    void onStateTimer();
    void onMainColorChanged(const QColor &color);

    void on_toolButton_add_clicked();

private:
    Ui::StockWidget *ui;

    bool m_isPressed = false;
    QPoint m_pressedPos;

    bool m_isEnter = false;

    State m_state = StateNormal;
    QTimer *m_stateTimer;

    int m_shadowWidth = 10;

    QColor m_mainColor = QColor("#A00000");

    AddStock *m_addStock = nullptr;
    QMap<QString, StockItem *> m_stockMap;
};

#endif // STOCKWIDGET_H
