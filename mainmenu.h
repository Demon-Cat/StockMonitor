#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_toolButton_capsule_clicked();

    void on_toolButton_quit_clicked();

private:
    Ui::MainMenu *ui;

    int m_shadowWidth = 10;
};

#endif // MAINMENU_H
