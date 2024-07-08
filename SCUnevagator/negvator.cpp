#include "negvator.h"
#include "user.h"
#include "ui_negvator.h"

negvator::negvator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::negvator)
{




    // 连接QTimer的timeout信号到checkTime函数
    timer=new QTimer;
    timer->start(5000);
    connect(timer, &QTimer::timeout,this,&negvator::checkTime);



    ui->setupUi(this);

    ui->src->setVisible(false);
    ui->dest->setVisible(false);
    ui->pushButton->setVisible(false);

    setWindowIcon(QIcon(":/new/prefix1/resource/icon.png"));

    //load a setting windows

    //load pen
    this->roadPen=new QPen;
    roadPen->setColor(Qt::blue);
    roadPen->setWidth(16);
    //loading map
    this->mapFile=":/new/prefix1/resource/map/ja.jpg";
    QPixmap pixmap(mapFile);
    this->map = new QGraphicsPixmapItem(pixmap);
    this->map->setPos(QPointF(0,0));
    this->scene=new QGraphicsScene;
    this->scene->addItem(map);

    //add node;
    QPixmap itemImage(":/new/prefix1/resource/mapp.png");


    itemCon.readNodeLink();

    MyItem itemTemp(itemImage);//用于获取item宽和高
    double sizex=itemTemp.boundingRect().width(),sizey=itemTemp.boundingRect().height();
    for(int i=0;i<itemCon.num;i++)
    {
        MyItem *item = new MyItem(itemImage);
        itemCon.item.push_back(item);
        item->name=itemCon.p[i]->name;
        item->id=itemCon.p[i]->id;
        item->setPos(itemCon.p[i]->x-(sizex)*0.25,itemCon.p[i]->y-(sizey)*0.5);
        item->setScale(0.5);
        if(item->id<1000)
        {
            item->setVisible(false);
        }
        scene->addItem(item); // 将item添加到场景中
    }
    //创建长桥roadCondition//编号为0
    QPointF f1,f2;
    for(int i=0;i<itemCon.num;i++)
    {
        if(itemCon.p[i]->name=="图书馆")
        {
            f1=QPointF(itemCon.p[i]->x,itemCon.p[i]->y);
        }
        if(itemCon.p[i]->name=="二基楼")
        {
            f2=QPointF(itemCon.p[i]->x,itemCon.p[i]->y);
        }
    }
    QGraphicsLineItem *temp=new QGraphicsLineItem(QLineF(f1,f2));
    roadCondition.push_back(temp);
    roadCondition_slot();


    ui->mapView->setScene(scene);
    ui->mapView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->mapView->show();

    //ui->mapView->translate();

    //setLineEditor
    ui->notice->setText("Now Noting");
    ui->src->setPlaceholderText("请输入起点");
    ui->dest->setPlaceholderText("请输入终点");


    //connect toolbutton
    connect(ui->mainWindow,&QAction::triggered,this,&negvator::mainWindow);
    connect(ui->search,&QAction::triggered,this,&negvator::search);
    connect(ui->user,&QAction::triggered,this,&negvator::userMenu);
    //connect auto emit
    //(this,SIGNAL(judge_time()),this,SLOT(roadCondition_slot()),Qt::QueuedConnection);




}



negvator::~negvator()
{
    delete ui;
    delete map;
}

void negvator::search()
{
    ui->dest->setVisible(true);
    ui->src->setVisible(true);
    ui->pushButton->setVisible(true);


}

void negvator::userMenu()
{
    User *user=new User;
    user->setTempNeg(this);
    this->close();
    user->show();
}

void negvator::on_pushButton_pressed()
{
    this->src=ui->src->text();
    this->dest=ui->dest->text();
    ui->src->setVisible(false);
    ui->dest->setVisible(false);
    ui->pushButton->setVisible(false);

    int did=0;
    int sid=0;
    for(int i=0;i<itemCon.num;i++)
    {
        if(dest==itemCon.p[i]->getname())
        {
            did=itemCon.p[i]->getid();
        }
        if(src==itemCon.p[i]->getname())
        {
            sid=itemCon.p[i]->getid();
        }
    }
    //
    qDebug()<<"起点ID:";
    qDebug()<<sid;
    qDebug()<<"终点ID:";
    qDebug()<<did;

    itemCon.transfer(itemCon.num);
    itemCon.dijkstra(sid,did);
    itemCon.print_path(sid,did);
    deque<int>way=itemCon.way;
    for(int i=0;i<way.size();i++)
    {
        qDebug()<<"路径：";
        qDebug()<<way[i];
    }
//清除前一次路径
    if(!lineItem.empty())
    {
        for(int i=lineItem.size()-1;i>=0;i--)
        {
            scene->removeItem(lineItem[i]);
        }
        lineItem.clear();
    }
//载入新路径
    for(int i=0;i<way.size()-1;i++)
    {
        int id1=0,id2=0;
        for(int j=0;j<itemCon.num;j++)
        {
            if(itemCon.p[j]->id==way[i])
            {
                id1=j;
            }else if(itemCon.p[j]->id==way[i+1])
            {
                id2=j;
            }
        }
        QLineF centerLine((itemCon.p[id1])->x,(itemCon.p[id1])->y,itemCon.p[id2]->x,itemCon.p[id2]->y);
        lineItem.push_back(new QGraphicsLineItem(centerLine));
        lineItem[i]->setPen(*roadPen);
        scene->addItem(lineItem[i]);

    }
    way.clear();
    itemCon.way.clear();//

//////////////////////////////////////////////搜索路径实验田

    if(this->infoWin==NULL)
    {

        this->infoWin=new InfoWin(0);
        this->infoWin->show();
    }
    else
    {
        this->infoWin->close();
        delete this->infoWin;
        this->infoWin=new InfoWin(0);
        this->infoWin->show();
    }

////////////////////////////////////////////////

}


void negvator::on_src_returnPressed()
{

}


void negvator::on_dest_returnPressed()
{

}




void negvator::on_pushButton_clicked()
{

}

bool negvator::isTimeToCall(QDateTime current) {
    current.setTimeSpec(Qt::LocalTime);
    QDateTime startTime(QDate::currentDate(), QTime(8, 0, 0));
    QDateTime endTime(QDate::currentDate(), QTime(14, 0, 0));
    return current >= startTime && current <= endTime;
}

void negvator::checkTime() {
    QDateTime current = QDateTime::currentDateTime();
    if (isTimeToCall(current)) {
        //emit judge_time();
        roadCondition_slot();
    }
}
void negvator::roadCondition_slot()
{
    QPen p(Qt::red,25);
    for(int i=0;i<roadCondition.size();i++)
    {
        if(roadCondition[i]->scene()==nullptr)
        {
            roadCondition[i]->setPen(p);
            scene->addItem(roadCondition[i]);
            qDebug()<<"timer";
        }else
        {

        }
    }
}

