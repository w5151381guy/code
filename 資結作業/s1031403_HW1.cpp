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
    int maze[m][n];
    srand((unsigned)time(NULL));
    cout<<"最初的迷宮"<<endl;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
              maze[i][j]=rand()%2;
        }
    }
    int x=0,y=0;
    maze[x][y]=0; maze[m-1][n-1]=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            cout<<maze[i][j];
        cout<<endl;
    }
    while(x != m-1 && y != n-1)
    {
        if(maze[x][y+1]==0)                         //向下走
        {
            maze[x][y]=2;
            y++;
            push(x);
            push(y);
        }
        if(maze[x+1][y-1]==0)                //向右上角走
        {
            maze[x][y]=2;
            x++; y--;
            push(x);
            push(y);
        }
        if(maze[x+1][y]==0)                         //向右走
        {
            maze[x][y]=2;                         //存入節點並設定走過的點為2
            x++;
            push(x);
            push(y);
        }
        if(maze[x+1][y+1]==0)                //向右下角走
        {
            maze[x][y]=2;
            x++; y++;
            push(x);
            push(y);
        }
        if(maze[x][y-1]==0)                         //向上走
        {
            maze[x][y]=2;
            y--;
            push(x);
            push(y);
        }
        if(maze[x-1][y+1]==0)                //向左下角走
        {
            maze[x][y]=2;
            x--; y++;
            push(x);
            push(y);
        }
        if(maze[x-1][y]==0)                         //向左走
        {
            maze[x][y]=2;
            x--;
            push(x);
            push(y);
        }
        if(maze[x-1][y-1]==0)                //向左上角走
        {
            maze[x][y]=2;
            x--; y--;
            push(x);
            push(y);
        }
        else
        {
            maze[x][y] = 2;                /* 表示是迴溯的路 */
            y = pop();                     /* 退回一步 */
            x = pop();
        }
    }
    cout<<"走過的迷宮"<<endl;
    maze[m-1][n-1]=2;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<maze[i][j];
        }
        cout<<endl;
    }
    return 0;
}
