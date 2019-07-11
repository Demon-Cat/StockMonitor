#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    QFont font = a.font();
    font.setFamily("微软雅黑");
    a.setFont(font);

    qSetMessagePattern("[%{time yyyy-MM-dd HH:mm:ss.zzz}] [%{category}] [%{type}] %{message}");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    MainWindow w;
    w.show();

    return a.exec();
}
