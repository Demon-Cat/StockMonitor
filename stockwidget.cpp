#include "stockwidget.h"
#include "ui_stockwidget.h"
#include <QPainter>
#include <QMouseEvent>

StockWidget::StockWidget(const QString &url, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockWidget),
    m_url(url)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //
    m_menu = new QMenu(this);

    m_action_new = new QAction("添加", m_menu);
    connect(m_action_new, &QAction::triggered, this, &StockWidget::sig_newStock);
    m_menu->addAction(m_action_new);

    m_action_quit = new QAction("退出", m_menu);
    connect(m_action_quit, &QAction::triggered, qApp, &QApplication::quit);
    m_menu->addAction(m_action_quit);
}

StockWidget::~StockWidget()
{
    delete ui;
}

QString StockWidget::url() const
{
    return m_url;
}

void StockWidget::setValue(qreal current, qreal percent)
{
    m_currentValue = current;
    m_percent = percent;
    update();
}

void StockWidget::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    m_pressedPos = event->globalPos() - pos();
    QWidget::mousePressEvent(event);
}

void StockWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    QWidget::mouseReleaseEvent(event);
}

void StockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        move(event->globalPos() - m_pressedPos);
    }
    QWidget::mouseMoveEvent(event);
}

void StockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#80000000"));
    painter.drawRoundedRect(rect(), 10, 10);
    painter.restore();

    painter.save();
    if (m_percent < 0)
    {
        painter.setPen(Qt::green);
    }
    else if (m_percent > 0)
    {
        painter.setPen(Qt::red);
    }
    else
    {
        painter.setPen(Qt::white);
    }
    QRect topRect = rect();
    topRect.setBottom(height() / 2);
    painter.drawText(topRect, Qt::AlignCenter, QString::number(m_currentValue));
    QRect bottomRect = rect();
    bottomRect.setTop(topRect.bottom());
    painter.drawText(bottomRect, Qt::AlignCenter, QString("%1%").arg(m_percent));
    painter.restore();
}

void StockWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)

    m_menu->exec(QCursor::pos());
}
