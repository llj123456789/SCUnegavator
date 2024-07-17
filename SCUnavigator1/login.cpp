#include "login.h"

#include "ui_login.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/resource/icon.png"));
    setWindowTitle("Login");
    //编辑框添加图标
    QAction *searchAction = new QAction(ui->account);
    searchAction->setIcon(QIcon(":/new/prefix1/resource/login.png"));
    ui->account->addAction(searchAction,QLineEdit::LeadingPosition );//编辑框左侧

    searchAction = new QAction(ui->password);
    searchAction->setIcon(QIcon(":/new/prefix1/resource/pass.png"));
    ui->password->addAction(searchAction,QLineEdit::LeadingPosition );//编辑框左侧


    this->ui->headText->setStyleSheet("");
    this->ui->welcome->setStyleSheet("background:transparent");
    // 加载驱动
    //db = QSqlDatabase::addDatabase("QSQLITE");
    // 建立链接

    //db.setDatabaseName("./SQLite/users.db");
    qDebug()<<"  kkk";
    if(db.connection()==false)
    {
        qDebug()<<"Error: Failed to connect database.";
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
    //QSqlQuery sql_query=QSqlQuery(this->db);
    QString qs = QString("SELECT * from users where account = %1 and password='%2';").arg(account0).arg(password0);
    db.sql(qs);
    qDebug()<<qs;
    if(db.isConnection)
    {

    }else
    {
        this->ui->message->setText(QString("用户或密码错误"));
        return;
    }
    if(db.next()==0)
    {
        this->ui->message->setText(QString("用户或密码错误"));
    }else
    {
        this->account=account0;
        this->password=password0;
        this->close();
        this->neg=new negvator;
        neg->account=this->account;
        //初始化chat
        neg->tips=new tip;
        neg->chat=new ChatClient(account,neg->tips);
        //断开数据库连接
        //QString connection=db.connectionName();
        //db.~QSqlDatabase();
        //QSqlDatabase::removeDatabase(connection);
        //显示主页面
        db.sql(QString("update users set online = true where account = %1").arg(this->account));

        db.close();

        neg->show();

    }
}


void login::on_pushButton_2_clicked()//注册
{
    int account0=(this->ui->account->text()).toInt();
    QString password0=this->ui->password->text();
    //QSqlQuery sql_query=QSqlQuery(this->db);
    QString qs;
    qs=QString("SELECT * FROM users where account = %1").arg(account0);
    db.sql(qs);
    qDebug()<<db.isConnection;
    if(db.isConnection)
    {
        if(db.next())
        {
            this->ui->message->setText(QString("用户'%1'已经存在").arg(account0));
        }else
        {
            qs = QString("insert into users(account,password) values(%1,'%2');").arg(account0).arg(password0);
            if(db.sql(qs)!=-1){     //如果插入数据成功
                this->ui->message->setText(QString("用户'%1'注册成功").arg(account0));

            }else{
                this->ui->message->setText(QString("用户'%1'注册失败1").arg(account0));
            }
        }
    }else
    {
        this->ui->message->setText(QString("用户'%1'注册失败0").arg(account0));
    }


}

