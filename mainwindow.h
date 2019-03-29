#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>

#include "stockwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimer();
    void onNetworkRequestFinished(QNetworkReply *reply);

    void onAddNewStock();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *m_manager;
    QTimer *m_timer;

    QMap<QString, StockWidget *> m_stockMap;
};

#endif // MAINWINDOW_H
