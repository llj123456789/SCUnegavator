#ifndef USER_H
#define USER_H

#include <QDialog>
#include"negvator.h"
#include"set.h"
namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(int account,QWidget *parent = nullptr);
    ~User();
    void setTempNeg(negvator * p)
    {
        this->tempNeg=p;
    }
    negvator* getTempNeg()
    {
        return this->tempNeg;
    }

private slots:
    void on_help_clicked();

    void on_setting_clicked();

public:
     int account;

private:
    Ui::User *ui;
    negvator *tempNeg;
    QImage *image;
    QString imageFile;
    QImage *back;

};

#endif // USER_H
