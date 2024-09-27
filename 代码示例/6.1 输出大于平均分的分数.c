#include<stdio.h>

int main()
{
  	int x;
    double sum = 0;
    int cnt = 0;
    int number[100];                           //定义数组
    scanf("%d", &x);
    while(x > 0)
    {
        number[cnt] = x;                       //对数组元素赋值
        sum += x;
        cnt ++;
        scanf("%d", &x);
    }
    if(cnt > 0)
    {
        int i;
        double average = sum / cnt;
        for(int i = 0; i < cnt ; i ++)         //18行
        {
            if(number[i]  > average)
            {
                printf("%d ", number[i]);        //使用数组元素
            }
        }                                       //24行，18-24行是遍历数组
    }
    
    return 0;
}
