#include<stdio.h>

int main()
{
  	int x;
    double sum = 0;
    int cnt = 0;
    int number[100];                           //��������
    scanf("%d", &x);
    while(x > 0)
    {
        number[cnt] = x;                       //������Ԫ�ظ�ֵ
        sum += x;
        cnt ++;
        scanf("%d", &x);
    }
    if(cnt > 0)
    {
        int i;
        double average = sum / cnt;
        for(int i = 0; i < cnt ; i ++)         //18��
        {
            if(number[i]  > average)
            {
                printf("%d ", number[i]);        //ʹ������Ԫ��
            }
        }                                       //24�У�18-24���Ǳ�������
    }
    
    return 0;
}
