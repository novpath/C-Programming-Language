#include<stdio.h>
#include<stdlib.h>
#include "Array.h"
#include "Array.c" 

int main(int argc, char const *argv[] )
{
    Array a = array_create(10);
    printf("length(a) = %d\n", array_size(&a));
    *array_at(&a, 0) = 10;
    printf("a[0] = %d\n", *array_at(&a, 0));
    int number = 0;
    int cnt = 0;
    while(number != -1){
    	scanf("%d", &number);
    	if(number != - 1)
    		*array_at(&a, cnt ++) = number;
	}
    for(int i = 0; i < array_size(&a); i ++)
    {
    	printf("%d ", *array_at(&a, i));
		if((i + 1) % 5 == 0)
			printf("\n"); 
	} 
    array_free(&a);
    
    return 0;
}
