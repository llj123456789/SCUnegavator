#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QDialog>
#include<QWidget>
#include<QHostAddress>
#include<QTcpSocket>
#include<QTimer>
#include<QNetworkProxy>
#include"sql.h"
#include"tip.h"



namespace Ui {
class ChatClient;
}

class ChatClient : public QDialog
{
    Q_OBJECT

public:
    explicit ChatClient(int account,tip* tips,QWidget *parent = nullptr);
    void InitSocket();
    void send();
    void connectChat();
    void bye();
    ~ChatClient();


    int id;
    //当前聊天室状态:
    bool canChat;
    bool canJoin;
    bool isRoot;
    bool connected;
private slots:
    void on_send_clicked();
    void readyRead_slot();

    void on_pushButton_clicked();

    void on_cl_clicked();

    void on_tc_clicked();

private:
    Ui::ChatClient *ui;
    QTcpSocket* socket;
    QHostAddress serverAdress;
    quint16 port;
    tip* m_tip;

};

#endif // CHATCLIENT_H
