#include "negvator.h"
#include "user.h"
#include "ui_negvator.h"

negvator::negvator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::negvator)
{
    ui->setupUi(this);
    //界面初始化
    this->ui->route->setStyleSheet("background-image:url(:/new/prefix1/resource/routeBack.jpg);\n"
                                "background-attachment:fixed;\n"
                                "background-repeat:none;\n"
                                   "background-position:center");


    this->ui->nowTimeEdit->setDateTime(QDateTime::currentDateTime());

    this->ui->information->setStyleSheet("QLineEdit{color:balck;background:transparent;font-size:20px;border:none;border-bottom:1px solid rgb(229, 229, 229)}"
                                   "QLineEdit::hover{}"

                                   );

    //this->ui->announcement->setStyleSheet("QLabel{background:white}");

    // 连接QTimer的timeout信号到checkTime函数
    timer=new QTimer;
    timer->start(60000);
    connect(timer, &QTimer::timeout,this,&negvator::checkTime);
    connect(timer,&QTimer::timeout,this,&negvator::setNowTime);

    //信息初始化
    baseV[0]=1.9*60; //m/min
    baseV[1]=15*1000/60;
    baseV[2]=20*1000/60; //NEED WAIT; //BUS TABLE
    density[0]=0,density[1]=0,density[2]=0;


    ui->src->setVisible(false);
    ui->dest->setVisible(false);
    ui->pushButton->setVisible(false);

    setWindowIcon(QIcon(":/new/prefix1/resource/icon.png"));
    setWindowTitle("SCUnegvator");
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
        if(itemCon.p[i]->name=="零")
        {
            f1=QPointF(itemCon.p[i]->x,itemCon.p[i]->y);
        }
        if(itemCon.p[i]->name=="青春广场")
        {
            f2=QPointF(itemCon.p[i]->x,itemCon.p[i]->y);
        }
    }
    QGraphicsLineItem *temp=new QGraphicsLineItem(QLineF(f1,f2));
    roadCondition.push_back(temp);
    checkTime();

//
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
    User *user=new User(this->account);
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
    deque<int>way=itemCon.way; //store id


//show info on route
    QString routeName[1000];
    int seq[1000];
    for(int i=0;i<way.size();i++)
    {
        qDebug()<<"路径：";
        qDebug()<<way[i];
        for(int j=0;j<itemCon.num;j++)
        {
            if(itemCon.p[j]->id==way[i])
            {
                routeName[i]=itemCon.p[j]->name;
                seq[i]=j;
            }
        }



    }
    this->ui->route->setText(QString("  FROM THE %1 TO THE %2: \n ").arg(routeName[0]).arg(routeName[way.size()-1]));
    this->dis=0;
    for(int i=0;i<way.size()-1;i++)
    {

        double p2pdis=(*(itemCon.p[i])-*(itemCon.p[i+1]));
        dis+=p2pdis;
        this->ui->route->append(QString("%1 -> %2").arg(routeName[i]).arg(p2pdis));
    }
    this->ui->route->append(QString(" %1 ").arg(routeName[way.size()-1]));
    this->ui->route->append(QString("The total distance is %1").arg(this->dis));
    this->v=baseV[this->transportation]-this->density[transportation];
    this->ui->route->append(QString("The pre-cost time is： %1").arg((this->dis)/this->v));
    this->ui->route->show();

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
/*
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
*/
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


int negvator::isTimeToCall(QDateTime dt) {
    if(dt.date().dayOfWeek()>=1&&dt.date().dayOfWeek()<=5) //工作日
    {
        if((dt.time()>QTime(7,20,0)&&dt.time()<QTime(7,40,0))||(dt.time()>QTime(8,10,0)&&dt.time()<QTime(8,15,0))||(dt.time()>QTime(9,30,0)&&dt.time()<QTime(9,55,0))||(dt.time()>QTime(11,55,0)&&dt.time()<QTime(12,15,0))||(dt.time()>QTime(16,20,0)&&dt.time()<QTime(16,55,0))||(dt.time()>QTime(20,45,0)&&dt.time()<QTime(21,5,0)))
            return 1;
        if((dt.time()>QTime(7,40,0)&&dt.time()<QTime(8,10,0))||(dt.time()>QTime(9,55,0)&&dt.time()<QTime(10,5,0))||(dt.time()>QTime(11,55,0)&&dt.time()<QTime(12,15,0))||(dt.time()>QTime(13,30,0)&&dt.time()<QTime(13,50,0))||(dt.time()>QTime(18,25,0)&&dt.time()<QTime(18,40,0))||(dt.time()>QTime(18,55,0)&&dt.time()<QTime(19,15,0))||(dt.time()>QTime(21,55,0)&&dt.time()<QTime(22,15,0)))
            return 2;
        else
            return 0;

    }
    else//周末
    {    if((dt.time()>QTime(7,40,0)&&dt.time()<QTime(8,10,0))||(dt.time()>QTime(9,55,0)&&dt.time()<QTime(10,5,0))||(dt.time()>QTime(11,55,0)&&dt.time()<QTime(12,15,0))||(dt.time()>QTime(13,30,0)&&dt.time()<QTime(13,50,0))||(dt.time()>QTime(18,25,0)&&dt.time()<QTime(18,40,0))||(dt.time()>QTime(18,55,0)&&dt.time()<QTime(19,15,0))||(dt.time()>QTime(21,55,0)&&dt.time()<QTime(22,15,0)))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return -1;
}

void negvator::checkTime() {
    QDateTime dt=this->time;
    int nowDensity=isTimeToCall(dt);
    if (nowDensity==0) {
        //emit judge_time();
        roadCondition_slot(0);
    }else if(nowDensity==1)
    {
        roadCondition_slot(1);
    }else if(nowDensity==2)
    {
        roadCondition_slot(2);
    }
}
void negvator::roadCondition_slot(int color)
{
    qDebug()<<"color "<<color;
    QPen p(Qt::red,25);
    if(color==0)
    {
        p.setColor(Qt::green);
    }else if(color==1)
    {
        p.setColor(Qt::yellow);
    }else if(color==2)
    {
        p.setColor(Qt::red);
    }
    for(int i=0;i<roadCondition.size();i++)
    {
        if(roadCondition[i]->scene()==nullptr)
        {
            roadCondition[i]->setPen(p);
            scene->addItem(roadCondition[i]);
        }else
        {
            scene->removeItem(roadCondition[i]);
            roadCondition[i]->setPen(p);
            scene->addItem(roadCondition[i]);
        }
    }
}

void negvator::setNowTime()
{
    this->ui->nowTimeEdit->setDateTime(QDateTime::currentDateTime());
    this->time=QDateTime::currentDateTime();
}


void negvator::on_toChat_clicked()
{
    ChatClient *chat=new ChatClient;
    chat->id=this->account;
    chat->show();

}

