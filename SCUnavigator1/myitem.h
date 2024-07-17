#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include<QGraphicsSceneMouseEvent>
#include<QFile>
#include<QDialog>
#include<QDir>
#include"road_node.h"
#include"infowin.h"
#include<iostream>
#include<queue>
#include<deque>

class MyItem:public QGraphicsPixmapItem
{

public:
    MyItem(const QPixmap &pixmap):QGraphicsPixmapItem(pixmap){


    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event){

        if (event->button() == Qt::LeftButton) {
            // 这里处理鼠标左键点击事件

            qDebug()<<this->name;
            qDebug() << this->pos();
            qDebug()<<this->id;
            this->infowin=new InfoWin(id);
            this->infowin->show();

        }
        QGraphicsPixmapItem::mousePressEvent(event);
    }

    QString name;
    int id;
    int nowId=1;
    int aimId=1;
    int nextId=1;
    int nowSeq=0,aimSeq=0,nextSeq=0;
    InfoWin* infowin;


};



class ItemContainer
{

public:
    //route
    double distance=0;
    double density[3]; //密度；人流量;根据时间 and 天气
    double costTime=0;
    int transportation=0; //0 is foot ;1 is bicycle; 2 is school-bus
    double baseV[3];
    double v=0;//速度 m/min

    ItemContainer(){}
    vector<MyItem*> item;
    path *p[200];
    int num=0;

public:
    void clear(int n)
    {

        for(int i=0;i<n;i++)
        {
            delete item[i];
        }
        item.clear();
    }
    void readNodeLink()
    {
        //read
        QFile f(":/new/prefix1/resource/Info/test.txt");
        QString s;
        QTextStream Input(&f);
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"cannot open";
            exit(0);
        }
        while(!Input.atEnd())
        {
            s=Input.readLine();
            p[num]=new path();
            for(int i=0;i<s.length();i++)
            {
                if(s[i]==' ')
                {
                    continue;
                }
                else if(s[i]=='\n')
                {
                    break;
                }else
                {
                    if(i!=0)
                    {
                        QString temp="";
                        while(i<s.length()&&s[i]!=' '&&s[i]!='\n')
                        {
                            temp.append(s[i]);
                            i++;
                        }
                        if(temp!="")
                            (p[num]->turn_to).push_back(temp.toInt());
                    }else
                    {
                        QString temp="";
                        while(i<s.length()&&s[i]!=' '&&s[i]!='\n')
                        {
                            temp.append(s[i]);
                            i++;
                        }
                        if(temp!="")
                            p[num]->id=temp.toInt();
                    }
                }
            }
            num++;
        }
        f.close();

        QFile ff(":/new/prefix1/resource/Info/node.txt");
        QTextStream InputN(&ff);
        if(!ff.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"cannot open";
            exit(0);
        }
        int nowId=0;
        while(!InputN.atEnd())
        {
            s=InputN.readLine();
            for(int i=0;i<s.length();i++)
            {
                if(s=="")
                    break;
                if(s.length()<=1)
                    break;
                while(i!=s.length()-1&&s[i]==' ') i++;
                if(i==s.length()-1)
                    break;
                if(i<s.length()-1)
                    i++;
                if(s[i]=='I')
                {
                    i+=5;
                    while(s[i]!=',')
                    {
                        i++;
                    }
                    i--;
                    int getId=0;
                    int len=0;
                    for(int j=i;j>=0;j--)
                    {
                        if(s[j]!=' ')
                        {
                            QString temp=s[j];
                            getId+=temp.toInt()*pow(10,len++);
                        }
                        else
                            break;
                    }
                    nowId=getId;
                }
                else if(s[i]=='N')
                {
                    i=i+8;
                    int getPos=0;
                    for(int j=0;j<num;j++)
                    {
                        if(p[j]->id==nowId)
                        {
                            getPos=j;
                            break;
                        }
                    }
                    QString tempName;
                    int len=0;
                    while(s[i]!='"')
                    {
                        qDebug()<<s[i];
                        tempName.append(s[i]);
                        i++;
                        len++;
                    }
                    p[getPos]->name=tempName;
                }
                else if(s[i]=='X')
                {
                    i+=4;
                    while(s[i]!='.')
                    {
                        i++;
                    }
                    i--;

                    int getX=0;
                    int len=0;
                    for(int j=i;j>=0;j--)
                    {
                        if(s[j]!=' ')
                        {
                            QString tempNum;
                            tempNum=s[j];
                            getX+=tempNum.toInt()*pow(10,len++);
                        }
                        else
                            break;
                    }
                    int getPos=0;
                    for(int j=0;j<num;j++)
                    {
                        if(p[j]->id==nowId)
                        {
                            getPos=j;
                            break;
                        }
                    }
                    p[getPos]->x=getX*(6687.0/4807.0)*0.9855;
                }
                else if(s[i]=='Y')
                {
                    i+=4;
                    while(s[i]!='.')
                    {
                        i++;
                    }
                    i--;
                    int getY=0;
                    int len=0;
                    for(int j=i;j>=0;j--)
                    {
                        if(s[j]!=' ')
                        {
                            QString tempNum;
                            tempNum=s[j];
                            getY+=tempNum.toInt()*pow(10,len++);
                        }
                        else
                            break;
                    }
                    int getPos=0;
                    for(int j=0;j<num;j++)
                    {
                        if(p[j]->id==nowId)
                        {
                            getPos=j;
                            break;
                        }
                    }
                    p[getPos]->y=getY*(4200.0/3450.0)*1.105;

                }else
                {
                    break;
                }

            }
        }


        num--;

    }



    const long long INF = 0x3f3f3f3f3f3f3f3fLL;

     static const int N = 3e5+2;


    class edge{//map
    public:
        int from=0, to=0;
        long long weight=0;
        edge(int f, int t, int w): from(f), to(t), weight(w) {}
    };

    deque <edge> e[N] ;//save map

    deque <path> school;

    deque <int> way;//storeid

    class s_node{//point
    public:
        int id=0;
        long long n_dis=0;
        s_node(int i, long long d): id(i), n_dis(d) {}
        bool operator < (const s_node &a)const{
            return n_dis > a.n_dis;
        }
    };

    //int n=0, m=0;
    int pre[N] ={};//save the path by recording the previous point

    //path_print
    void print_path(int s, int t){
        if(s == t){
            way.push_back(s);
            return ;
        }
        print_path(s, pre[t]);
        way.push_back(t);
    }

    long long dis[N];//recode all the distance from random point to starting point

    void dijkstra(int s, int de){
        /*int s=1;*/


        bool done[N];
        for(int i=1;i<=N-1;i++){//initialization
            dis[i] = INF;
            done[i] = false;
        }
        dis[s] = 0;//distance from starting point to starting point is zero
        priority_queue <s_node> Point;//save point information
        Point.push(s_node(s, dis[s]));//initialize starting point

        while(!Point.empty()){
            s_node next = Point.top();
            Point.pop();

            if(done[next.id] == true) continue;//have found its shortest path
            else done[next.id] = true;

            for(int i=0;i<e[next.id].size();i++){
                edge next_neighbor = e[next.id][i];
                if(done[next_neighbor.to] == true) continue; //"next"'s neighbor has been found

                if(dis[next_neighbor.to] > next_neighbor.weight + next.n_dis){

                    dis[next_neighbor.to] = next_neighbor.weight + next.n_dis;
                    Point.push(s_node(next_neighbor.to, dis[next_neighbor.to]));
                    pre[next_neighbor.to] = next.id;
                }
            }
        }
    }



    void transfer(int s){
        for(int i=0;i<num;i++){
            if(p[i]->getIsUsed()){

                int from =p[i]->getid();

                for(int j=0;j<(p[i])->turn_to.size();j++){
                    int to = p[i]->turn_to[j];
                    int seq=0;
                    for(int k=0;k<num;k++)
                    {
                        if(p[i]->turn_to[j]==p[k]->id)
                            seq=k;
                    }
                    double weight = abs(*p[i] - *p[seq]);

                    qDebug()<<"i: "<<i<<"sqe: "<<seq<<"  from"<<from<<"to"<<to<<"weght"<<weight;

                    e[from].push_back(edge(from, to, weight));
                    e[to].push_back(edge(to, from, weight));
                }
            }
        }

        return ;
    }

    /////////////////////









};

#endif // MYITEM_H
