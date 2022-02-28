#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;
typedef int status;
typedef struct{
    ElemType *elem;//线性表的基地址
    int length;//线性表的长度
    int listsize;//当前分配的存储容量
}SqList;

status InitList_Sq(SqList *L);
status Listinsert_Sq(SqList *L, int i, ElemType e);
status LocateElem(SqList *L, ElemType x);
status ListDelete(SqList *L, int i, ElemType *e);

status InitList_Sq(SqList *L)
{
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem)
    {
        return -1;
    }
    
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 0;
}

status Listinsert_Sq(SqList *L, int i, ElemType e)
{
    if (i<1 || i>L->length+1)
    {
        return -1;
    }
    if (L->length >= L->listsize)
    {
        ElemType* newbase = (ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if (!newbase)
        {
            return -1;
        }
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    
    ElemType *p;
    ElemType *q = &(L->elem[i-1]);//把L->elem【i-1】(这个线性表的第i个数据元素的地址赋给q)
    for ( p = &(L->elem[L->length-1]); p>=q; --p)
    {
        *(p+1) = *p;
    }
    *q = e;
    (L->length)++;
}


status LocateElem(SqList *L, ElemType x)
{
    for ( int i = 0; i < L->length; i++)
    {
        if (L->elem[i] == x)
        {
            return i;
        }
    }
    return -1;
}


status ListDelete(SqList *L, int i, ElemType *e)
{
    if (i<1 || i>L->length)
    {
        return -1;
    }
    ElemType *p;
    ElemType *q;
    p = &(L->elem[i-1]);
    *e = *p;
    q = &(L->elem[L->length-1]);
    for (++p;p<=q;p++)
    {
        *(p-1) = *p;
    }
    (L->length)--;
    return 0;
}

int main()
{
    SqList list;
    InitList_Sq(&list);
 
    int n = 10;
     
    for (int i = 0; i < 10; i++)
    {
        Listinsert_Sq(&list, i+1, i+1);
    }
    ElemType e;
    ListDelete(&list, 5, &e);
    printf("删除的元素是：%d\n", e);
 
    Listinsert_Sq(&list, 2, -1);
     
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", list.elem[i]);
    }
    getchar();
    return 0;
}
