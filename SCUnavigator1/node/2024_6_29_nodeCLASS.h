#ifndef _nodeCLASS
#define _nodeCLASS
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

struct Infor
{
   string open;
   string close;
   string book_way;
};//结构体infor显示建筑的开关门时间和预约方式

class node
{
    public:
     static int counter;//静态数据成员代表是节点
    protected:
     double x;
     double y;
     int id;
     string name;
    public:
     node(){
        x=0;
        y=0;
        id=0;
        counter++;
     }
     node(int id,double x,double y,string name){
        this->id=id;
        this->x=x;
        this->y=y;
        this->name=name;
        counter++;
     }
     node(const node &Node)
     {
        this->x=Node.x;
        this->y=Node.y;
        this->id=Node.id;
        this->name=Node.name;
        counter++;
     }
     ~node(){counter--;}
     int get_node_id(){
     	 return this->id; 
	 }
     double distance(const node &Node1,const node &Node2)
     {
         return sqrt(pow(Node1.x-Node2.x,2)+pow(Node1.y-Node2.y,2));
     }
     double operator-(const node &Node1)//重载减号，A地-B地代表其距离
      {
         node tem;
         tem.x=this->x;
         tem.y=this->y;
         tem.id=this->id;
         tem.name=this->name;
         return distance(tem,Node1);
      } 
};
int node::counter=0;//类外的静态数据成员代表一共有多少个节点

class path:public node
{
   protected:
      bool IsUsed;
      bool IsCrow;
      node* nodenext;
      node* nodepre;
   public:
   	  static int path_counter;
      path(){
         IsUsed=true;
         IsCrow=false;
         nodenext=NULL;
         nodepre=NULL;
         path_counter++;
      }
      path(int id,double x,double y,string name,node* next,node* pre):node(id,x,y,name){
         this->nodenext=next;
         this->nodepre=pre;
         IsCrow=false;
         IsUsed=true;
         path_counter++;
      }
      path(const path& Path)
      {
         this->IsUsed=Path.IsUsed;
         this->IsCrow=Path.IsCrow;
         this->nodenext=Path.nodenext;
         this->nodepre=Path.nodepre;
         this->x=Path.x;
         this->y=Path.y;
         this->id=Path.id;
         this->name=Path.name;
         path_counter++;
      }
      ~path(){}

      void ban()
      {
         this->IsUsed=false;
      }
      void jam()
      {
         this->IsCrow=true;
      }
      bool getIsUsed()
      {
         return IsUsed;
      }
      bool getIsCrow()
      {
         return IsCrow;
      }
      int getid()
      {
         return id;
      }
      string getname()
      {
         return name;
      }
      node* get_next()
      {
         return nodenext;
      }
      node* get_pre()
      {
      	 return nodepre;
	  }
      
      void set_pre_point(node* Node)
      {
         this->nodenext=Node;
      }
};

int path::path_counter=0;

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
      arch(int id,double x,double y,string name,node* next,node* pre,Infor information):path(id,x,y,name,pre,next){
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
        this->nodenext=arch.nodenext;
        this->nodepre=arch.nodepre;
        this->information=arch.information;
        this->is_dest=arch.is_dest;
     }
     ~arch(){}
     void set_is_dest()
     {
        is_dest=true;
     }
     bool get_is_dest()
     {
        return is_dest;
     }
     void showInfo()//三种实现————每个建筑都show但是show内判断bool，析构函数里show，主程中show
     {
        cout<<this->name<<endl;
        cout<<this->information.open<<"~"<<this->information.close<<endl;
        cout<<this->information.book_way<<endl;
     }
};

#endif