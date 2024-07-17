#include<iostream>
#include<algorithm>
#include<queue>
#include<deque>
#include<string>
#include"2024_6_29_nodeCLASS.h"

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

class s_node{//point
	public:		
		int id=0;
		long long n_dis=0;
		s_node(int i, long long d): id(i), n_dis(d) {}
		bool operator < (const s_node &a)const{
			return n_dis > a.n_dis;
		}
};

int n=0, m=0;
int pre[N] ;//save the path by recording the previous point

//path_print
void print_path(int s, int t){
	if(s == t){
		cout << s << " ";
		return ;
	}
	print_path(s, pre[t]);
	cout << t << " ";
}

long long dis[N];//recode all the distance from random point to starting point

void dijkstra(int s, int de){
	/*int s=1;*/
	bool done[N];
	for(int i=1;i<=n;i++){//initialization
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
void  transfer(){
	for(int i=0;i<path::path_counter;i++){
		if(school[i].getIsUsed()){
			int from = school[i].get_next()->get_node_id();
			int to = school[i].get_pre()->get_node_id();
			double weight = abs(school[i].get_next()-school[i].get_pre());
			e[from].push_back(edge(from, to, weight));
			e[to].push_back(edge(to, from, weight));
		}	
	}
	return ;
}


int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//n--how many points; m--how many paths
	/*cin >> n >> m ;
	for(int i=1;i<=n;i++){
		e[i].clear();
	}
	*/
	
	for(int i=1;i<=path::path_counter;i++){
		e[i*2].clear();
	}
	while(1){
		int start_id=0, des_id=0;
		//change to two id input
		cin >> start_id >> des_id;
		
		dijkstra(start_id, des_id);
		print_path(start_id, des_id);
	}
	
	/*while(m--){
		int from=0, to=0;
		long long int weight=0;
		cin >> from >> to >> weight;
		e[from].push_back(edge(from, to, weight));
	}
	*/
	
	/*dijkstra();
	for(int i=1;i<=n;i++){
		if(dis[i] >= INF) cout << "-1 ";
		else cout << dis[i] << " ";
	}
	*/
	return 0;
}
