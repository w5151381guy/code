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
    if(!visit[num]){
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
    if(!visit[i]){
      visit[i] = true;
      dfs(i);
    }
  }
}
void bfs(){
  vector<int> vec;
  for(int i=0;i<10;i++)
    visit[i] = false;
  for(int i=0;i<10;i++){
    if(!visit[i]){
      vec.push_back(i);
      visit[i] = true;
      while(!vec.empty()){
        int num = vec.front();
        vec.erase(vec.begin());
        for(int i=0;i<input[num].size();i++){
          if(!visit[input[num][i]]){
            visit[input[num][i]] = true;
            BFS.push_back(input[num][i]);
            vec.push_back(input[num][i]);
          }
        }
      }
    }
  }
}
void print(){
  cout << "DFS spanning tree:";
  for(int i=0;i<DFS.size();i++)
    cout << DFS[i];
  cout << "\nBFS spanning tree:";
  for(int i=0;i<BFS.size();i++)
    cout << BFS[i];
  cout << endl;
}
int main(){
  int node1,node2;
  int min;
  cout << "input (0,0) to stop\n";
  cin >> node1 >> node2;
  input[node1].push_back(node2);
  min = node1;
  while(cin >> node1 >> node2){
    if(min > node1)
      min = node1;
	  if(node1 - node2 == 0)
		  break;
    input[node1].push_back(node2);
  }
  DFS.push_back(min);
  BFS.push_back(min);
  travel();
  bfs();
  print();
  return 0;
}
