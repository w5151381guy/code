#include<iostream>
#include<string>
#include<cstring>
using namespace std;
void kmap(string);
int main()
{
    int count;
    string num;      //minterm&maxterm
    cout<<"Please input how many boolean functions:";
    cin>>count;
    for(int i=0;i<count;i++)
    {
        cout<<"Please input minterm and maxterm:";
        cin>>num;
        kmap(num);
    }
    return 0;
}
void kmap(string a)
{
    string arr[4][4];
    cout<<"轉成k-map架構"<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i<2)
            {
                if(j == 2)
                    arr[i][j]=a[i*4+j+1];
                else if(j == 3)
                    arr[i][j]=a[i*4+j-1];
                else
                    arr[i][j]=a[i*4+j];
            }
            if(i == 2)
            {
                if(j == 2)
                    arr[i][j]=a[(i+1)*4+j+1];
                else if(j == 3)
                    arr[i][j]=a[(i+1)*4+j-1];
                else
                    arr[i][j]=a[(i+1)*4+j];
            }
            if(i == 3)
            {
                if(j == 2)
                    arr[i][j]=a[(i-1)*4+j+1];
                else if(j == 3)
                    arr[i][j]=a[(i-1)*4+j-1];
                else
                    arr[i][j]=a[(i-1)*4+j];
            }
            cout<<arr[i][j];
        }
        cout<<endl;
    }
    cout<<"==============================\n"<<"wxyz"<<endl;
           /*第一行及第一列*/
    if(arr[0][0] == "1" && arr[0][1] == "1" && arr[0][2] == "1" && arr[0][3] == "1")
        cout<<"0022"<<endl;
    else if(arr[0][0] != "0" && arr[0][1] != "0" && arr[0][2] != "0" && arr[0][3] != "0")
        cout<<"0022"<<endl;
    if(arr[0][0] == "1" && arr[1][0] == "1" && arr[2][0] == "1" && arr[3][0] == "1")
        cout<<"2200"<<endl;
    else if(arr[0][0] != "0" && arr[1][0] != "0" && arr[2][0] != "0" && arr[3][0] != "0")
        cout<<"2200"<<endl;
    else if(arr[0][0] == "1" && arr[0][1] == "1")
        cout<<"0002"<<endl;
    else if(arr[0][1] == "1" && arr[0][2] == "1")
        cout<<"0021"<<endl;
    else if(arr[0][2] == "1" && arr[0][3] == "1")
        cout<<"0012"<<endl;
    else if(arr[0][0] == "1" && arr[0][3] == "1")
        cout<<"0020"<<endl;
    else if(arr[0][0] == "1" && arr[1][0] == "1")
        cout<<"0200"<<endl;
    else if(arr[1][0] == "1" && arr[2][0] == "1")
        cout<<"2100"<<endl;
    else if(arr[2][0] == "1" && arr[3][0] == "1")
        cout<<"1200"<<endl;
    else if(arr[0][0] == "1" && arr[3][0] == "1")
        cout<<"2000"<<endl;
           /*第二行及第二列*/
    if(arr[1][0] == "1" && arr[1][1] == "1" && arr[1][2] == "1" && arr[1][3] == "1")
        cout<<"0122"<<endl;
    else if(arr[1][0] != "0" && arr[1][1] != "0" && arr[1][2] != "0" && arr[1][3] != "0")
        cout<<"0122"<<endl;
    if(arr[0][1] == "1" && arr[1][1] == "1" && arr[2][1] == "1" && arr[3][1] == "1")
        cout<<"2201"<<endl;
    else if(arr[0][1] != "0" && arr[1][1] != "0" && arr[2][1] != "0" && arr[3][1] != "0")
        cout<<"2201"<<endl;
    else if(arr[1][0] == "1" && arr[1][1] == "1")
        cout<<"0102"<<endl;
    else if(arr[1][1] == "1" && arr[1][2] == "1")
        cout<<"0121"<<endl;
    else if(arr[1][2] == "1" && arr[1][3] == "1")
        cout<<"0112"<<endl;
    else if(arr[1][0] == "1" && arr[1][3] == "1")
        cout<<"0120"<<endl;
    else if(arr[0][1] == "1" && arr[1][1] == "1")
        cout<<"0201"<<endl;
    else if(arr[1][1] == "1" && arr[2][1] == "1")
        cout<<"2101"<<endl;
    else if(arr[2][1] == "1" && arr[3][1] == "1")
        cout<<"1201"<<endl;
    else if(arr[0][1] == "1" && arr[3][1] == "1")
        cout<<"2001"<<endl;
          /*第三行及第三列*/
    if(arr[2][0] == "1" && arr[2][1] == "1" && arr[2][2] == "1" && arr[2][3] == "1")
        cout<<"1122"<<endl;
    else if(arr[2][0] != "0" && arr[2][1] != "0" && arr[2][2] != "0" && arr[2][3] != "0")
        cout<<"1122"<<endl;
    if(arr[0][2] == "1" && arr[1][2] == "1" && arr[2][2] == "1" && arr[3][2] == "1")
        cout<<"2211"<<endl;
    else if(arr[2][0] != "0" && arr[2][1] != "0" && arr[2][2] != "0" && arr[2][3] != "0")
        cout<<"1122"<<endl;
    else if(arr[2][0] == "1" && arr[2][1] == "1")
        cout<<"1102"<<endl;
    else if(arr[2][1] == "1" && arr[2][2] == "1")
        cout<<"1121"<<endl;
    else if(arr[2][2] == "1" && arr[2][3] == "1")
        cout<<"1112"<<endl;
    else if(arr[2][0] == "1" && arr[2][3] == "1")
        cout<<"1120"<<endl;
    else if(arr[0][2] == "1" && arr[1][2] == "1")
        cout<<"0211"<<endl;
    else if(arr[1][2] == "1" && arr[2][2] == "1")
        cout<<"2111"<<endl;
    else if(arr[2][2] == "1" && arr[3][2] == "1")
        cout<<"1211"<<endl;
    else if(arr[0][2] == "1" && arr[3][2] == "1")
        cout<<"2011"<<endl;
           /*第四行及第四列*/
    if(arr[3][0] == "1" && arr[3][1] == "1" && arr[3][2] == "1" && arr[3][3] == "1")
        cout<<"1022"<<endl;
    else if(arr[3][0] != "0" && arr[3][1] != "0" && arr[3][2] != "0" && arr[3][3] != "0")
        cout<<"1022"<<endl;
    if(arr[0][3] == "1" && arr[1][3] == "1" && arr[2][3] == "1" && arr[3][3] == "1")
        cout<<"2210"<<endl;
    else if(arr[0][3] != "0" && arr[1][3] != "0" && arr[2][3] != "0" && arr[3][3] != "0")
        cout<<"2210"<<endl;
    else if(arr[3][0] == "1" && arr[3][1] == "1")
        cout<<"1002"<<endl;
    else if(arr[3][1] == "1" && arr[3][2] == "1")
        cout<<"1021"<<endl;
    else if(arr[3][2] == "1" && arr[3][3] == "1")
        cout<<"1012"<<endl;
    else if(arr[3][0] == "1" && arr[3][3] == "1")
        cout<<"1020"<<endl;
    else if(arr[0][3] == "1" && arr[1][3] == "1")
        cout<<"0210"<<endl;
    else if(arr[1][3] == "1" && arr[2][3] == "1")
        cout<<"2110"<<endl;
    else if(arr[2][3] == "1" && arr[3][3] == "1")
        cout<<"1210"<<endl;
    else if(arr[0][3] == "1" && arr[3][3] == "1")
        cout<<"2010"<<endl;
}
