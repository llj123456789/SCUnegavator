#include"login.h"
#include"infowin.h"
#include <QApplication>
#include<QMovie>
#include<QLabel>
#include<QThread>
#include<QSplashScreen>
#include<QDateTime>



////////////////////





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen* splash=new QSplashScreen();
    QLabel label(reinterpret_cast<QWidget*>(splash));
    //label.resize(1200,800);
    splash->resize(1000,700);
    splash->move(10,10);
    QMovie mv(":/new/prefix1/resource/start.gif");
    label.setMovie(&mv);
    mv.start();
    splash->show();
    splash->setCursor(Qt::BlankCursor);

    for (int i = 0; i < 8000; i += mv.speed()) {
        a.processEvents(); //防止界面出现无响应
        QThread::msleep(mv.speed());
    }
    splash->close();

    //connnect database



    login *logtemp=new login;
    logtemp->show();

    return a.exec();
}
