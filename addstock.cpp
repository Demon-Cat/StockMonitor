#include "addstock.h"
#include "ui_addstock.h"
#include <QPainter>
#include "mainwindow.h"

AddStock::AddStock(QWidget *parent) :
    BaseShadowDialog(parent),
    ui(new Ui::AddStock)
{
    ui->setupUi(this);

    //
    connect(MainWindow::instance(), &MainWindow::mainColorChanged, this, &AddStock::onMainColorChanged);
}

AddStock::~AddStock()
{
    delete ui;
}

void AddStock::showAddStock()
{
    ui->lineEdit_code->clear();
    ui->lineEdit_code->setFocus();
}

QString AddStock::code() const
{
    return ui->lineEdit_code->text();
}

void AddStock::paintEvent(QPaintEvent *event)
{
    BaseShadowDialog::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //背景
    QRect backgroundRect = rect().marginsRemoved(QMargins(10, 10, 10, 10));
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F7F8FA"));
    painter.drawRect(backgroundRect);
    painter.restore();

    //标题
    QRect titleRect = ui->widget_title->geometry();
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_mainColor);
    painter.drawRect(titleRect);
    painter.restore();
}

void AddStock::onMainColorChanged(const QColor &color)
{
    m_mainColor = color;
    update();
}

void AddStock::on_toolButton_close_clicked()
{
    reject();
}

void AddStock::on_toolButton_ok_clicked()
{
    accept();
}

void AddStock::on_toolButton_cancel_clicked()
{
    reject();
}
