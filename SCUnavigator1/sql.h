#ifndef SQL_H
#define SQL_H

#include<QTcpSocket>

class SQL
{
public:
    SQL(QHostAddress adress=QHostAddress("121.36.19.243"),quint16 p=9998);
    ~SQL(){
        delete this->db;
    };
    int sql(QString); //返回结果代表得到的结果数量
    bool isConnection;
    bool close();
    bool connection(QHostAddress adress=QHostAddress("121.36.19.243"),quint16 p=9998);
    QString value(int);
    int next();//返回当前结果参数数量;


private:
    int pos;//当前指向几行数据
    int num;//当前总共有几行数据
    QStringList nowValue;
    QStringList values;
    QHostAddress serverAddress;
    QTcpSocket* db;
    quint16 dbp;


};

#endif // SQL_H
