#include <iostream>
#include <vector>
using namespace std;
vector<int> input[10];   //2's array for input
vector<int> DFS;
vector<int> BFS;
bool visit[10];
void dfs(int node){
  for(int i=0;i<input[node].size();i++){
    int num = input[node][i];
    if(visit[num] == false){
      visit[num] = true;
      DFS.push_back(num);
      dfs(num);
    }
  }
}
void travel(){
  for(int i=0;i<10;i++)
    visit[i] = false;
  for(int i=0;i<10;i++){
    if(visit[i] == false){
      visit[i] = true;
      dfs(i);
    }
  }
}
void bfs(){

}
void print(){
  cout << "DFS spanning tree:"
  for(int i=0;i<DFS.size();i++)
    cout << DFS[i];
  cout << "\nBFS spanning tree:"
  for(int i=0;i<BFS.size();i++)
    cout << BFS[i];
  cout << endl;
}
int main(){
  int node1,node2;
  cout << "input (0,0) to stop\n";
  while(cin >> node1 >> node2)
    input[node1].push_back(node2);
  DFS.push_back(0);
  BFS.push_back(0);
  travel();
  bfs();
  print();
  return 0;
}
