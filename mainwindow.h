#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QPainter>

#include "mainmenu.h"
#include "stockwidget.h"
#include "capsulestock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow *instance();

    //
    void addStock(const QString &strCode);
    void deleteStock(const QString &strCode);

    void addCapsuleStock(const QString &strCode);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void drawMainCircle(QPainter &painter);
    void drawMainCircleShadow(QPainter &painter);
    void drawMainRoundRect(QPainter &painter);
    void drawMainRoundRectShadow(QPainter &painter);

signals:
    void mainColorChanged(const QColor &color);

private slots:
    void onQueryTimer();
    void onNetworkRequestFinished(QNetworkReply *reply);

    void onAddNewStock();

private:
    static MainWindow *s_mainWindow;

    Ui::MainWindow *ui;

    bool m_isPressed = false;
    QPoint m_pressDistance;

    bool m_isEnter = false;

    int m_shadowWidth = 8;
    QRect m_mainCircleRect;
    QColor m_mainCircleColor = QColor("#A00000");
    QRect m_mainRoundRect;

    QNetworkAccessManager *m_manager;
    QTimer *m_queryTimer;

    QMap<QString, StockInfo *> m_stockMap;

    //
    StockWidget *m_stockWidget = nullptr;

    //
    QMap<QString, CapsuleStock *> m_capsuleStockMap;

    //
    MainMenu *m_mainMenu = nullptr;
};

#endif // MAINWINDOW_H
