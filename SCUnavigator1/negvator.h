#ifndef NEGVATOR_H
#define NEGVATOR_H

#include <QMainWindow>
#include<QImage>
#include<QGraphicsView>
#include<QFileDialog>
#include<QGraphicsScene>
#include<QObject>
#include<QMenu>
#include<QtWidgets>
#include"myitem.h"
#include"infowin.h"
#include<QTime>
#include<QDateTime>
#include<QTimer>
#include"chatclient.h"
#include<QCloseEvent>
#include"tip.h"

QT_BEGIN_NAMESPACE




namespace Ui {
class negvator;
}
QT_END_NAMESPACE



class negvator : public QMainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *e)
    {

        this->chat->bye();


    }

public:

    negvator(QWidget *parent = nullptr);
    ~negvator();
    void setNode();


    //void generateMan();
    int isTimeToCall(QDateTime current);
    void checkTime();




    void generateMan()
    {
        for(int i=0;i<60;i++)
        {
            scene->removeItem(manCon.item[i]);
        }
        manCon.clear(60);

        QPixmap manImage[4];
        manImage[0].load(":/new/prefix1/resource/man.png");///////size   pay
        manImage[1].load(":/new/prefix1/resource/1.png");
        manImage[2].load(":/new/prefix1/resource/2.png");
        manImage[3].load(":/new/prefix1/resource/3.png");
        MyItem itemTemp(manImage[0]);
        //itemTemp.setScale(60);
        double mansizex=itemTemp.boundingRect().width(),mansizey=itemTemp.boundingRect().height();
        for(int i=0;i<60;i++)
        {
            int s=QRandomGenerator::global()->bounded(4);
            int where=QRandomGenerator::global()->bounded(100);
            MyItem *man=new MyItem(manImage[s]);
            man->setScale(0.8);
            man->nowSeq=where;
            man->nowId=itemCon.item[man->nowSeq]->id;
            man->setPos(itemCon.p[man->nowSeq]->x-(mansizex)*0.5,itemCon.p[man->nowSeq]->y-(mansizey)*0.5);
            scene->addItem(man);
            manCon.item.push_back(man);
        }


        //
    }








private slots:



    void on_src_returnPressed();

    void on_pushButton_pressed();

    void on_dest_returnPressed();

    void search();

    void userMenu();

    void mainWindow(){};


    void on_pushButton_clicked();
//
    void roadCondition_slot(int color);//0 is green,1 is yellow ,2 is red;

    void setNowTime();//设置现在的时间
    void on_toChat_clicked();

    void on_comboBox_4_activated(int index);

    void on_nowTimeEdit_dateChanged(const QDate &date);

    void on_nowTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_comboBox_2_activated(int index);

signals:

    //void judge_time();


public:
    Ui::negvator *ui;
    negvator *negSelf=this;
    QGraphicsPixmapItem *map;
    QGraphicsScene *scene;
    ItemContainer itemCon;//物体容器
    ItemContainer manCon;//人容器
    vector<QGraphicsLineItem *>lineItem;
    vector<QGraphicsLineItem *>roadCondition;
    InfoWin* infoWin;
    QString mapFile;
    QString src;
    QString dest;
    QPen *roadPen;
    //for user
    int account;
    //time
    QTimer *timer;
    QTimer *checkNowTimer;
    QTimer *threadTimer;
    QDateTime time;

    //route
    double dis=0;
    double density[3]; //密度；人流量;根据时间 and 天气
    double costTime=0;
    int transportation=0; //0 is foot ;1 is bicycle; 2 is school-bus
    double baseV[3];
    double v=0;//速度 m/min
    //chat
    ChatClient *chat;
    //弹窗
    tip *tips;
    //线程类
    std::thread* threads;

};

void generateMan(negvator *p);
void moving(negvator *p);
void moveMan(negvator *p);
#endif // NEGVATOR_H
