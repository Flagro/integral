#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

extern double get_integral(double *, double *, double *, int *);
extern void test(char *, char *, int, double, double, double);

int main(int argc, char * argv[])
{
    char *help_advice = "Try './main -help' for more information.";
    if(argc <= 1)
        printf("%s\n", help_advice);
    double x1, x2, x3;
    int it_cnt;
    double ans = get_integral(&x1, &x2, &x3, &it_cnt);
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-help"))
        {
            puts("This program is calculating the area between three given");
            puts("curves: f1(x) = ln(x), f2(x) = -2x + 14 and f3(x) = 1/(2-x) + 6");
            puts("by using trapezoidal method for finding the defined integral");
            puts("and method of chords for finding the abscissas of the");
            puts("intersection points.");
            puts("Usage: ./main [options]");
            puts("Options and arguments:");
            puts("\t-help\t\tDisplay this information");
            puts("\t-getintegral\tPrint the value of area between given curves");
            puts("\t-abscissa\tPrint the abscissas of intersection points");
            puts("\t-itcnt\t\tPrint the amount of iterations for finding the roots");
            puts("\t-testf\t\tPrint the functions from the tests");
            puts("\t-testmode {i|r} {all | custom fn a b eps} To get into the test mode");
            puts("\t\t\tof function i-integer or function r-root with all-mode");
            puts("\t\t\tor custom mode. All-mode tests the chosen function");
            puts("\t\t\ton the prepared tests and the custom mode allows");
            puts("\t\t\tyou to test the function on the function(s) from the");
            puts("\t\t\tlist that you can get by using -testf option.");
            puts("\t\t\tfn argument stands for the index of the test function(s)");
            puts("\t\t\tand take only [0;4] integer values, a and b arguments");
            puts("\t\t\tare for segments' ends and eps stands for the precision.");
        }
        else if (!strcmp(argv[i], "-getintegral"))
        {
            printf("Area between given curves with eps = 0.001: %.5lf\n", ans);
        }
        else if (!strcmp(argv[i], "-abscissa"))
        {
            puts("Curve intersection points:");
            puts("x1 - between f1 and f2,");
            puts("x2 - between f1 and f3,");
            puts("x3 - between f2 and f3:");
            printf("x1 = %lf, x2 = %lf, x3 = %lf\n", x1, x2, x3);
        }
        else if (!strcmp(argv[i], "-itcnt"))
        {
            printf("Amount of iterations required for finding abscissas: ");
            printf("%d\n", it_cnt);
        }
        else if (!strcmp(argv[i], "-testf"))
        {
            printf("Functions from the tests:\n");
            puts("functions for the integral:");
            puts("0)f(x) = x\n1)f(x) = x^2\n2)f(x) = 1 / x\n3)f(x) = e^x\n4)f(x) = 5 - x^2");
            puts("functions for the root:");
            puts("0)f(x) = x, g(x) = 1 - x");
            puts("1)f(x) = x^2, g(x) = sqrt(x) + 1");
            puts("2)f(x) = e^x, g(x) = x^2");
            puts("3)f(x) = ln(x) + 6, g(x) = x"); 
            puts("4)f(x) = 5 - x^2, g(x) = x^3");
        }
        else if (!strcmp(argv[i], "-testmode"))
        {
            if (i + 2 >= argc)
            {
                printf("Incorrect input:");
                puts("-testmode option requires at least 2 arguments.");
                printf("%s", help_advice);
                break;
            }
            char *func = argv[i + 1];
            if (strcmp(func, "i") & strcmp(func, "r"))
            {
                printf("Incorrect input:");
                puts("invalid -testmode's 1st argument.");
                printf("%s", help_advice);
                break;
            }
            char *mode = argv[i + 2];
            if (strcmp(mode, "all") & strcmp(mode, "custom"))
            {
                printf("Incorrect input:");
                puts("invalid -testmode's 2nd argument.");
                printf("%s", help_advice);
                break;
            }
            if (!strcmp(mode, "all"))
            {
                test(func, mode, 0, 0, 0, 0);
                i += 2;
            }
            else
            {
                if (i + 6 >= argc)
                {
                    printf("Incorrect input:");
                    puts("-testmode in custom mode requires at least 6 arguments.");
                    printf("%s", help_advice);
                    break;
                }
                int func_num;
                assert(sscanf(argv[i + 3], "%d", &func_num) && "Incorrect input");
                double func_a;
                assert(sscanf(argv[i + 4], "%lf", &func_a) && "Incorrect input");
                double func_b;
                assert(sscanf(argv[i + 5], "%lf", &func_b) && "Incorrect input");
                double func_eps;
                assert(sscanf(argv[i + 6], "%lf", &func_eps) && "Incorrect input");
                test(func, mode, func_num, func_a, func_b, func_eps);
                i += 6;
            }
        }
        else
        {
            printf("Unknown option: %s\n", argv[i]);
            printf("%s\n", help_advice);
        }
        
    }
    return 0;
}

