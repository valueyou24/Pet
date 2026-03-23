#include "mywidget.h"

#include <QApplication>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;

    QSystemTrayIcon sysTray(QIcon(":/icon/img/icon.png"),&w);

    QMenu menu;
    auto showAct = new QAction("show",&sysTray);
    auto exitAct = new QAction("exit",&sysTray);

    QObject::connect(showAct,&QAction::triggered,[&](){
        w.setVisible(true);
    });

    QObject::connect(exitAct,&QAction::triggered,[&](){
        QApplication::quit();
    });

    menu.addAction(showAct);
    menu.addAction(exitAct);

    sysTray.setContextMenu(&menu);

    sysTray.show();
    w.show();
    return a.exec();
}
