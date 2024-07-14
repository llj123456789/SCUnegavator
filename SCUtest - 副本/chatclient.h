#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QDialog>
#include<QWidget>
#include<QHostAddress>
#include<QTcpSocket>
#include<QTimer>
#include<QNetworkProxy>


namespace Ui {
class ChatClient;
}

class ChatClient : public QDialog
{
    Q_OBJECT

public:
    explicit ChatClient(QWidget *parent = nullptr);
    void InitSocket();
    void send();

    ~ChatClient();
    //读取数据库值;
    QStringList getValue(QTcpSocket *database)
    {
        QString recv=database->readAll();
        QStringList sl=recv.split("@sql@");
        return sl;
    }

    int id;
    //当前聊天室状态:
    bool canChat;
    bool canJoin;

private slots:
    void on_send_clicked();
    void readyRead_slot();


    void on_pushButton_clicked();

private:
    Ui::ChatClient *ui;
    QTcpSocket* socket;
    QHostAddress serverAdress;
    quint16 port;
    quint16 dbp;
    QTcpSocket *db;
};

#endif // CHATCLIENT_H
