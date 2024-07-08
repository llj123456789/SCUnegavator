#ifndef INFOWIN_H
#define INFOWIN_H
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include <QDialog>
#include<QLineEdit>
#include <QSqlError>
#include<ActiveQt/QAxWidget>
#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
class InfoWin;
}

class InfoWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfoWin(int id,QWidget *parent = nullptr); //定义id：0 is road information；

    ~InfoWin();
private slots:
    void loadWeb();
    void showWebPhoto();
    void showWebPosition();
    void showWebInfo();

private:
    Ui::InfoWin *ui;
public:
    QSqlDatabase db;
    QLineEdit *lineUrl;
    QAxWidget* webWidget;
    int id;
    QString name;
    QString photo;
    QString image;
    QString web;
    QString webImage;
    QString webInfo;

};

#endif // INFOWIN_H
