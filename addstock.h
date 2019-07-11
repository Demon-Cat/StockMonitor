#ifndef ADDSTOCK_H
#define ADDSTOCK_H

#include "baseshadowdialog.h"

namespace Ui {
class AddStock;
}

class AddStock : public BaseShadowDialog
{
    Q_OBJECT

public:
    explicit AddStock(QWidget *parent = nullptr);
    ~AddStock();

    void showAddStock();

    QString code() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onMainColorChanged(const QColor &color);

    void on_toolButton_close_clicked();
    void on_toolButton_ok_clicked();
    void on_toolButton_cancel_clicked();

private:
    Ui::AddStock *ui;

    QColor m_mainColor = QColor("#A00000");
};

#endif // ADDSTOCK_H
