#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <math.h>
using namespace std;
//int arr[]={16,7,22,19,12};
//vector<int> v1(arr,arr+sizeof(arr)/sizeof(arr[0]));
vector<int> v1;
void select(int);
void insert();
int deletion();
void print();
int judge(int);
int main()
{
    int num;
    while(true)
    {
        cout<<"(1)insert"<<endl;
        cout<<"(2)delete"<<endl;
        cout<<"(3)print"<<endl;
        cout<<"(0)exit"<<endl;
        cin>>num;
        select(num);
    }
    return 0;
}
void select(int a)
{
    switch(a)
    {
        case 1:insert();break;
        case 2:deletion();break;
        case 3:print();break;
        case 0:exit(0);
    }
}
void insert()
{
    int num;
    cout<<"Please input number: ";
    cin>>num;
    v1.push_back(num);
    for (int i = 0; i < v1.size(); i++)
    {
        int child = i;
        do
        {
            int root = child / 2;
            if(child % 2 == 0)
                root--;
            if (v1[root] < v1[child])
            {
                  int temp = v1[root];
                  v1[root] = v1[child];
                  v1[child] = temp;
            }
            child = root;
          } while (child != 0);
    }
}
int deletion()
{
    int popValue = v1[0];
    v1[0] = v1[v1.size()-1];
    v1.erase(v1.end()-1);
    int index = 1;
    while(true){
      if(2 * index >= v1.size())
          break;

      if(2 * index == v1.size()-1){
      if(v1[index] < v1[2*index])
          swap(v1[index], v1[2*index]);
          break;
    }

      int maxVal = max(v1[2*index], v1[2*index+1]);
      if(maxVal == v1[2*index]){
        swap(v1[index], v1[2*index]);
        index = index * 2;
      }
      else {
        swap(v1[index], v1[2*index+1]);
        index = index * 2 + 1;
      }
  }
  return popValue;
}
void print()
{
    int level;
    level = judge(v1.size());
    for(int i=0;i<level;i++)
    {
        for(int j=pow(2,i);j<2*(pow(2,i));j++)
        {
            if(j == v1.size()+1)
                break;
            else
                cout<<v1[j-1]<<"   ";
        }
        cout<<endl;
    }
}
int judge(int x)
{
    int a = 1;
    int timer = 0;
    while(true){
      if(a==x) return timer+1;
      if(a>x) return timer;
      a*=2;
      ++timer;
    }
}
