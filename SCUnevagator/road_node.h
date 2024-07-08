#ifndef _nodeCLASS
#define _nodeCLASS
#include<iostream>
#include<string>
#include<QString>
#include<math.h>
#include<deque>
using namespace std;

struct Infor
{
    QString open;
    QString close;
    QString book_way;
};//结构体infor显示建筑的开关门时间和预约方式

class node
{
public:
   // static int MyCounter;//静态数据成员代表是节点
public:
    double x;
    double y;
    int id;
    QString name;
public:
    node(){
        x=0;
        y=0;
        id=0;
     //   MyCounter++;//每当生成一个节点时count计数器会自动加一
    }
    node(int id,double x,double y,QString name){
        this->id=id;
        this->x=x;
        this->y=y;
        this->name=name;
     //   MyCounter++;
    }
    node(const node &Node)
    {
        this->x=Node.x;
        this->y=Node.y;
        this->id=Node.id;
        this->name=Node.name;
     //   MyCounter++;
    }
    //~node(){MyCounter--;}//每当析构一个节点，count计数器会自动减一
    double distance(const node &Node1,const node &Node2)
    {
        return sqrt(pow(Node1.x-Node2.x,2)+pow(Node1.y-Node2.y,2));
    }
    double operator-(const node &Node1)//重载减号，“A地-B地”代表其距离
    {
        node tem;
        tem.x=this->x;
        tem.y=this->y;
        tem.id=this->id;
        tem.name=this->name;
        return distance(tem,Node1);
    }
};
//int node::MyCounter=0;//类外的静态数据成员代表地图一共有多少个节点

class path:public node
{
public:
    deque<int>turn_to;
public:
    bool IsUsed;
    bool IsCrow;
public:
    path(){
        IsUsed=true;
        IsCrow=false;
    }
    path(int id,QString name,double x,double y):node(id,x,y,name){
        IsCrow=false;
        IsUsed=true;
    }
    path(const path& Path)
    {
        this->IsUsed=Path.IsUsed;
        this->IsCrow=Path.IsCrow;
        for(int i=0;i<Path.turn_to.size();i++){
            this->turn_to.push_back(Path.turn_to[i]);
        }
        this->x=Path.x;
        this->y=Path.y;
        this->id=Path.id;
        this->name=Path.name;
    }
    ~path(){}

    void which_to_turn(deque<int> a){
        for(int i=0;i<a.size();i++){
            this->turn_to.push_back(a[i]);
        }
    }
    //向该函数传入一个双向队列，函数会自动给对象的队列复制该队列

    void ban()
    {
        this->IsUsed=false;
    }
    //若封路，则调用此函数来给道路“是否启用”参数置零

    void jam()
    {
        this->IsCrow=true;
    }
    //若拥堵，则调用此函数给道路“拥挤”参数置一

    bool getIsUsed()
    {
        return IsUsed;
    }
    //返回“是否启用”的真值

    bool getIsCrow()
    {
        return IsCrow;
    }
    //返回“是否拥挤”的真值

    int getid()
    {
        return id;
    }
    //返回id号

    QString getname()
    {
        return name;
    }
    //返回名字

};

class arch:public path{
private:
    Infor information;
    bool is_dest;
public:
    arch(){
        Infor tem;
        tem.book_way="error";
        tem.close="error";
        tem.open="error";
        information=tem;
        is_dest=false;
    }
    arch(int id,double x,double y,QString name,Infor information):path(id,name,x,y){
        this->information=information;
        is_dest=false;
    }
    arch(const arch& arch)
    {
        this->x=arch.x;
        this->y=arch.y;
        this->id=arch.id;
        this->name=arch.name;
        this->IsCrow=arch.IsCrow;
        this->IsUsed=arch.IsUsed;
        this->information=arch.information;
    }
    ~arch(){}
    void set_info(Infor a)
    {
        this->information=a;
    }
    void showInfo()//三种实现————每个建筑都show但是show内判断bool，析构函数里show，主程中show
    {

        /*
        cout<<this->name<<endl;
        cout<<this->information.open<<"~"<<this->information.close<<endl;
        cout<<this->information.book_way<<endl;
*/
    }
};

#endif
