#include "login.h"

#include "ui_login.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    this->ui->welcome->setStyleSheet("background:transparent");
    // 加载驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 建立链接
    db.setDatabaseName("./SQLite/users.db");
    if(!db.open())
    {
        qDebug()<<"Error: Failed to connect database."<<db.lastError().text();
    }else
    {
        qDebug() << "Succeed to connect database." ;
    }

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()//登录
{
    int account0=(this->ui->account->text()).toInt();
    QString password0=this->ui->password->text();
    QSqlQuery sql_query=QSqlQuery(this->db);
    QString qs = QString("select * from info where account = %1 and password='%2';").arg(account0).arg(password0);
    qDebug()<<qs;
    if(sql_query.exec(qs))
    {

    }else
    {
        this->ui->message->setText(QString("用户或密码错误"));
        return;
    }
    if(!sql_query.next())
    {
        this->ui->message->setText(QString("用户或密码错误"));
    }else
    {
        this->account=account0;
        this->password=password0;
        this->close();
        this->neg=new negvator;
        neg->account=this->account;
        //断开数据库连接
        QString connection=db.connectionName();
        db.~QSqlDatabase();
        QSqlDatabase::removeDatabase(connection);
        //显示主页面
        neg->show();
    }
}


void login::on_pushButton_2_clicked()//注册
{
    int account0=(this->ui->account->text()).toInt();
    QString password0=this->ui->password->text();
    QSqlQuery sql_query=QSqlQuery(this->db);
    QString qs;
    qs=QString("SELECT * FROM info where account = %1").arg(account0);
    if(sql_query.exec(qs))
    {
        if(sql_query.next())
        {
            this->ui->message->setText(QString("用户'%1'存在").arg(account0));
        }else
        {
            qs = QString("insert into info(account,password) values('%1','%2');").arg(account0).arg(password0);
            if(sql_query.exec(qs)){     //如果插入数据成功
                this->ui->message->setText(QString("用户'%1'注册成功").arg(account0));

            }else{
                this->ui->message->setText(QString("用户'%1'注册失败").arg(account0));
            }
        }
    }else
    {
        this->ui->message->setText(QString("用户'%1'注册失败").arg(account0));
    }


}

