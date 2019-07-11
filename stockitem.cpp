#include "stockitem.h"
#include "ui_stockitem.h"
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QtDebug>

StockItem::StockItem(const QString &strCode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockItem)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    ui->label_name->setText(strCode);
    ui->toolButton_delete->hide();
}

void StockItem::updateStockInfo(StockInfo *info)
{
    ui->label_name->setText(info->name());
    ui->label_value->setText(QString("%1").arg(info->value(), 0, 'f', 2));
    ui->label_percent->setText(QString("%1%").arg(info->percent(), 0, 'f', 2));

    if (info->percent() > 0)
    {
        setStyleSheet("color: #A00000");
    }
    else if (info->percent() < 0)
    {
        setStyleSheet("color: #00A000");
    }
}

void StockItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    switch (m_state) {
    case StateNormal:
        break;
    case StateHover:
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#20000000"));
        painter.drawRoundedRect(rect(), 4, 4);
        break;
    }
}

void StockItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_state = StateHover;
    ui->toolButton_delete->show();
    update();
}

void StockItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    m_state = StateNormal;
    ui->toolButton_delete->hide();
    update();
}

void StockItem::mousePressEvent(QMouseEvent *event)
{

}

void StockItem::mouseReleaseEvent(QMouseEvent *event)
{

}

void StockItem::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->pos() - m_pressedPoint).manhattanLength() < 50)
    {
        return;
    }

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
//    mimeData->setData("channel", QByteArray::number(m_channel));
//    mimeData->setData("index", QByteArray::number(m_index));
//    mimeData->setData("indexInPage", QByteArray::number(m_indexInPage));
    drag->setMimeData(mimeData);
    //drag->setPixmap(QPixmap(":/liveview/liveview/camera.png"));

    drag->exec(Qt::MoveAction);
}

void StockItem::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "StockItem::dragEnterEvent";
}

void StockItem::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << "StockItem::dragLeaveEvent";
}

void StockItem::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << "StockItem::dragMoveEvent";
}

void StockItem::dropEvent(QDropEvent *event)
{
    qDebug() << "StockItem::dropEvent";
}
