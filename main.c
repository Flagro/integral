#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

extern double get_integral(double *, double *, double *, int *, int *);
extern void test(char *, char *, int, double, double, double);

void invalid_input_msg(char *error)
{
    printf("Incorrect input: ");
    printf("%s\n", error);
    puts("Try './main -help' for more information.");
}

int main(int argc, char * argv[])
{
    if(argc <= 1)
        puts("The program got no options, try './main -help' for the usage");
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
            puts("\t-getintegral [abscissa] [itcnt] Print the value of area");
            puts("\t\t\tbetween given curves; use 'abscissa' as the agument");
            puts("\t\t\tto print the abscissas of intersection points and");
            puts("\t\t\tuse 'itcnt' as the argument to print the amount");
            puts("\t\t\tof iterations required for finding the roots and");
            puts("\t\t\tcalculating the integrals");
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
            double x1, x2, x3;
            int it_r, it_i;
            double ans = get_integral(&x1, &x2, &x3, &it_r, &it_i);
            puts("The area between three given curves:");
            puts("f1(x) = ln(x), f2(x) = -2x + 14 and f3(x) = 1/(2-x) + 6");
            puts("calculated by using trapezoidal method and method of chords");
            printf("with eps = 0.001 is: %.5lf\n", ans);
            char ab = 0, it = 0;
            if (i + 1 < argc && !strcmp(argv[i + 1], "abscissa"))
            {
                ab = 1;
                if (i + 2 < argc && !strcmp(argv[i + 2], "itcnt"))
                    it = 1;
            }
            else if (i + 1 < argc && !strcmp(argv[i + 1], "itcnt"))
            {
                it = 1;
                if (i + 2 < argc && !strcmp(argv[i + 2], "abscissa"))
                    ab = 1;
            }
            if (ab)
            {
                i++;
                puts("Curve intersection points:");
                puts("x1 - between f1 and f2,");
                puts("x2 - between f1 and f3,");
                puts("x3 - between f2 and f3:");
                printf("x1 = %lf, x2 = %lf, x3 = %lf\n", x1, x2, x3);
            }
            if (it)
            {
                i++;
                printf("Amount of iterations required for finding abscissas: ");
                printf("%d\n", it_r);
                printf("Amount of iterations required for finding integrals: ");
                printf("%d\n", it_i);
            }
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
                invalid_input_msg("-testmode option requires at least 2 arguments.");
                break;
            }
            char *func = argv[i + 1];
            if (strcmp(func, "i") && strcmp(func, "r"))
            {
                invalid_input_msg("invalid -testmode's 1st argument.");
                break;
            }
            char *mode = argv[i + 2];
            if (strcmp(mode, "all") & strcmp(mode, "custom"))
            {
                invalid_input_msg("invalid -testmode's 2nd argument.");
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
                    invalid_input_msg("-testmode in custom mode requires at least 6 arguments.");
                    break;
                }
                int scanned;
                int func_num;
                scanned = sscanf(argv[i + 3], "%d", &func_num);
                if (!scanned || func_num < 0 || func_num > 4)
                {
                    invalid_input_msg("invalid -testmode's 3rd argument.");
                    break;
                }
                double func_a;
                scanned = sscanf(argv[i + 4], "%lf", &func_a);
                if (!scanned)
                {
                    invalid_input_msg("invalid -testmode's 4th argument.");
                    break;
                }
                double func_b;
                scanned = sscanf(argv[i + 5], "%lf", &func_b);
                if (!scanned || func_a >= func_b)
                {
                    invalid_input_msg("invalid -testmode's 5th argument.");
                    break;
                }
                double func_eps;
                scanned = sscanf(argv[i + 6], "%lf", &func_eps);
                if (!scanned || func_eps <= 0)
                {
                    invalid_input_msg("invalid -testmode's 6th argument.");
                    break;
                }
                test(func, mode, func_num, func_a, func_b, func_eps);
                i += 6;
            }
        }
    }
    return 0;
}

