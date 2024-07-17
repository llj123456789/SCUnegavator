#include "sql.h"

SQL::SQL(QHostAddress address,quint16 p)
{
    this->serverAddress=address;
    this->dbp=p;
    db=new QTcpSocket;
    nowValue=QStringList();
    values=QStringList();
    pos=0;
    num=0;

}

int SQL::sql(QString query)
{
    if(isConnection)
    {
        db->write(query.toUtf8());
        db->waitForBytesWritten(500);
        if(db->waitForReadyRead(500))
        {
            QString recv=db->readAll();
            if(recv=="SCU")///////////////////////pay attention
            {
                this->num=0;
                this->pos=0;
                return 0;
            }
            if(recv=="ERRO")
            {
                this->num=0;
                this->pos=0;
                return -1;
            }
            values=QString(recv).split("\n");
            this->num=values.length(); //
            this->pos=0;
            return this->num;
        }else
        {
            return -1;
        }
    }else
        return -1;
}

int SQL::next()
{
    if(pos<num)
    {
        nowValue=values[pos].split("@sql@");
        pos++;
        return nowValue.length();
    }else
    {
        return 0;
    }
}


QString SQL::value(int i)
{
    return nowValue[i];
}

bool SQL::close()
{
    db->write(QString("EXITNOWTIME").toUtf8());
    if(db->waitForBytesWritten())
    {

    }
    db->disconnectFromHost();
    if(db->waitForDisconnected())
    {
        isConnection=false;
        return true;
    }else return false;
}

bool SQL::connection(QHostAddress address,quint16 p)
{
    delete db;
    db=new QTcpSocket;
    qDebug()<<"here";
    this->serverAddress=address;
    this->dbp=p;
    qDebug()<<"here";
    this->db->connectToHost(serverAddress,dbp);
    qDebug()<<"here";
    nowValue=QStringList();
    values=QStringList();
    pos=0;
    num=0;
    qDebug()<<"here";
    if(db->waitForConnected())
    {
        //连接成功
        isConnection=true;
        return true;
    }else {
        isConnection=false;
        return false;
    }
}
