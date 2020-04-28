#include <math.h>

extern double root(double (*f) (double), double (*g) (double), 
            double a, double b, double eps1);
extern double integral(double (*f) (double), double a, double b, double eps2);
extern int integral_it_cnt(void);
extern int root_it_cnt(void);
extern double f1(double);
extern double f2(double);
extern double f3(double);

// this function is calculating the area of given functions's f1, 
// f2, f3 intersection. these functions are defined in .asm files.
// the return value of this function is the calculated area and it
// saves the abscissas of intersection points in it's arguments x1
// x2, x3 and amount of iterations for finding the root in it_cnt:
double get_integral(double *x1, double *x2, double *x3, int *it_r, int *it_i)
{
    int it_r1 = 0, it_i1 = 0;// root and integral function's iteration counter
    // we are using these eps1 and eps2 values to reach
    // final precision eps = 0.001 (more details in report
    // but the main idea is to take the max(int_i + eps2)
    // and min(int_i - eps2) where int_i is the integral
    // that was calculated with integral functions on
    // [x_j+-eps1;x_k+-eps1] segment and check that
    // the max(int_i + eps2) - min(int_i - eps2) < eps what
    // will prove that integral was calculated with eps
    // precision):
    double  eps1 = 1e-6, eps2 = 1e-6;
    // the root is inside [a;b] segments;
    // it's obvious from the graphics of the functions
    // and will be proved in report:
    double a, b;
    a = 5, b = 8;
    // intersection of f1 and f2 on [a;b]: 
    double x1_2 = root(f1, f2, a, b, eps1);
    it_r1 += root_it_cnt();
    a = 2.1, b = 2.2;
    // intersection of f1 and f3 on [a;b]: 
    double x1_3 = root(f1, f3, a, b, eps1);
    it_r1 += root_it_cnt();
    a = 4, b = 5;
    // intersection of f2 and f3 on [a;b]:
    double x2_3 = root(f2, f3, a, b, eps1);
    it_r1 += root_it_cnt();
    *x1 = x1_2;// first intersection point;
    *x2 = x1_3;// second intersection point;
    *x3 = x2_3;// third intersection point;
    *it_r = it_r1;// saving the count of iterations;
    // first, second and third square:
    double sq1_23 = integral(f1, x1_3, x1_2, eps2);
    it_i1 += integral_it_cnt();
    double sq2_13 = integral(f2, x2_3, x1_2, eps2);
    it_i1 += integral_it_cnt();
    double sq3_12 = integral(f3, x1_3, x2_3, eps2);
    it_i1 += integral_it_cnt();
    *it_i = it_i1;// saving the count of iterations;
    // this formula is obvious from the functions' graphics
    // and will be proved in report:
    return sq2_13 + sq3_12 - sq1_23;
}