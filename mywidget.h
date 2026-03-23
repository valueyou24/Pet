#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include<QMap>
#include<QList>
#include<QUrl>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include<QContextMenuEvent>
#include<QMenu>
QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

namespace Act
{
    Q_NAMESPACE

enum RoleAct{
        Swing,
        Sleep,
        SayHello
    };

    Q_ENUM_NS(RoleAct)
}


using namespace Act;
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void showActAnimation(RoleAct k);
public slots:
    void onMenuTrigger(QAction* event);

private:
    Ui::MyWidget *ui;

    QMap<RoleAct,QList<QUrl>> action_map;
    QTimer* timer;
    RoleAct cur_role_act;
    QUrl cur_role_pix;
    QMenu* menu;

protected:
    void paintEvent(QPaintEvent* event) override;
    void contextMenuEvent(QContextMenuEvent*event);

private:
    void loadRoleActRes();
    void initMenu();

};


class DragFilter:public QObject
{
public:
    bool eventFilter(QObject* obj,QEvent* event) override;

private:
    QPoint pos;

};

#endif // MYWIDGET_H
