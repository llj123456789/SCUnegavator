#include "chatclient.h"
#include "ui_chatclient.h"
#include "ui_tip.h"
#include<QRandomGenerator>


ChatClient::ChatClient(int account,tip* tips,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatClient)
{
    ui->setupUi(this);
    m_tip=tips;
    setWindowFlags(Qt::FramelessWindowHint);
    canChat=false;
    canJoin=false;
    isRoot=false;
    connected=false;
    this->id=account;

}

ChatClient::~ChatClient()
{
    delete ui;
}

void ChatClient::InitSocket()
{

    socket->abort();
    //socket->setProxy(QNetworkProxy::NoProxy);
    if(canJoin==true)
        socket->connectToHost(serverAdress,port);
    if(socket->waitForConnected(1000))
    {
        this->ui->notice->setText("连接服务器成功！请大家合理交流，不发表违背社会主义核心价值观的不当!联系管理员QQ2041584846");
        qDebug()<<"连接服务器成功！";
    }
    else
    {
        qDebug()<<("连接失败，请检查IP地址和端口！");
        if(canJoin==false)
            this->ui->notice->setText("连接失败，您已被加入黑名单！申诉或更多信息请联系管理员QQ2041584846");
        else
            this->ui->notice->setText("连接失败，请检查网络是否正常，防火墙是否正常！联系管理员QQ2041584846");
    }

//    connect(socket,SIGNAL(connected()),this,SLOT(connected_Slot()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connected=true;
}
void ChatClient::connectChat()
{
    //连接服务器数据库判断用户状态
    SQL sql;
    sql.connection();
    if(sql.sql(QString("SELECT canchat,canjoin,isroot FROM users WHERE account = %1 ").arg(id)))
    {
        if(sql.next())
        {
            qDebug()<<sql.value(0)<<" %% "<<sql.value(1);

            if(sql.value(0)=="True")
            {
                canChat=true;
            }else canChat=false;
            if(sql.value(1)=="True")
            {
                canJoin=true;
            }else canJoin=false;
            if(sql.value(2)=="True")
            {
                isRoot=true;
            }else isRoot=false;
        }
    }sql.close();




    this->ui->idEdit->setText(QString("id : %1").arg(id));
    this->ui->comment->setStyleSheet("background-image:url(:/new/prefix1/resource/chat.jpg);\n"
                                     "background-position:center;\n"
                                     "background-attachment:fixed;\n"
                                     "background-repeat:none;\n"

                                     );

    setWindowFlag (Qt::WindowCloseButtonHint, false);//去掉窗口右上角的叉叉

    socket=new QTcpSocket;
    serverAdress=QHostAddress("121.36.19.243");
    port=9999;
    InitSocket();
}

void ChatClient::send()
{
    QString content=QString("%1:").arg(id)+this->ui->editor->toPlainText();
    this->ui->editor->clear();
    QByteArray data=content.toUtf8();
    int a;
    a=(socket->write(data));
    if(socket->waitForBytesWritten())
    {
        qDebug()<<"send succ";
    }
    else
    {
        qDebug()<<"send errro";qDebug()<<a;
    }
}

void ChatClient::on_send_clicked()
{
    if(canChat==true)
        send();
}

void ChatClient::readyRead_slot()
{

    QString recv=socket->readAll();
    QStringList data=recv.split("@@");
    QString CMD=data[0];
    qDebug()<<CMD;
    if(CMD=="FORBIDOKNOWTIME")
    {
        canChat=false;
        this->ui->notice->setText("你已被禁言你已被禁言你已被禁言你已被禁言你已被禁言你已被禁言你已被禁言");
    }else if(CMD=="ALLOWOKNOWTIME")
    {
        canChat=true;
        canJoin=true;
    }else if(CMD=="CLSOKNOWTIME")
    {
        this->ui->comment->clear();
    }else if(CMD=="CHANGENOTICEOKNOWTIME")
    {
        QString tips=data[1];
        this->ui->notice->setText(tips);
    }else if(CMD=="QUITOKNOWTIME")
    {
        this->socket->write(QString("EXITNOWTIME").toUtf8());
        this->socket->disconnectFromHost();
        this->close();
        delete this;
    }
    else
    {
        if(recv.contains("time:"))
        {
            QString nowid=recv.split(':')[0];
            qDebug()<<nowid;
            nowid=QStringLiteral("<font color = gray >%4 </font>").arg(nowid);
            QString mes=(recv.split(':')[1]).split("time:")[0];
            qDebug()<<mes;
            mes=QStringLiteral("<strong><font color = black >  %4  </font></strong>").arg(mes);
            QString t=recv.split("time:")[1];
            qDebug()<<t;
            t=QStringLiteral("<font color = orange > %4</font><").arg(t);
            if(isRoot)
            {
                t=QStringLiteral("<font color=green>【管理员】</font>")+nowid+mes+t;

            }else

            {
                t=nowid+mes+t;
            }

            ui->comment->append(t);
            m_tip->ui->hint->clear();
            m_tip->ui->hint->append(t);
            m_tip->show();
            m_tip->raise();
        }
        else
        {

            ui->comment->append("系统通知: "+recv);
            m_tip->ui->hint->clear();
            m_tip->ui->hint->append("系统通知: "+recv);
            m_tip->show();
            m_tip->raise();
        }

    }


}

void ChatClient::bye()
{
    socket->write(QString("EXITNOWTIME").toUtf8());
    if(socket->waitForBytesWritten())
    {
        this->socket->disconnectFromHost();
    }
    delete socket;
    this->close();
    delete this;
}

void ChatClient::on_pushButton_clicked()//close聊天室
{
    this->close();
}


void ChatClient::on_cl_clicked()
{
    connectChat();
}


void ChatClient::on_tc_clicked()
{
    socket->write(QString("EXITNOWTIME").toUtf8());
    if(socket->waitForBytesWritten())
    {
        this->socket->disconnectFromHost();
    }
    this->ui->notice->setText("聊天室已经退出!聊天室已经退出!联系管理员QQ2041584846");

}

