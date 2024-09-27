#include<stdio.h>

int main()
{
    int BJT;
    scanf("%d", &BJT);
    
    int hour1, minute1, t1;
    int hour2, minute2, t2;
    
    hour1 = BJT / 100;
    minute1 =  BJT  % 100;
    t1 = 60 * hour1 + minute1;
    t2 = t1 - 60 * 8;
    
    if(t2 >= 0 )
    {
        hour2 = t2 / 60;
        minute2 = t2 % 60;
    }else{
        t2 = 24 * 60 + t2;
        hour2 = t2 / 60;
        minute2 = t2 % 60;
    }    
    if(hour2 == 0)
        printf("%d", minute2);
    else if(minute2 < 10) 
    	printf("%d%02d", hour2, minute2);
    else
    	printf("%d%d", hour2, minute2);
    
    return 0;
}
