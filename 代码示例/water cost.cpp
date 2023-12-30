#include <stdio.h>
double fun(double x);

int main()
{
    double x, y;

    scanf ("%lf", &x);
    
	y = fun(x);

    printf ("f(%.2f) = %.2f\n", x, y);

    return 0;
}

double fun(double x)

{
    double result;
    
    if (x <= 15){ 
        result = 4 * x / 3;
    }
    else{
        result = 2.5 * x - 10.5; 
    }

    
	return result;

}
