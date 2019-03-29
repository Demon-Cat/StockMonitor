#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QRegularExpression>
#include <QInputDialog>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(0, 0);

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkRequestFinished);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimer);
    m_timer->start(5000);

    StockWidget *stock = new StockWidget("http://hq.sinajs.cn/list=s_sh000001", this);
    connect(stock, &StockWidget::sig_newStock, this, &MainWindow::onAddNewStock);
    m_stockMap.insert("000001", stock);
    //stock->move(200, 200);
    stock->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimer()
{
    for (auto iter = m_stockMap.constBegin(); iter != m_stockMap.constEnd(); ++iter)
    {
        const StockWidget *stock = iter.value();

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
        const QString &key = match.captured(1);
        qreal currentValue = match.captured(3).toDouble();
        qreal percent = match.captured(5).toDouble();
        if (m_stockMap.contains(key))
        {
            m_stockMap.value(key)->setValue(currentValue, percent);
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
    const QString &key = QInputDialog::getText(this, "请输入代码", "代码：");
    if (key.isEmpty())
    {
        return;
    }

    //url
    QString url;
    if (key.left(2) == QString("60"))
    {
        url = QString("http://hq.sinajs.cn/list=s_sh%1").arg(key);
    }
    else if (key.left(2) == QString("00"))
    {
        url = QString("http://hq.sinajs.cn/list=s_sz%1").arg(key);
    }

    StockWidget *stock = new StockWidget(url, this);
    connect(stock, &StockWidget::sig_newStock, this, &MainWindow::onAddNewStock);
    m_stockMap.insert(key, stock);
    stock->show();
}
