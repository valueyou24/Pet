#include "mywidget.h"
#include "ui_mywidget.h"
#include<QPaintEvent>
#include<QPainter>//绘图
#include<QPixmap>
#include<QCursor>
#include<QMetaEnum>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::MyWidget)
    ,timer(new QTimer(this))
    ,menu(new QMenu(this))
{

    this->setWindowFlag(Qt::FramelessWindowHint);//去除窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    this->installEventFilter(new DragFilter);//鼠标点击事件

    connect(timer,&QTimer::timeout,[this](){
        static int index = 0;//记录显示动作的当前图片索引
        auto paths = this->action_map.value(this->cur_role_act);
        this->cur_role_pix = paths[index++ % paths.size()];

        //painEvent()不允许这样调用函数
        this->update();
    });

    initMenu();

    loadRoleActRes();

    showActAnimation(RoleAct::Swing);

    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::showActAnimation(RoleAct k)
{
    timer->stop();

    this->cur_role_act = k;

    timer->start(60);

}

void MyWidget::onMenuTrigger(QAction *event)
{
    QMetaEnum me =QMetaEnum::fromType<RoleAct>();
    bool ok;
    int k = me.keyToValue(event->text().toStdString().c_str(),&ok);

    if(!ok) return;

    showActAnimation(static_cast<RoleAct>(k));
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(this->cur_role_pix.toLocalFile());

    painter.drawPixmap(0,0,pix);

    //painter.drawRect(100,100,200,200);
}

void MyWidget::contextMenuEvent(QContextMenuEvent *event)
{
    this->menu->popup(QCursor::pos());
}

void MyWidget::loadRoleActRes()
{
    auto addRes = [this](RoleAct k,QString path,int count)
    {
        QList<QUrl> paths;
        char buf[260];
        for(int i = 0; i < count; i++)
        {
            memset(buf,0,sizeof(buf));
            sprintf_s(buf,path.toStdString().c_str(),i);
            paths.append(QUrl::fromLocalFile(buf));
        }
        action_map.insert(k,paths);
    };

    addRes(RoleAct::SayHello,":/SayHello/img/sayHello/sayHello_%d.png",28);
    addRes(RoleAct::Sleep,":/Sleep/img/sleep/sleep_%d.png",25);
    addRes(RoleAct::Swing,":/Swing/img/swing/swing_%d.png",32);
}

void MyWidget::initMenu()
{
    menu->addAction("SayHello");
    menu->addAction("Sleep");
    menu->addAction("Swing");

    QAction* act = new QAction("Hide");

    connect(act,&QAction::triggered,[this](){
        this->setVisible(false);
    });
    menu->addAction(act);

    connect(this->menu,&QMenu::triggered,this,&MyWidget::onMenuTrigger);
}


bool DragFilter::eventFilter(QObject *obj, QEvent *event)
{
    auto w = dynamic_cast<QWidget*>(obj);
    if(!w)
        return false;

    if(event->type() == QEvent::MouseButtonPress)
    {
        auto e = dynamic_cast<QMouseEvent*>(event);
        if(e)
        {
            pos = e->pos();
        }
    }
    else if(event->type() == QEvent::MouseMove)
    {
        auto e = dynamic_cast<QMouseEvent*>(event);
        if(e)
        {
            if(e->buttons()&Qt::MouseButton::LeftButton)
            {
                w->move(e->globalPosition().toPoint()-pos);
            }
        }
    }

    return QObject::eventFilter(obj,event);
}
