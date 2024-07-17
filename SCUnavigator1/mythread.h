#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>
#include<cmath>
#include"negvator.h"
class MYTHREAD
{
public:
    MYTHREAD();

signals:
    void g1(int,double,double);
    void g2(int,double,double);

};

#endif // MYTHREAD_H
