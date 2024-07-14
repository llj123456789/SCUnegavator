#include "infowin.h"
#include "ui_infowin.h"
#include<QThread>
InfoWin::InfoWin(int idtemp,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfoWin)
{
    ui->setupUi(this);
    this->id=idtemp;

    setWindowIcon(QIcon(":/new/prefix1/resource/icon.png"));

    webView=new QWebEngineView(this);

    qDebug()<<QString("now id is %1").arg(this->id);
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./SQLite/baseInfo.db");
    if(!db.open())
    {
        qDebug()<<"Error: Failed to connect database."<<db.lastError().text();
    }else
    {
        qDebug() << "Succeed to connect database." ;
    }
    QSqlQuery query(this->db);
    QString ask=QString("SELECT * from archi where id = %1").arg(this->id);
    qDebug()<<ask;
    if(query.exec(ask))
    {
        qDebug()<<"ask ok";
        if(query.next())
        {
            this->id=query.value(0).toInt();
            this->image=query.value(1).toString();
            this->name=query.value(2).toString();
            this->photo=query.value(3).toString();
            this->web=query.value(4).toString();
            this->webInfo=query.value(5).toString();
            this->webImageId=query.value(6).toString();
            setWindowTitle(QString("%1 信息").arg(this->name));

            //connect(lineUrl,SIGNAL(returnPressed()),this,SLOT(loadWeb()));
            connect(this->ui->mainPhoto,&QAction::triggered,this,&InfoWin::showWebPhoto);
            connect(this->ui->web,&QAction::triggered,this,&InfoWin::showWebInfo);
            connect(this->ui->position,&QAction::triggered,this,&InfoWin::showWebPosition);

            QStackedLayout *layout=new QStackedLayout(this->ui->frame);
            ui->frame->setLayout(layout);
            layout->addWidget(webView);
            //setWindowState(Qt::WindowMaximized);
            QThread::msleep(100); //休眠1ms;
            //初始页面
            QString url=this->webInfo;
            if (!url.isEmpty())
            {
                webView->load(url);

            }

            //webWidget->dynamicCall("Navigate(const QString&",url);





        }else
        {
            qDebug()<<"no such id \"error!!\"";
        }

    }else
    {
        //可创建erro窗口提示
        qDebug()<<db.lastError().text();
    }

}

InfoWin::~InfoWin()
{
    delete ui;
}

void InfoWin::loadWeb()
{
    QString url=this->web.trimmed();
    if (!url.isEmpty())
    {
        webView->load(url);

    }
}

void InfoWin::showWebPhoto()
{
    QString url="https://g7bzesqvqx.720yun.com/t/cd4jur4vvO0?scene_id="+this->webImageId;
    if (!url.isEmpty())
    {
        webView->load(url);

    }
}

void InfoWin::showWebInfo()
{
    QString url=this->web;
    if (!url.isEmpty())
    {
        webView->load(url);

    }
}

void InfoWin::showWebPosition()

{
    QString url=this->webInfo;
    if (!url.isEmpty())
    {
        webView->load(url);

    }
}
