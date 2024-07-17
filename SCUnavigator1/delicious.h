#ifndef DELICIOUS_H
#define DELICIOUS_H

#include <QWidget>
#include"negvator.h"//添加父类的头文件
namespace Ui {
class delicious;
}

class delicious : public QWidget
{
    Q_OBJECT

public:
    explicit delicious(QWidget *parent = nullptr);
    ~delicious();
    negvator* neg;

private slots:
    void on_pushButton_clicked();

private:
    Ui::delicious *ui;
};

#endif // DELICIOUS_H
