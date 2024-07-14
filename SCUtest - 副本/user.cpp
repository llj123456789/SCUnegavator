#include "user.h"
#include "ui_user.h"

User::User(int accountTemp,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/new/prefix1/resource/icon.png"));
    setWindowTitle("我的");
    account=accountTemp;
    QString id=QString("%1").arg(this->account);
    qDebug()<<"user account"<<account;
    this->ui->id->setText(id);

    this->image = new QImage();
    this->imageFile=":/new/prefix1/resource/head.png";
    image->load(imageFile);
    QGraphicsScene *scene=new QGraphicsScene;
    //add node;
    scene->addPixmap(QPixmap::fromImage(*image));

    this->back = new QImage(":/new/prefix1/resource/map/back.png");
    scene=new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*back));
    ui->background->setScene(scene);
    ui->background->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->background->show();
}

User::~User()
{
    delete ui;
}

void User::on_help_clicked()
{

    this->close();
    this->getTempNeg()->show();
    delete this;

}


void User::on_setting_clicked()
{
    this->close();
    Set* setting=new Set;
    setting->neg=this->getTempNeg();
    setting->show();

}

