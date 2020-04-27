#include <math.h>

int i_it_cnt;// counter of function root iterations;

// this is a helper function that calculates an area using trapezoidal
// rule for a function f on segment [a;b] with n segments partition:
double trapezoidal_method(double (*f) (double), double a, double b, int n)
{
    double h = (b - a) / n;// the length of partitions' segments;
    double ans = 0;// answer;
    // we need to go though all the f(a + i * h) values:
    for (int i = 0; i <= n; i++)
    {
        // all the f(a + i * h) values except f(a) and f(a + n * h) are 
        // included in formula 2 times:
        if (!i || i == n)
            ans += 0.5 * f(a + i * h);
        else
            ans += f(a + i * h);
    }
    ans *= h;// multiplying the sum of the trapezoids' bases by h;
    return ans;
}

// this function is calculating the definite integral of function f 
// on the segment [a;b] with precision eps2 using trapezoidal rule 
// and Runge rule:
double integral(double (*f) (double), double a, double b, double eps2)
{
    i_it_cnt = 0;// setting counter to zero before counting;
    int n = 10;// calculating the trapezoidal formula for 10 segments;
    // In and I2n are for trapezoidal method for n and 2n segments:
    double In, I2n = trapezoidal_method(f, a, b, n);
    do
    {
        i_it_cnt++;// updating the iteration counter;
        In = I2n;// updating the In value;
        n *= 2;
        I2n = trapezoidal_method(f, a, b, n);// updating the I2n value;
    } while (fabs((In - I2n) / 3) > eps2);// using Runge rule;
    return I2n;
}

// this functions returns the amount of iterations that last call
// of function integral with function trapezoidal_method made:
int integral_it_cnt(void)
{
    return i_it_cnt;
}