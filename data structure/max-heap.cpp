#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;
int size;
int arr[20];
void heapify(int arr[],int i,int size)
{
    int left,right,largest,temp;
    left=2*i;
    right=(2*i+1);
    if((left<=size)&&arr[left]>arr[i])           //判斷子結點有沒有比父結點大
        largest=left;
    else
        largest=i;
    if((right<=size)&&(arr[right]>arr[largest])) //同上
        largest=right;
    if(largest!=i)                               //如果子結點比父結點大的話就做交換
    {
        temp=arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
        heapify(arr,largest,size);
    }
}
void max_heap(int arr[],int size)
{
    for(int i=size/2;i>=1;i--)
        heapify(arr,i,size);
}
void insert(){
  int num;
  cout<<"Please insert number:";
  cin>>num;
  arr[size+1] = num;
  size++;
  max_heap(arr,size);
}
void deletion(){
  for(int i=1;i<size;i++)
    arr[i]=arr[i+1];
  size--;
  max_heap(arr,size);
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
void print()
{
    int level;
    level = judge(size);
    for(int i=0;i<level;i++)
    {
        for(int j=pow(2,i);j<2*(pow(2,i));j++)
        {
            if(j == size+1)
                break;
            else
                cout<<arr[j]<<" ";
        }
        cout<<endl;
    }
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
int main(){
  cout<<"Please enter the size of array:";
  cin>>size;
  cout<<"Please enter the element of array:";
  for(int i=1;i<=size;i++)
    cin>>arr[i];
  max_heap(arr,size);
  int num;
  while(true){
    cout<<"(1)insert"<<endl;
    cout<<"(2)delete"<<endl;
    cout<<"(3)print"<<endl;
    cout<<"(0)exit"<<endl;
    cin>>num;
    select(num);
  }
  return 0;
}
