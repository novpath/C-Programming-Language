#include<stdio.h>

int main()
{
	int a, b;

	scanf("%d %d", &a, &b);
	
	int ret = 0;
	int i;
	for(i = 1; i < ((a < b)? a : b); i ++)
	{
	    if(a % i == 0 && b % i == 0)
	    {
	    	ret = i;  //�������С��Լ������ֱ��break
	    }
	}

	printf("%d��%d�����Լ����%d��\n", a, b, ret);
	
	return 0;
}
