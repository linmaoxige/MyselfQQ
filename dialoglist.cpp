#include "dialoglist.h"
#include "ui_dialoglist.h"
#include <QToolButton>
#include <QDebug>
#include <widget.h>
#include <QMessageBox>

DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    //h设置标题
    setWindowTitle("MyselfQQ 2020");
    //设置图标
    setWindowIcon(QPixmap(":/images/qq.jpg"));

    //准备图标
    QList<QString>nameList;
    nameList << "冰雪奇缘" << "浮生如梦" <<"淡然" <<"霜霜" <<"雯雯" <<"雪莲" <<"弱水三千" <<"胡萝卜"
             << "千百度" << "阿水";
    //图标资源列表
    QStringList iconNameList;
    iconNameList << "1"<< "2"<< "3"<< "4"<< "5"<< "6"<< "7"<< "8"<< "9"<< "10";

    QVector <QToolButton *> vToolBtn;


    for (int i = 0; i < 10; i++) {
        //设置头像
        QToolButton * btn = new QToolButton;
        //设置文字
        btn->setText(nameList[i]);
        //设置头像
        QString str = QString(":/images/%1.jpg").arg(iconNameList.at(i));
        btn->setIcon(QPixmap(str));
        //设置头像大小
        btn->setIconSize(QSize(70,70));
        //设置按钮风格 透明
        btn->setAutoRaise(true);
        //设置文字和图片一起显示
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //加到 垂直布局中
        ui->vLayout->addWidget(btn);
        //容器保存住10个按钮，方便以后再次操作
        vToolBtn.push_back(btn);
        //9个标示默认初始化
        isShow.push_back(false);

    }
    //对9个按钮 进行添加信号槽
    for(int i = 0; i < vToolBtn.size(); i++)
    {
        connect(vToolBtn[i], &QToolButton::clicked,[=](){
            //如果被打开了，就不要再次打开
            if(isShow[i])
            {
                QString str = QString("%1窗口已经被打开了").arg(vToolBtn[i]->text());
                QMessageBox::warning(this,"警告",str);
                return;
            }
            isShow[i] = true;

            //弹出对话框
            //构造聊天窗口时候 告诉这个窗口他的名字 参数1 顶层方式弹出 方式2 窗口名字

            Widget * widget = new Widget(0,vToolBtn[i]->text());
            //设置窗口标题
            widget->setWindowTitle(vToolBtn[i]->text());
            widget->setWindowIcon(vToolBtn[i]->icon());
            widget->show();

            connect(widget,&Widget::closeWidget,[=](){
                isShow[i] = false;
            });

        });
    }


}

DialogList::~DialogList()
{
    delete ui;
}
