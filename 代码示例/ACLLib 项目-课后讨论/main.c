#include"acllib.h"
#include"stdio.h"

int Setup(){
	int width = 255,i,j;
	initWindow("RainBow", DEFAULT, DEFAULT, width, width);
	beginPaint();
	for(j = 0; j <= width; j ++)	
		for(i = 0; i <= width; ++ i)
		{
			putPixel(i, j, RGB(i % 255, j % 255, (j + i) * (j - i) % 255));
		}
	endPaint();
	
	return 0;
}	
