#include "chatclient.h"
#include "ui_chatclient.h"

ChatClient::ChatClient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatClient)
{
    ui->setupUi(this);
    canChat=false;
    canJoin=false;
    //连接服务器数据库判断用户状态
    dbp=9998;
    db=new QTcpSocket;
    db->connectToHost(QHostAddress("121.36.19.243"),dbp);
    if(db->waitForConnected(1000))
    {
        db->write((QString("SELECT canchat,canjoin FROM users WHERE id = %1 ").arg(id)).toUtf8());
        if(db->waitForBytesWritten())
        {
            if(db->waitForReadyRead())
            {
                QString recv=db->readAll();
                QStringList sl=recv.split('&');
                if(sl[0]=="true")
                {
                    canChat=true;
                }else canChat=false;
                if(sl[1]=="true")
                {
                    canJoin=true;
                }else canJoin=false;
            }

        }

    }s->close();



    this->ui->idEdit->setText(QString("id : %1").arg(id));
    this->ui->comment->setStyleSheet("background-image:url(:/new/prefix1/resource/chat.jpg);\n"
                                   "background-attachment:fixed;\n"
                                   "background-repeat:none;\n"
                                   );
    //"background-position:center"

    setWindowFlag (Qt::WindowCloseButtonHint, false);//去掉窗口右上角的叉叉

    socket=new QTcpSocket;
    serverAdress=QHostAddress("121.36.19.243");
    port=9999;
    InitSocket();
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
    if(CMD=="FORBIDOKNOWTIME")
    {
        canChat=false;
        this->ui->notice->setText("你已被禁言你已被禁言你已被禁言你已被禁言你已被禁言你已被禁言你已被禁言")；
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
    }
    ui->comment->append(socket->readAll());

}



void ChatClient::on_pushButton_clicked()//退出聊天室
{
    this->socket->close();
    delete this->socket;
    this->close();
    delete this;
}

