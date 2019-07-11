#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QPainter>
#include "addstock.h"
#include "mainwindow.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //阴影
    painter.save();
    qreal alphaStep = 100.0 / m_shadowWidth;
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < m_shadowWidth; i++)
    {
        QRect rect(m_shadowWidth - i, m_shadowWidth - i, this->width() - (m_shadowWidth - i) * 2, this->height() - (m_shadowWidth - i) * 2);
        //int alpha = 150 - qSqrt(i) * 50;
        color.setAlpha(100 - i * alphaStep);
        painter.setPen(color);
        painter.drawRoundedRect(rect, i, i);
    }
    painter.restore();

    //背景
    QRect backgroundRect = rect().marginsRemoved(QMargins(10, 10, 10, 10));
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F7F7F7"));
    painter.drawRect(backgroundRect);
    painter.restore();
}

void MainMenu::on_toolButton_capsule_clicked()
{
    AddStock addStock(this);
    addStock.showAddStock();
    const int result = addStock.exec();
    if (result != AddStock::Accepted)
    {
        return;
    }
    const QString strCode = addStock.code();
    if (strCode.isEmpty())
    {
        return;
    }
    //
    MainWindow::instance()->addCapsuleStock(strCode);
}

void MainMenu::on_toolButton_quit_clicked()
{
    qApp->quit();
}
