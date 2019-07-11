#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QRegularExpression>
#include <QInputDialog>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QtDebug>

MainWindow *MainWindow::s_mainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(140, 70);

    s_mainWindow = this;

    //
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkRequestFinished);

    //
    m_queryTimer = new QTimer(this);
    connect(m_queryTimer, &QTimer::timeout, this, &MainWindow::onQueryTimer);
    m_queryTimer->start(2000);
    onQueryTimer();

    //
    m_stockWidget = new StockWidget(this);
    m_stockWidget->hide();

    //
    addStock("000001");

    //
    addCapsuleStock("600835");
}

MainWindow::~MainWindow()
{
    s_mainWindow = nullptr;
    delete ui;
}

MainWindow *MainWindow::instance()
{
    return s_mainWindow;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_mainCircleRect = QRect(m_shadowWidth, m_shadowWidth, height() - 2 * m_shadowWidth, height() - 2 * m_shadowWidth);

    m_mainRoundRect.setLeft(m_mainCircleRect.left() + m_mainCircleRect.width() / 2);
    m_mainRoundRect.setTop(m_mainCircleRect.top() + 5);
    m_mainRoundRect.setRight(width() - m_shadowWidth);
    m_mainRoundRect.setBottom(m_mainCircleRect.bottom() - 5);

    QMainWindow::resizeEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    drawMainRoundRectShadow(painter);
    drawMainCircleShadow(painter);
    drawMainRoundRect(painter);
    drawMainCircle(painter);
}

void MainWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    //qDebug() << "MainWindow::enterEvent";
    m_isEnter = true;

    m_stockWidget->setAboutToShow();

    update();
}

void MainWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    //qDebug() << "MainWindow::leaveEvent";
    m_isEnter = false;

    m_stockWidget->setAboutToHide();

    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    m_pressDistance = event->globalPos() - pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    m_isPressed = false;

    //
    if (!m_stockWidget->isVisible())
    {
        m_stockWidget->setAboutToShow();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        move(event->globalPos() - m_pressDistance);
    }

    //
    m_stockWidget->setHide();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)

    if (!m_mainMenu)
    {
        m_mainMenu = new MainMenu(this);
    }
    QRect rc = m_mainMenu->geometry();
    const QRect &desktopRect = qApp->desktop()->geometry();
    const QPoint &pos = event->globalPos();
    rc.moveTopLeft(pos);
    if (pos.x() + m_mainMenu->width() > desktopRect.right())
    {
        rc.moveRight(desktopRect.right() - m_mainMenu->width());
    }
    if (pos.y() + m_mainMenu->height() >desktopRect.bottom())
    {
        rc.moveBottom(desktopRect.bottom() - m_mainMenu->height());
    }

    m_mainMenu->move(rc.topLeft());
    m_mainMenu->show();
}

void MainWindow::drawMainCircle(QPainter &painter)
{
    painter.save();
    //
    painter.setRenderHint(QPainter::Antialiasing);
    //
    painter.setPen(QColor("#B2B2B2"));
    QLinearGradient linearGradient(QPointF(m_mainRoundRect.center().x(), m_mainRoundRect.top()), QPointF(m_mainRoundRect.center().x(), m_mainRoundRect.bottom()));
    linearGradient.setColorAt(0, QColor("#F5F5F5"));
    linearGradient.setColorAt(1, QColor("#D8D8D8"));
    painter.setBrush(linearGradient);
    painter.drawEllipse(m_mainCircleRect);
    //
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_mainCircleColor);
    painter.drawEllipse(m_mainCircleRect.marginsRemoved(QMargins(3, 3, 3, 3)));
    //
    StockInfo *stock = m_stockMap.value("000001", nullptr);
    if (stock)
    {
        //百分比
        int m_startAngle = 270 - 1.8 * stock->percent() * 10;
        int m_spanAngle = 3.6 * stock->percent() * 10;
        int startAngle = m_startAngle * 16;
        int spanAngle = m_spanAngle * 16;
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#60FFFFFF"));
        painter.drawChord(m_mainCircleRect.marginsRemoved(QMargins(5, 5, 5, 5)), startAngle, spanAngle);
        //
        QFont font = painter.font();
        font.setBold(true);
        font.setPixelSize(13);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(m_mainCircleRect, Qt::AlignCenter, QString("%1%").arg(qAbs(stock->percent()), 0, 'f', 2));
    }
    //
    painter.restore();
}

void MainWindow::drawMainCircleShadow(QPainter &painter)
{
    painter.save();
    qreal alphaStep = 80.0 / m_shadowWidth;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < m_shadowWidth; i++)
    {
        QRect rc = m_mainCircleRect.marginsAdded(QMargins(i, i, i, i));
        color.setAlpha(80 - i * alphaStep);
        painter.setPen(color);
        painter.drawEllipse(rc);
    }
    if (m_isEnter)
    {
        QRect rc = m_mainCircleRect.marginsAdded(QMargins(2, 2, 2, 2));
        QColor color = m_mainCircleColor;
        color.setAlpha(100);
        painter.setPen(QPen(color, 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(rc);
    }
    painter.restore();
}

void MainWindow::drawMainRoundRect(QPainter &painter)
{
    painter.save();
    //
    painter.setRenderHint(QPainter::Antialiasing);
    //
    painter.setPen(Qt::NoPen);
    QLinearGradient linearGradient(QPointF(m_mainRoundRect.center().x(), m_mainRoundRect.top()), QPointF(m_mainRoundRect.center().x(), m_mainRoundRect.bottom()));
    linearGradient.setColorAt(0, QColor("#F5F5F5"));
    linearGradient.setColorAt(1, QColor("#D8D8D8"));
    painter.setBrush(linearGradient);
    painter.drawRoundedRect(m_mainRoundRect, m_mainRoundRect.height() / 2, m_mainRoundRect.height() / 2);
    //
    StockInfo *stock = m_stockMap.value("000001", nullptr);
    if (stock)
    {
        //
        QFont font = painter.font();
        font.setPixelSize(12);
        painter.setFont(font);
        painter.setPen(Qt::black);
        //
        QRect topRc = m_mainRoundRect;
        topRc.setLeft(topRc.left() + 10);
        topRc.setBottom(m_mainRoundRect.center().y());
        painter.drawText(topRc, Qt::AlignCenter, QString("%1").arg(stock->increase(), 0, 'f', 2));
        //
        QRect bottomRc = m_mainRoundRect;
        bottomRc.setLeft(bottomRc.left() + 10);
        bottomRc.setTop(m_mainRoundRect.center().y());
        painter.drawText(bottomRc, Qt::AlignCenter, QString("%1").arg(stock->value(), 0, 'f', 2));
    }
    //
    painter.restore();
}

void MainWindow::drawMainRoundRectShadow(QPainter &painter)
{
    painter.save();
    qreal alphaStep = 80.0 / m_shadowWidth;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < m_shadowWidth; i++)
    {
        QRect rc = m_mainRoundRect.marginsAdded(QMargins(i, i, i, i));
        color.setAlpha(80 - i * alphaStep);
        painter.setPen(color);
        painter.drawRoundedRect(rc, m_mainRoundRect.height() / 2 + i, m_mainRoundRect.height() / 2 + i);
    }
    if (m_isEnter)
    {
        QRect rc = m_mainRoundRect.marginsAdded(QMargins(2, 2, 2, 2));
        QColor color = m_mainCircleColor;
        color.setAlpha(100);
        painter.setPen(QPen(color, 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(rc, rc.height() / 2, rc.height() / 2);
    }
    painter.restore();
}

void MainWindow::addStock(const QString &strCode)
{
    StockInfo *stock = new StockInfo(strCode, this);
    m_stockMap.insert(strCode, stock);
}

void MainWindow::deleteStock(const QString &strCode)
{
    StockInfo *stock = m_stockMap.value(strCode, nullptr);
    if (stock)
    {
        stock->deleteLater();
        stock = nullptr;
    }
    m_stockMap.remove(strCode);
}

void MainWindow::addCapsuleStock(const QString &strCode)
{
    if (m_capsuleStockMap.contains(strCode))
    {
        return;
    }
    addStock(strCode);
    //
    CapsuleStock *stock = new CapsuleStock(strCode, this);
    stock->show();
    m_capsuleStockMap.insert(strCode, stock);
}

void MainWindow::onQueryTimer()
{
    for (auto iter = m_stockMap.constBegin(); iter != m_stockMap.constEnd(); ++iter)
    {
        const StockInfo *stock = iter.value();

        QNetworkRequest request;
        request.setUrl(QUrl(stock->url()));
        request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

        m_manager->get(request);
    }
}

void MainWindow::onNetworkRequestFinished(QNetworkReply *reply)
{
    QByteArray baData = reply->readAll();

    QString strData = QTextCodec::codecForName("GBK")->toUnicode(baData);
    //qDebug() << strData;

    //var hq_str_s_sh000001="上证指数,3026.9513,-33.3560,-1.09,4532146,45124730";
    QRegularExpression re("(\\d+)=\"(.+),(.+),(.+),(.+),(.+),(.+)\";");
    QRegularExpressionMatch match = re.match(strData);
    if (match.hasMatch())
    {
        //qDebug() << match.captured(0);
        QString key = match.captured(1);
        QString name = match.captured(2);
        qreal value = match.captured(3).toDouble();
        qreal increase = match.captured(4).toDouble();
        qreal percent = match.captured(5).toDouble();

        StockInfo *stock = m_stockMap.value(key, nullptr);
        if (stock)
        {
            stock->setName(name);
            stock->setValue(value);
            stock->setIncrease(increase);
            stock->setPercent(percent);

            //
            m_stockWidget->updateStockInfo(stock);

            //
            CapsuleStock *capsule = m_capsuleStockMap.value(key, nullptr);
            if (capsule)
            {
                capsule->updateStockInfo(stock);
            }

            //
            if (stock->code() == "000001")
            {
                QColor color("#A00000");
                const qreal percent = stock->percent();
                if (percent < 0)
                {
                    color = QColor("#00A000");
                }
                else if (percent > 0)
                {
                    color = QColor("#A00000");
                }
                if (m_mainCircleColor != color)
                {
                    m_mainCircleColor = color;
                    emit mainColorChanged(color);
                }
                update();
            }
        }
    }
    else
    {

    }

    //
    reply->deleteLater();
}

void MainWindow::onAddNewStock()
{

}
