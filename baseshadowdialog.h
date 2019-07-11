#ifndef BASESHADOWDIALOG_H
#define BASESHADOWDIALOG_H

#include <QDialog>

class BaseShadowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BaseShadowDialog(QWidget *parent = 0);

    void setTitleWidget(QWidget *title);

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:

private:
    QWidget *m_titleWidget = nullptr;
    int m_shadowWidth = 10;
    QPoint m_pressPoint;
    bool m_bPressed = false;
};

#endif // BASESHADOWDIALOG_H
