#ifndef STOCKITEM_H
#define STOCKITEM_H

#include <QWidget>
#include "stockinfo.h"

namespace Ui {
class StockItem;
}


class StockItem : public QWidget
{
    Q_OBJECT

    enum State
    {
        StateNormal,
        StateHover
    };

public:
    explicit StockItem(const QString &strCode, QWidget *parent = nullptr);

    void updateStockInfo(StockInfo *info);

protected:
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:

public slots:

private:
    Ui::StockItem *ui;

    State m_state = StateNormal;

    QPoint m_pressedPoint;
};

#endif // STOCKITEM_H
