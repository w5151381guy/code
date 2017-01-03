#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> >input;   //2's array for input
int main(){
  int node1,node2;
  vector<int> vec;
  cout << "input (0,0) to exit\n";
  while(cin >> node1 >> node2){
    vec.push_back(node2);
    input[node1].push_back(vec);
    vec.clear();
  }
  dfs();
  bfs();
  print();
  return 0;
}
