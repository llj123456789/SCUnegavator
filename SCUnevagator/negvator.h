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
#include<QTimer>



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

    bool isTimeToCall(QDateTime current);
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

    void roadCondition_slot();


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

};


#endif // NEGVATOR_H
