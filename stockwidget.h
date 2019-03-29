#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>

namespace Ui {
class StockWidget;
}

class StockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StockWidget(const QString &url, QWidget *parent = nullptr);
    ~StockWidget();

    QString url() const;

    void setValue(qreal current, qreal percent);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void sig_newStock();

private:
    Ui::StockWidget *ui;

    QString m_url;

    bool m_isPressed = false;
    QPoint m_pressedPos;

    qreal m_currentValue = 0;
    qreal m_percent = 0;

    QMenu *m_menu;
    QAction *m_action_quit;
    QAction *m_action_new;
};

#endif // STOCKWIDGET_H
