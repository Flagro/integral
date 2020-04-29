#include <stdio.h>
#include <string.h>
#include <math.h>

extern double get_integral(double *, double *, double *, int *, int *);
extern void test(char *, char *, int, double, double, double);

void invalid_input_msg(char *error)
{
    printf("Incorrect input: ");
    printf("%s\n", error);
    puts("Try './main -help' for more information.\n");
}

int main(int argc, char * argv[])
{
    // chk[0] = presence of -help option, chk[1] = presence of -getintegral,
    // chk[2] = presence of abscissa, chk[3] = presence of itcnt, 
    // chk[4] = presence of -testf option, chk[5] = presence of
    // -testmode i all option, chk[6] = presence of -testmode r all:
    char chk[7] = {0};// presence of each option except -testmode
    if(argc <= 1)
        puts("The program got no options, try './main -help' for the usage\n");
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-help"))
        {
            chk[0] = 1;// presence of -help option
            break;
        }
        else if(!strcmp(argv[i], "-getintegral"))
        {
            chk[1] = 1;// presence of -getintegral option
            if (i + 1 < argc)
            {
                if (!strcmp(argv[i + 1], "abscissa"))
                {
                    //i++;
                    chk[2] = 1;// presence of abscissa argument
                    if (i + 2 < argc && !strcmp(argv[i + 2], "itcnt"))
                    {
                        chk[3] = 1;// presence of itcnt argument
                        //i++;
                    }
                }
                else if (!strcmp(argv[i + 1], "itcnt"))
                {
                    //i++;
                    chk[3] = 1;// presence of itcnt argument
                    if (i + 2 < argc && !strcmp(argv[i + 2], "abscissa"))
                    {
                        chk[2] = 1;// presence of abscissa argument
                        //i++;
                    }
                }
            }
        }
        else if(!strcmp(argv[i], "-testf"))
            chk[4] = 1;
        else if(!strcmp(argv[i], "-testmode"))
        {
            if (i + 2 < argc)
            {
                char *func = argv[i + 1];
                char *mode = argv[i + 2];
                if (!strcmp(mode, "all"))
                {
                    if (!strcmp(func, "i"))
                        chk[5] = 1;
                    if (!strcmp(func, "r"))
                        chk[6] = 1;
                    i += 2;
                }
                else if (!strcmp(mode, "custom"))
                    i += 6;
            }
        }
        else// none of available options:
        {
            printf("This program has no option '%s'.", argv[i]);
            puts("Try './main -help' for more information.\n");
        }
    }
    if (chk[0])// -help option
    {
        puts("This program is calculating the area between three given");
        puts("curves: f1(x) = ln(x), f2(x) = -2x + 14 and f3(x) = 1/(2-x) + 6");
        puts("by using trapezoidal method for finding the defined integral");
        puts("and method of chords for finding the abscissas of the");
        puts("intersection points.");
        puts("Usage: ./main [options]");
        puts("Options and arguments:");
        puts("\t-help\t\tDisplay this information.");
        puts("\t-getintegral [abscissa] [itcnt] Print the value of area");
        puts("\t\t\tbetween given curves; use 'abscissa' as the agument");
        puts("\t\t\tto print the abscissas of intersection points and");
        puts("\t\t\tuse 'itcnt' as the argument to print the amount");
        puts("\t\t\tof iterations required for finding the roots and");
        puts("\t\t\tcalculating the integrals.");
        puts("\t-testf\t\tPrint the functions from the tests.");
        puts("\t-testmode {i|r} {all | custom fn a b eps} To get into the test mode");
        puts("\t\t\tof function i-integer or function r-root with all-mode");
        puts("\t\t\tor custom mode. All-mode tests the chosen function");
        puts("\t\t\ton the prepared tests and the custom mode allows");
        puts("\t\t\tyou to test the function on the function(s) from the");
        puts("\t\t\tlist that you can get by using -testf option.");
        puts("\t\t\tfn argument stands for the index of the test function(s)");
        puts("\t\t\tand take only [0;4] integer values, a and b arguments");
        puts("\t\t\tare for segments' ends (the chosen function must be defined");
        puts("\t\t\tin every point of the segment) and eps stands for the precision.\n");
        return 0;
    }
    if (chk[1])// -getintegral option
    {
        double x1, x2, x3;
        int it_r, it_i;
        double ans = get_integral(&x1, &x2, &x3, &it_r, &it_i);
        puts("The area between three given curves:");
        puts("f1(x) = ln(x), f2(x) = -2x + 14 and f3(x) = 1/(2-x) + 6");
        puts("calculated by using trapezoidal method and method of chords");
        printf("with eps = 0.001 is: %.5lf\n\n", ans);
        if (chk[2])// abscissa argument
        {
            puts("Curve intersection points:");
            puts("x1 - between f1 and f2,");
            puts("x2 - between f1 and f3,");
            puts("x3 - between f2 and f3:");
            printf("x1 = %lf, x2 = %lf, x3 = %lf\n\n", x1, x2, x3);
        }
        if (chk[3])// itcnt argument
        {
            printf("Amount of iterations required for finding abscissas: ");
            printf("%d\n", it_r);
            printf("Amount of iterations required for finding integrals: ");
            printf("%d\n\n", it_i);
        }
    }
    if (chk[4])
    {   
        printf("Functions from the tests:\n");
        puts("functions for the integral and their domains:");
        puts("0)f(x) = x; (-inf;+inf)");
        puts("1)f(x) = x^2; (-inf;+inf)");
        puts("2)f(x) = 1 / x; (-inf;0), (0;+inf)");
        puts("3)f(x) = e^x; (-inf;+inf)");
        puts("4)f(x) = 5 - x^2; (-inf;+inf)");
        puts("functions for the root and F(x) = f(x) - g(x) domains:");
        puts("0)f(x) = x, g(x) = 1 - x; (-inf;+inf)");
        puts("1)f(x) = x^2, g(x) = sqrt(x) + 1; [0;+inf)");
        puts("2)f(x) = e^x, g(x) = x^2; (-inf;+inf)");
        puts("3)f(x) = ln(x) + 6, g(x) = x; (0;+inf)"); 
        puts("4)f(x) = 5 - x^2, g(x) = x^3; (-inf;+inf)\n");
    }
    if (chk[0] || chk[1] || chk[2] || chk[3] || chk[4])
    {
        // main mode is done
        return 0;
    }
    // test mode:
    if (chk[5])
    {
        test("i", "all", 0, 0, 0, 0);
    }
    if (chk[6])
    {
        test("r", "all", 0, 0 ,0 ,0);
    }
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-testmode"))
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
            if (!strcmp(mode, "custom"))
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
                if ((!strcmp(func, "r") && 
                   ((func_num == 1 && func_a < 0) || (func_num == 3 && func_a <= 0))) ||
                   (!strcmp(func, "i") && 
                   (func_num == 2 && func_a <= 0 && func_b >= 0)))
                {
                    puts("Invalid segment, try '-testf' option for more info\n");
                }
                else
                    test(func, mode, func_num, func_a, func_b, func_eps);
                i += 6;
            }
            else
                i += 2;
        }
    }
    return 0;
}

