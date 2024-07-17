#include "delicious.h"
#include "ui_delicious.h"

delicious::delicious(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::delicious)
{
    ui->setupUi(this);
}

delicious::~delicious()
{
    delete ui;
}

void delicious::on_pushButton_clicked()
{
    //Widget *Ui::negvator = new Widget();//新建父类对象
    this->close();
    neg->show();
}
