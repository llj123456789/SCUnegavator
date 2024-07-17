#ifndef FIND_ROED_H
#define FIND_ROED_H

#include<iostream>
#include<queue>
#include<deque>
#include"road_node.h"

using namespace std;

const int long long INF = 0x3f3f3f3f3f3f3f3fLL;

const int N = 3e5+2;


class edge{//map
public:
    int from=0, to=0;
    long long weight=0;
    edge(int f, int t, int w): from(f), to(t), weight(w) {}
};

deque <edge> e[N] ;//save map

deque <path> school;

deque <int> way;

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
extern int pre[N] ;//save the path by recording the previous point

//path_print
void print_path(int s, int t){
    if(s == t){
        cout << s << " ";
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
    //print_path(s, n);
}

//creat road
#endif
