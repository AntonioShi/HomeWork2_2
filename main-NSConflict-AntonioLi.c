/**HomeWork2-2
 * 设A和B是两个按元素值递增有序的单链表，
 * 写一算法将A和B归并为按按元素值递减有序的单链表C，
 * 试分析算法的时间复杂度。
 * 據分析可能要用到循環雙鏈表的操作.
 * 因爲,要對比兩個鏈表的尾節點的數據,所以,要同時用到Next和prior
 */
#include <stdio.h>
#include <malloc.h>

typedef int DataType ;
typedef struct Node{
    DataType data ;
    struct Node *next ;
    struct Node *prior ;
}DLNode;

void DLNodeInitiate(DLNode **head){
    *head = (DLNode *)malloc(sizeof(DLNode)) ;
    (*head)->next = *head ;
    (*head)->prior = *head ;

}

int DLNodeInsert(DLNode *head, int i, DataType s){
    DLNode *p, *q ;
    int j = 0 ;
    //p = head ;,error!!
    p = head->next ;
    while(p != head && j < i){
        p = p->next ;
        j ++ ;
    }

    if(j != i){
        printf("参数错误4\n") ;
        return 0 ;
    }

    q = (DLNode *)malloc(sizeof(DLNode)) ;
    q->data = s ;

    //插入默认是插在目前元素的后面，课本上是在前面。
//    q->next = p->next ;
//    p->next->prior = q ;
//    p->next = q ;
//    q->prior = p ;
    //都可以，且结果一样

    //课本上的
    q->prior = p->prior ;
    p->prior->next = q ;


    q->next = p ;
    p->prior = q ;

    return 1 ;
}

//考虑到特殊请况,链表链接
void InsertInTheLast(DLNode *head, DLNode *x){
    DLNode *p, *s ;

//    p = head->next ;
//    while (p->next != head) {
//        p = p->next ;
//    }
    p = head->prior ;//直接到达尾节点的位置

    if(p->next == head)
    {

        s= (DLNode *)malloc(sizeof(DLNode));  //生成新节点
        s->data =x->data;

        s->next = p->next;
        p->next->prior = s;
        s->prior = p;
        p->next = s;
    }
//
//    s= (DLNode *)malloc(sizeof(DLNode));  //生成新节点
//    s->data =x->data;
//    p = head->prior ;
//    p->next = s ;
//    p = s->prior ;
//    head = s->next ;
    //我觉得实现啦相同的功能,在A的末尾添加一个节点

    /**
     * p = head ;
     * p->prior == p->last;
     * */
}


int DLNodeLength(DLNode *head){
    DLNode *p = head ;
    int size = 0 ;

    while(p->next != head){//**
        p = p->next ;
        size ++ ;
    }

    return size ;
}

void Destroy(DLNode **head){
    DLNode *p, *q ;
    p = *head ;
    int i, n = DLNodeLength(*head) ;
    //for (i = 0; i < n; ++i) {!!
    for (i = 0; i <= n; ++i) {
        q = p ;
        p = p->next ;
        free(q) ;
    }

    *head = NULL ;

//    while(p != NULL){//!!
//        q = p ;
//        p = p->next ;
//        free(q) ;
//    }

}


void DLNodeSort(DLNode *a, DLNode *b, DLNode *c){
    DLNode *p, *q ;

    p = a->prior ;//确保指针纸箱末尾
    q = b->prior ;

//    int aL = DLNodeLength(a) ;
//    int bL = DLNodeLength(b) ;
//    int min = aL < bL ? aL : bL ;
//    for (int i = 0; i < min; ++i) {
//        if(p->data > q->data) {
//            //得到最大的数,作为新节点的第一个数据项
//            InsertInTheLast(c, p);
//            p = p->prior ;
//        }
//        else if(p->data <= q->data){
//            InsertInTheLast(c, q) ;
//            q = q->prior ;
//        }
//    }
//
//    if(min == aL && q != b){//当A链比较短的时候
//      InsertInTheLast(c, q) ;
//        q = q->prior ;
//    }
//    else if(min == bL && p != a){//当B链比较短的时候
//      InsertInTheLast(c, p) ;
//        p = p->prior ;
//    }

    //比较相同长度的部分
    for (; p != a && q != b; ) {//因为药比较共同长度的项,所以时间复杂度至少为O(min)
        if(p->data > q->data) {
            //得到最大的数,作为新节点的第一个数据项
            InsertInTheLast(c, p);
            p = p->prior ;
        }
        else if(p->data <= q->data){
            InsertInTheLast(c, q) ;
            q = q->prior ;
        }
    }

    /*如果两个链表长度不一*/
    if(p == a )
    { /*A链表结束B链表未结束*/
        while(q != b)
        {
            InsertInTheLast(c, q); //将B链表所有的数按序全部插入C链表中
            q = q->prior;

        }
    }
    else if(q == b)
    {/*B链表结束A链表未结束*/
        while(p != a)
        {
            InsertInTheLast(c, p);//将A链表所有的数按序全部插入C链表中
            p = p->prior;

        }
    }

}

int main() {
    printf("Hello, World!\n");

    DLNode *heada, *headb, *headc ;
    int i, s, n;
    DLNode *p ;

    DLNodeInitiate(&heada) ;
    DLNodeInitiate(&headb) ;
    DLNodeInitiate(&headc) ;

    for (i = 0; i < 10; i++) {
        DLNodeInsert(heada, i, (i + 1)) ;
    }//插入初始化数据

    for (p = heada->next; p != heada; p = p->next) {
        printf("%-3d", p->data) ;
    }//输出数据
    printf("\n") ;

    for (i = 0; i < 20; i++) {
        DLNodeInsert(headb, i, (i+10)) ;
    }//插入初始化数据

    for (p = headb->next; p != headb; p = p->next) {
        printf("%-3d", p->data) ;
    }//输出数据
    printf("\n") ;

    //c链表已经完成初始化
    DLNodeSort(heada, headb, headc) ;//排序操作,构成新的链表
    printf("\n") ;

    /*从第一个数值开始输出*/
    p = headc->next;
    for(; p != headc; p = p->next)
    {
        printf("%-3d ",p->data);
    }

    Destroy(&heada) ;//析空内存
    Destroy(&headb) ;

    return 0;
}