#include "set.h"
#include "ui_set.h"

Set::Set(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Set)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/resource/icon.png"));
    setWindowTitle("设置");
    this->ui->lineEdit->setStyleSheet("background:transparent");
    this->ui->lineEdit_2->setStyleSheet("background:transparent");
    this->ui->settingFirst->setStyleSheet("background:transparent");
}

Set::~Set()
{
    delete ui;
}

void Set::on_comboBox_2_activated(int index)
{

}


void Set::on_roadColor_activated(int index)//路径颜色
{
    if(index==0)
    {
        this->neg->roadPen->setColor(Qt::blue);
    }
    if(index==1)
    {
        this->neg->roadPen->setColor(Qt::black);
    }
    if(index==2)
    {
        this->neg->roadPen->setColor(Qt::red);
    }
    if(index==3)
    {
        this->neg->roadPen->setColor(Qt::yellow);
    }
}


void Set::on_pushButton_3_clicked()
{
    this->close();
    this->neg->show();
}

