#include<stdio.h>

int main(void)
{
	char word[8];
	char word2[8];
	scanf("%s", word);
	scanf("%s", word2);
	printf("%s##%s##\n", word, word2);
	
	for(int i = 0; i < 16; i ++)
	{
		printf("%c %p ", word[i], &word[i]);
		if(i % 2 == 1)
		printf("\n");
	}
	for(int i = 0; i < 16; i ++)
	{
		printf("%c %p ", word2[i], &word2[i]);	
		if(i % 2 == 1)
		printf("\n");
	}
	
	return 0;
} 

