#include "stockwidget.h"
#include "ui_stockwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QStyle>
#include "mainwindow.h"

StockWidget::StockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //
    m_stateTimer = new QTimer(this);
    m_stateTimer->setSingleShot(true);
    m_stateTimer->setInterval(1000);
    connect(m_stateTimer, &QTimer::timeout, this, &StockWidget::onStateTimer);

    //
    m_addStock = new AddStock(this);

    //
    ui->scrollArea->setStyleSheet("QScrollArea {background-color: transparent;}");
    ui->scrollAreaWidgetContents->setStyleSheet("background-color: transparent;");

    //
    connect(MainWindow::instance(), &MainWindow::mainColorChanged, this, &StockWidget::onMainColorChanged);
}

StockWidget::~StockWidget()
{
    delete ui;
}

void StockWidget::setAboutToShow()
{
    m_state = StateAboutToShow;
    m_stateTimer->start();
}

void StockWidget::setAboutToHide()
{
    m_state = StateAboutToHide;
    m_stateTimer->start();
}

void StockWidget::updateShowOrHide()
{
    switch (m_state) {
    case StateAboutToShow:
    {
        const QRect &desktopRect = qApp->desktop()->geometry();
        const QRect &mainRect = MainWindow::instance()->geometry();
        QRect rc = geometry();
        rc.moveTop(mainRect.bottom());
        rc.moveLeft(mainRect.center().x() - rc.width() / 2);
        if (rc.bottom() > desktopRect.bottom())
        {
            rc.moveTop(mainRect.top() - rc.height());
        }
        if (rc.left() < desktopRect.left())
        {
            rc.moveLeft(desktopRect.left());
        }
        if (rc.right() > desktopRect.right())
        {
            rc.moveRight(desktopRect.right());
        }
        move(rc.topLeft());

        show();
        //activateWindow();
        break;
    }
    case StateAboutToHide:
    {
        if (m_isEnter || m_addStock->isVisible())
        {
            m_stateTimer->start();
            break;
        }
        hide();
        break;
    }
    default:
        break;
    }
}

void StockWidget::setHide()
{
    m_stateTimer->stop();
    hide();
}

void StockWidget::updateStockInfo(StockInfo *info)
{
    StockItem *item = m_stockMap.value(info->code(), nullptr);
    if (item)
    {
        item->updateStockInfo(info);
    }
}

//void StockWidget::mousePressEvent(QMouseEvent *event)
//{
//    m_isPressed = true;
//    m_pressedPos = event->globalPos() - pos();
//    QWidget::mousePressEvent(event);
//}

//void StockWidget::mouseReleaseEvent(QMouseEvent *event)
//{
//    m_isPressed = false;
//    QWidget::mouseReleaseEvent(event);
//}

//void StockWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    if (m_isPressed)
//    {
//        move(event->globalPos() - m_pressedPos);
//    }
//    QWidget::mouseMoveEvent(event);
//}

void StockWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    qDebug() << "StockWidget::enterEvent";
    m_isEnter = true;
}

void StockWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    qDebug() << "StockWidget::leaveEvent";
    m_isEnter = false;
}

void StockWidget::paintEvent(QPaintEvent *event)
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
    painter.setBrush(QColor("#F7F8FA"));
    painter.drawRect(backgroundRect);
    painter.restore();

    //标题
    QRect titleRect = ui->widget_top->geometry();
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_mainColor);
    painter.drawRect(titleRect);
    painter.restore();
}

void StockWidget::onStateTimer()
{
    updateShowOrHide();
}

void StockWidget::onMainColorChanged(const QColor &color)
{
    m_mainColor = color;
    update();
}

void StockWidget::on_toolButton_add_clicked()
{
    QRect rc = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_addStock->size(), rect());
    m_addStock->move(mapToGlobal(rc.topLeft()));
    m_addStock->showAddStock();
    int result = m_addStock->exec();
    if (result != AddStock::Accepted)
    {
        return;
    }

    const QString strCode = m_addStock->code();
    if (strCode.isEmpty())
    {
        return;
    }
    if (m_stockMap.contains(strCode))
    {
        return;
    }
    StockItem *item = new StockItem(strCode, this);
    ui->verticalLayout_item->addWidget(item);
    m_stockMap.insert(strCode, item);
    //
    MainWindow::instance()->addStock(strCode);
}
