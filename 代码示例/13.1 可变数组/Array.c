#include "array.h"

Array array_create(int init_size)
{
	Array a;
	a.size = init_size;
	a.array = (int *) malloc(sizeof(int) * a.size);
	return a; 
}


void array_free(Array *a)
{
	free(a->array);
	a->array = NULL;
	a->size = 0;
}
int array_size(const Array *a)
{
    return a->size;
}

int* array_at(Array *a, int index)
{
	if(index >= a->size){
		array_inflate(a, (index / BLOCK_SIZE + 1) * BLOCK_SIZE - a->size);
	}
	return &(a->array[index]);
}

void array_inflate(Array *a, int more_size)
{
	int *p = (int*)malloc(sizeof(int) * (a->size + more_size));
	int i;
	for(i = 0; i < a->size; i ++){    //可用库函数memcpy()实现 
		p[i] = a->array[i];
	} 
	free(a->array);
	a->array = p;
	a->size += more_size;
} 
