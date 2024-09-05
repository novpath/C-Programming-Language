#include<stdio.h>
#include<string.h>

int main()
{
	char str1[10000], str2[10000];
	char *p = NULL;
	int i = 0, j, pos;
	scanf("%[^\n]", str1);
	getchar();
	while((str2[i] = getchar()) != '\n')
		i ++;
	str2[i] = '\0';
	
	pos = -1;
	i = j = 0;
	while(i < strlen(str2) && j < strlen(str1))
	{
		if(str1[j] == str2[i])
		{
			i ++;
			j ++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
		if(j == strlen(str1))
		{
			pos = i - strlen(str1);
			printf("%d ", pos);
			i = pos + 1;
			j = 0; 
		}
	}
	
	if(pos == -1)
		printf("%d", pos);
	
	return 0;
}
