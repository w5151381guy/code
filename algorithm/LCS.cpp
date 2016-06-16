#include<iostream>
#include<string>
#include<cstring>
using namespace std;
void print_LCS(int i,int j,char dir[15][15],string a,int count,char arr[15])
{
	if(i == 0 || j == 0)
	{
		for(int k = count - 1 ; k >= 0 ; k--)
			cout<<arr[k];
		cout<<endl;
		return;
	}
	if(dir[i][j] == 1)            //1 means top left
	{
		arr[count++] = a[i-1];
		print_LCS(i-1,j-1,dir,a,count,arr);
	}
	else if(dir[i][j] == 4)       //4 means two ways to go
	{
		/*go up and then go left*/
		print_LCS(i-1,j,dir,a,count,arr);         
		print_LCS(i,j-1,dir,a,count,arr);
	}
	else if(dir[i][j] == 2)       //2 means up
		print_LCS(i-1,j,dir,a,count,arr);
	else                          //3 means left
		print_LCS(i,j-1,dir,a,count,arr);
}
void LCS(string a,string b)
{
	char arr[15];             //array to store LCS
	int count = 0;
	char ch[15][15];         //store DP for two squence
	char dir[15][15];        //direction for DP
	/*initial zero for (i,0) and (0,j)*/
	for(int i = 0 ; i < a.length() ; i++)
		for(int j = 0 ; j < b.length() ; j++)
			ch[i][j] = 0;
	/*store squence to ch*//*set direction for datapath*/
	for(int i = 1 ; i <= a.length() ; i++)
	{
		for(int j = 1 ; j <= b.length() ; j++)
		{
			if(a[i-1] == b[j-1])
			{
				ch[i][j] = ch[i-1][j-1] + 1;
				dir[i][j] = 1;       //1 means top left
			}
			else
			{
				if(ch[i-1][j] >= ch[i][j-1])
				{
					if(ch[i-1][j] == ch[i][j-1])      //if up = left then 2 ways to go
					{
						ch[i][j] = ch[i-1][j];        //set up number to array
						dir[i][j] = 4;                //4 means 2 ways to go
					}
					else
					{
						ch[i][j] = ch[i-1][j];
						dir[i][j] = 2;       //2 means up
					}
				}
				else
				{
					ch[i][j] = ch[i][j-1];
					dir[i][j] = 3;       //3 means left
				}
			}
		}
	}
	print_LCS(a.length(),b.length(),dir,a,count,arr);
}
int main()
{
	string str1,str2;        //input sequence
	cin>>str1>>str2;
	LCS(str1,str2);
	return 0;
}
