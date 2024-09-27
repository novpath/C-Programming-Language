#include<stdio.h>
#include<string.h>

int main()
{
	char str[1000] = {0, };
	char utc[11];
	char s1[] = "$GPRMC";
	char s2[] = "END";
	char UTC[11] = {0, };
	int th, tm, ts, bjt_hours, minutes, seconds, flag;
	int i, j, k;
	int field, number;
	int begin, check, check_str, check_value;
	int positioning;
	
	do
	{
		scanf("%s", str);
		i = j = k = flag = 0;
		field = number = 0;
		begin = check_str = check_value = 0; 
		positioning = 0;
		if(!strncmp(str, s1, 6))
		{
			while(str[j] != '\0')
			{
				if(str[j] == ',')
					number ++;
				j ++;
			}
			if(number != 12)
				break;
			while(str[i] != '\0')
			{
				if(str[i] == ',')
					field ++;
				if(begin == 1 && str[i] != '*' && check_str != 1)
				{
					if(i == 1)
						check = str[i];
					else if(i > 1)
						check = check ^ str[i];
				}
				if(field == 1 && flag == 0)
				{
					for(k = i + 1, j = 0; j < 10 && str[k] != ','; k ++, j ++)
					{
						utc[j] = str[k];
					}
					utc[10] = '\0';
					th = (utc[0] - '0') * 10 + (utc[1] - '0');
					tm = (utc[2] - '0') * 10 + (utc[3] - '0');
					ts = (utc[4] - '0') * 10 + (utc[5] - '0');
					flag = 1;
				}
				if(field == 2 && str[i] != ',')
				{
					if(str[i] == 'A')
						positioning = 1;
				}
				if(check_str == 1)
				{
					if(str[i] >= '0' && str[i] <= '9')
						check_value = check_value * 16 + (str[i] - '0');
					else if(str[i] >= 'a' && str[i] <= 'f')
						check_value = check_value * 16 + (str[i] - 'a' + 10);
					else if(str[i] >= 'A' && str[i] <= 'F')
						check_value = check_value * 16 + (str[i] - 'A' + 10);
				}
				
				if(check_str == 0 && field == 12 && str[i] == '*')
					check_str = 1;
				if(begin == 0 && str[i] == '$')
					begin = 1;
				i ++;
			}
			if((check % 65536) == check_value && positioning == 1)
			{
				minutes = tm;
				seconds = ts;
				bjt_hours = (th + 8) % 24;
			}
		}
	}while(strcmp(str, s2) != 0);
	
	printf("%02d:%02d:%02d", bjt_hours, minutes, seconds);
	
	return 0;
}
