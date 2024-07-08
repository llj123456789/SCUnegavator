#include "infowin.h"
#include "ui_infowin.h"

InfoWin::InfoWin(int idtemp,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfoWin)
{
    ui->setupUi(this);
    this->id=idtemp;
    lineUrl=new QLineEdit;
    lineUrl->setVisible(false);
    lineUrl->setReadOnly(true);

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
            this->webImage=query.value(6).toString();

            lineUrl->setText(web);

            connect(lineUrl,SIGNAL(returnPressed()),this,SLOT(loadWeb()));
            connect(this->ui->mainPhoto,&QAction::triggered,this,&InfoWin::showWebPhoto);
            connect(this->ui->web,&QAction::triggered,this,&InfoWin::showWebInfo);
            connect(this->ui->position,&QAction::triggered,this,&InfoWin::showWebPosition);

            webWidget=new QAxWidget;
            //设置ActiveX控件为IEMicrosoft Web Browser,设置ActiveX控件的id，使用UUID
            //此处的{8856F961-340A-11D0-A96B-00C04FD705A2}就是Microsoft Web Browser控件的UUID
            webWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
            webWidget->setObjectName(QString::fromUtf8("webWidget"));
            webWidget->setFocusPolicy(Qt::StrongFocus);//接收键盘焦点的方式：鼠标单击、Tab键
            webWidget->setProperty("DisplayAlerts",false); //不显示警告信息。
            webWidget->setProperty("DisplayScrollBars",true); // 显示滚动条


            this->ui->mainLayout->addWidget(lineUrl);
            this->ui->mainLayout->addWidget(webWidget);
            setLayout(this->ui->mainLayout);

            //setWindowState(Qt::WindowMaximized);
            //初始页面
            QString url=lineUrl->text().trimmed();
            webWidget->dynamicCall("Navigate(const QString&",url);





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
    QString url=lineUrl->text().trimmed();
    webWidget->dynamicCall("Navigate(const QString&",url);
}

void InfoWin::showWebPhoto()
{
    QString url=this->webImage;
    webWidget->dynamicCall("Navigate(const QString&",url);
}

void InfoWin::showWebInfo()
{
    QString url=this->web;
    webWidget->dynamicCall("Navigate(const QString&",url);
}

void InfoWin::showWebPosition()

{
    QString url=this->webInfo;
    webWidget->dynamicCall("Navigate(const QString&",url);
}
