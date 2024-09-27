#include<stdio.h>
#include<string.h>

int main()
{
	char *str = "Hello";    
	char word[] = "Hello"; 
	char line[10] = "Hello";
	
	printf("%p %p\n", &str, str);
	printf("%p\n", word);
	printf("%p\n", line);
	printf("%d %d", strlen(line), strlen(word));
	
	return 0;
}
