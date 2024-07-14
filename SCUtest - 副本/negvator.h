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



QT_BEGIN_NAMESPACE
namespace Ui {
class negvator;
}
QT_END_NAMESPACE

class negvator : public QMainWindow
{
    Q_OBJECT

public:
    negvator(QWidget *parent = nullptr);
    void setNode();

    int isTimeToCall(QDateTime current);
    void checkTime();


    ~negvator();



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

signals:

    //void judge_time();


public:
    Ui::negvator *ui;
    negvator *negSelf=this;
    QGraphicsPixmapItem *map;
    QGraphicsScene *scene;
    ItemContainer itemCon;//物体容器
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
    //QTimer *checkNowTimer;
    QDateTime time;
    //route
    double dis=0;
    double density[3]; //密度；人流量;根据时间 and 天气
    double costTime=0;
    int transportation=0; //0 is foot ;1 is bicycle; 2 is school-bus
    double baseV[3];
    double v=0;//速度 m/min
};


#endif // NEGVATOR_H
