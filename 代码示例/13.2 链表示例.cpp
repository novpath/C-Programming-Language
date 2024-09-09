#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
    int value;
    struct _node *next;
} Node;

typedef struct _list{
    Node *head;
} List;

void add(List *pList, int number)
{
    //add to linked-list
    Node *p = (Node*)malloc(sizeof(Node));
    p->value = number;
    p->next = NULL;
    //find the last
    Node *last = pList->head;
    if(last)
    {
        while(last->next){
            last = last->next;
        }
        //attach
        last->next = p;
    }else{
        pList->head = p;
    }
}

int search(List *pList, int number)
{
    int ret = 0;
    Node *p;
    for ( p = pList->head; p; p = p->next ) {
        if ( p->value == number ) {
        	ret = 1;
            break;
        }
    }
    
    return ret;
}

void print(List *pList)
{
    Node *p;
    for(p = pList->head; p; p = p->next){
        printf("%d\t", p->value);
    }
    printf("\n");
}

void del(List *pList, int number)
{
    Node *p, *q;
    for(q = NULL, p = pList->head; p ; q = p, p = p->next)
    {
        if(p->value == number)
        {
            if(q){
                q->next = p->next;
            }else{
                pList->head = p->next;
            }
            free(p);
            break;
        }
    }
}

void clear(List *pList)
{
	Node *p, *q;
    for(p = pList->head; p; p = q){
    	q = p->next;
    	free(p);
	}
}

int main(int argc, char const *argv[])
{
    List list;
    int number;
    list.head = NULL;
    do{
        scanf("%d", &number);
        if(number != -1){
            add(&list, number);
        }
    }while(number != -1);
    
    print(&list);
    del(&list, 1);
    print(&list);
    clear(&list);
    
    return 0;
}
