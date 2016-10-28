#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int m,n;
int pop();
void push(int,int);
struct Node
{
   int data;          /* 儲存堆疊資料 */
   struct Node *next; /* 指向下一節點 */
};
typedef struct Node SNode; /* 堆疊節點的新型態 */
typedef SNode *LStack;     /* 串列堆疊的新型態 */
LStack top = NULL;          /* 堆疊頂端的指標 */
int isStackEmpty()
{
    if ( top == NULL )
        return 1;
    else
        return 0;
}
int pop()
{
    LStack ptr;      /* 指向堆疊頂端 */
    int temp;
    if ( !isStackEmpty() )
    {                    /* 堆疊是否是空的 */
        ptr = top;        /* 指向堆疊頂端 */
        top = top->next;  /* 堆疊指標指向下節點 */
        temp = ptr->data; /* 取出資料 */
        free(ptr);        /* 釋回節點記憶體 */
        return temp;      /* 堆疊取出 */
    }
   else
        return -1;
}
void push(int d)
{
    LStack new_node; /* 新節點指標 */
                  /* 配置節點記憶體 */
    new_node = (LStack)malloc(sizeof(SNode));
    new_node->data = d; /* 建立節點內容 */
    new_node->next = top; /* 新節點指向原開始 */
    top = new_node; /* 新節點成為堆疊開始 */
}
int main()
{
    cout<<"Please enter the exit point:";
    cin>>m>>n;
    int maze[n+2][m+2];
    int maze2[n+2][m+2];
    srand((unsigned)time(NULL));
    cout<<"最初的迷宮"<<endl;
    for(int i=0;i<n+2;i++){
      for(int j=0;j<m+2;j++){
        maze[i][j] = 1;
        //maze2[i][j] = 1;
      }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
              maze[i][j]=rand()%2;
        }
    }
    maze[1][1]=0; maze[n][m]=0;
    for(int i=0;i<n+2;i++){
      for(int j=0;j<m+2;j++)
        maze2[i][j] = maze[i][j];
    }
    int x=1,y=1;
    for(int i=0;i<n+2;i++){
        for(int j=0;j<m+2;j++)
            cout<<maze[i][j];
        cout<<endl;
    }
    maze2[1][1]=2;
    while(x != n && y != m)
    {
        push(x);push(y);
        if(maze[x+1][y]==0)                         //向右走
        {
          maze2[x+1][y]=2;                         //存入節點並設定走過的點為2
          x++;
          //push(x);
        }
        else if(maze[x][y+1]==0)                         //向下走
        {
            maze2[x][y+1]=2;
            y++;
            //push(y);
        }
        else if(maze[x+1][y+1]==0)                //向右下角走
        {
            maze2[x+1][y+1]=2;
            x++; y++;
            //push(x);
            //push(y);
        }
        else if(maze[x-1][y]==0)                         //向左走
        {
            maze2[x-1][y]=2;
            x--;
            //push(x);
        }
        else if(maze[x][y-1]==0)                         //向上走
        {
            maze2[x][y-1]=2;
            y--;
            //push(y);
        }
        else if(maze[x+1][y-1]==0)                //向右上角走
        {
            maze2[x+1][y-1]=2;
            x++; y--;
            //push(x);
            //push(y);
        }
        else if(maze[x-1][y+1]==0)                //向左下角走
        {
            maze2[x-1][y+1]=2;
            x--; y++;
            //push(x);
            //push(y);
        }
        else if(maze[x-1][y-1]==0)                //向左上角走
        {
            maze2[x-1][y-1]=2;
            x--; y--;
            //push(x);
            //push(y);
        }
        else
        {
            maze2[x][y] = 3;                /* 表示是迴溯的路 */
            x = pop();                     /* 退回一步 */
            y = pop();
        }
    }
      maze2[n][m] = 2;
      cout<<"走過的迷宮"<<endl;
      for(int i=0;i<n+2;i++)
      {
          for(int j=0;j<m+2;j++)
          {
              cout<<maze2[i][j];
          }
            cout<<endl;
      }
    return 0;
}
