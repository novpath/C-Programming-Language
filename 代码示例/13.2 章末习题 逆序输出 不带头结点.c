#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	struct LNode *next;
} Node, *LinkList;

void List_HeadInsert(LinkList *L);

int main(void)
{
	LinkList L;
	Node *p = NULL;
	List_HeadInsert(&L);
	
	for(p = L; p; p = p->next)
	{
		printf("%d ", p->data);
	}
	
	return 0;
}

void List_HeadInsert(LinkList *L)
{
	Node *s;
	int x;
	scanf("%d", &x);
	while(x != -1){
		s = (Node *)malloc(sizeof(Node));
		s->data = x;
        s->next = *L;
        *L = s;
		scanf("%d", &x);
	}
}
