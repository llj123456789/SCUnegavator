#ifndef LOGIN_H
#define LOGIN_H
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include <QDialog>
#include <QSqlError>
#include"negvator.h"
#include"sql.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
public:
    int account;
    QString password;
    negvator *neg;
    SQL db;
    //else information
};

#endif // LOGIN_H
