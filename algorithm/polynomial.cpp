#include<iostream>
#include<cstdlib>
using namespace std;
/*設定linklist*/
struct link
{
    int exp;            //次方
    int coef;           //係數
    struct link *next;
};
typedef struct link *poly;
typedef struct link *plink;
/*新增資料*/
void AddData(poly p,int _coef,int _exp)
{
    poly tmp = p;
    while(tmp->next != NULL)
    {
        if(tmp->next->exp == _exp)            //比較現有次方，如果一樣就直接加係數
        {
            tmp->next->coef += _coef;
            return ;
        }
        else if(tmp->next->exp > _exp)        //如果次方比現有次方小，加入節點
        {
            poly tmp2 = tmp->next;
            tmp->next = (plink)malloc(sizeof(struct link));
            tmp->next->exp = _exp;
            tmp->next->coef = _coef;
            tmp->next->next = tmp2;
            return ;
        }
        else
            tmp = tmp->next;
    }
    tmp->next = (plink)malloc(sizeof(struct link));                   //若太大的話，則自己生成節點
    tmp->next->exp = _exp;
    tmp->next->coef = _coef;
    tmp->next->next = NULL;
}
/*輸入資料*/
void InputData(poly p)
{
    int n = 0,i = 0;
    int _coef = 0,_exp = 0;
    scanf("%d",&n);
    for(i = 0;i<n;i++)
    {
        scanf("%d%d",&_coef,&_exp);
        AddData(p,_coef,_exp);
    }
}
/*印出結果*/
void print(poly p)
{
    poly tmp = p->next;
    if(tmp == NULL)
    {
        cout<<"0"<<endl;
        return ;
    }
    else
    {
        while(tmp != NULL)
        {
            if(tmp == p->next)
            {
                cout<<tmp->coef<<"x^"<<tmp->exp;
            }
            else
            {
                cout<<" + "<<tmp->coef<<"x^"<<tmp->exp;
            }
            tmp = tmp->next;
        }
        cout<<endl;
    }
}
/*相加*/
void add(poly a,poly b,poly c)
{
    poly tmp = a->next;
    poly tmp2 = b->next;
    while(tmp != NULL)
    {
        AddData(c,tmp->coef,tmp->exp);
        tmp = tmp->next;
    }
    while(tmp2 != NULL)
    {
        AddData(c,tmp2->coef,tmp2->exp);
        tmp2 = tmp2->next;
    }
}
/*相乘*/
void multiply(poly a,poly b,poly c)
{
    poly tmp = a->next;
    poly tmp2 = b->next;
    while(tmp != NULL)
    {
        tmp2 = b->next;
        while(tmp2 != NULL)
        {
            AddData(c,tmp->coef * tmp2->coef,tmp->exp + tmp2->exp);
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
}
/*將係數為0得去除*/
void RemoveCoefZero(poly p)
{
    poly pre = p;
    poly cur = p->next;
    while(cur != NULL)
    {
        if(cur->coef == 0)
        {
            pre->next = cur->next;
            delete cur;
            cur = pre->next;
            continue;
        }
        pre = cur;
        cur = cur->next;
    }
}
/*main function*/
int main()
{
    int number;
    poly a,b,add_c,mul_d;
    a = (plink)malloc(sizeof(struct link));
    a->next = NULL;
    b = (plink)malloc(sizeof(struct link));
    b->next = NULL;
    add_c = (plink)malloc(sizeof(struct link));
    add_c->next = NULL;
    mul_d = (plink)malloc(sizeof(struct link));
    mul_d->next = NULL;
    InputData(a);
    InputData(b);
    add(a,b,add_c);
    multiply(a,b,mul_d);
    RemoveCoefZero(add_c);
    RemoveCoefZero(mul_d);
    cout<<"result of add"<<endl;
    print(add_c);
    cout<<endl;
    cout<<"result of multiply"<<endl;
    print(mul_d);
    return 0;
}
