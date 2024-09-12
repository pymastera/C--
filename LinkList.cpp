#include <iostream>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
using namespace std;
//Status是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef int ElemType;       //ElemType可换成任意类型
/*
线性表的基本操作：创建InitList、销毁DestroyList、清空ClearList、返回元素个数ListLength、是否为空表ListEmpty、
获取某元素GetElem、前驱PriorElem、后继NextElem、插入一元素ListInsert、删除一元素ListDelete、遍历ListTraverse。
*/
typedef struct LNode{       //链表结点定义
    ElemType data;
    struct LNode *next; 
}LNode, *LinkList;
Status InitList(LinkList &L){       //创建
    L = new LNode;      //创建结点，动态分配一块内存
    L->next = NULL;     //指针域置空
    return OK;
}
int ListEmpty(LinkList L){
    return(L->next?0:1);
}
Status DestroyList(LinkList &L){            //销毁
    LNode *p;
    while(L){
        p = L;
        L = L->next;
        delete p;
    }
    return OK;
}
Status ClearList(LinkList &L){      //清空
    LNode *p, *q;
    p = L->next;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
    L->next = NULL;
    return OK;
}
int ListLength(LinkList L){
    LinkList p = L->next;
    int i = 0;
    while(p){
        i++;
        p = p->next;
    }
    return i;
}
Status GetElem_L(LinkList L, int i, ElemType &e){
    //L为带头结点的单链表的头指针
    //当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    LinkList p = L->next;
    int j = 1;
    while(p && j<i){
        p = p->next;
        ++j;
    }
    if (!p || j>i) return ERROR;
    e = p->data;
    return OK;
}
LNode *LocateElem_ptr(LinkList L, ElemType e){
    //在线性表L中查找值为e的数据元素
    //找到，则返回L中值为e的数据元素，查找失败返回NULL
    LinkList p = L->next;
    while(p && p->data!=e)
        p = p->next;
    return p;
}

int LocateElem_num(LinkList L, ElemType e){     //根据指定数据获取位置序号
    LinkList p = L->next;
    int j = 1;
    while(p && p->data!=e){
        p = p->next;
        j++;
    }
    return(p?j:0);
}
Status ListInsert_L(LinkList &L, int i, ElemType e) {       //在L中第i个元素之前插入元素e
    LinkList p = L; 
    int j = 0;

    while(p && j < i - 1) {     //寻找第i-1个结点
        p = p->next;
        ++j;
    }

    if (!p || j > i - 1) {      //i小于1或者大于表长+1
        return ERROR;
    }

    LNode *s = new LNode;       //生成新结点
    s->data = e;

    s->next = p->next;
    p->next = s;

    return OK;
}
Status ListDelete_L(LinkList &L, int i, ElemType &e){
    LinkList p = L;
    int j = 0;
    while(p->next && j<i-1){        //寻找第i-1个结点并让p指向之
        p = p->next;                //循环到i-2，p指向i-1
        ++j;
    }
    if(!p->next || j>i-1) return ERROR; //删除位置非法
    LNode *q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
    return OK;
}
void CreateList_H(LinkList &L, int n){      //头插法建立，逆序输入
    L = new LNode;
    L->next = NULL;
    for (int i = n; i > 0; --i)
    {
        LNode *p = new LNode;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    }
}
void CreateList_R(LinkList &L, int n){      //尾插法建立，正序输入
    L = new LNode;
    L->next = NULL;
    LinkList r = L;
    for (int i = 0; i < n; ++i)
    {
        LNode *p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}
LinkList Connect(LinkList Ta, LinkList Tb){ //假设Ta、Tb都是非空的单循环链表
    LinkList p = Ta->next;                  //①p存表头结点
    Ta->next = Tb->next->next;              //②Tb表头连结Ta表尾
    delete Tb->next;                        //③释放Tb表头结点
    Tb->next = p;                           //④修改指针
    return Tb;
}
/****************************************************************************/
int main()
{
    LinkList list;
    InitList(list);
    printf("%d",ListEmpty(list));
    return 0;
}
