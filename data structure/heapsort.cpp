#include<iostream>
using namespace std;
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
void heapsort(int arr[],int size)
{
    int temp;
    max_heap(arr,size);
    for(int i=size;i>=2;i--)
    {
        temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;
        heapify(arr,1,i-1);
    }
}
int main()
{
    cout<<"Please enter the size of array:";
    int size;
    cin>>size;
    cout<<"Please enter the element of array:";
    int arr[size];
    for(int i=1;i<=size;i++)
        cin>>arr[i];
    heapsort(arr,size);
    cout<<"==========After Sorting=========="<<endl;
    for(int i=size;i>=1;i--)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}
