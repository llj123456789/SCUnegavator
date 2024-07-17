#include "tip.h"
#include "ui_tip.h"
#include<QScreen>

tip::tip(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::screen)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect = screen->availableGeometry();
    int x=rect.size().width();
    int y=rect.size().height();
    int deltax=this->frameGeometry().width();
    int deltay=this->frameGeometry().height();
    this->move(x-deltax,y-deltay);
    this->ui->hint->clear();
    this->raise();
}

tip::~tip()
{
    delete ui;
}

void tip::on_pushButton_clicked()
{
    this->close();
}

