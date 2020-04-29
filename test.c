#include <stdio.h>
#include <string.h>
#include <math.h>

enum{ N = 5 };// amount of tests;

// the integral function that this program is testing:
extern double integral(double (*f) (double), double a, double b, double eps2);
extern int integral_it_cnt(void);

// the root function that this program is testing:
extern double root(double (*f) (double), double (*g) (double),
                   double a, double b, double eps1);
extern int root_it_cnt(void);

// functions for the 0th root test:
double r_f0(double x) { return x; }
double r_g0(double x) { return 1 - x; }
// functions for the 1st root test:
double r_f1(double x) { return x * x; }
double r_g1(double x) { return sqrt(x) + 1; }
// functions for the 2nd root test:
double r_f2(double x) { return exp(x); }
double r_g2(double x) { return x * x; }
// functions for the 3rd root test:
double r_f3(double x) { return log(x) + 6; }
double r_g3(double x) { return x; }
// functions for the 4th root test:
double r_f4(double x) { return 5 - x * x; }
double r_g4(double x) { return x * x * x; }
// array of the first test functions:
double (*f_r[N]) (double) = {r_f0, r_f1, r_f2, r_f3, r_f4};
// array of the second test functions:
double (*g_r[N]) (double) = {r_g0, r_g1, r_g2, r_g3, r_g4};
// array of first functions in human-readable form:
char *f_r_hr[5] = {"f(x) = x", "f(x) = x^2", "f(x) = e^x", 
                    "f(x) = ln(x) + 6", "f(x) = 5 - x^2"};
// array of second functions in human-readable form:
char *g_r_hr[5] = {"g(x) = 1 - x", "g(x) = sqrt(x) + 1", 
                    "g(x) = x^2", "g(x) = x", "g(x) = x^3"};

// function for the 0th integral test:
double i_f0(double x) { return x; }
// function for the 1st integral test:
double i_f1(double x) { return x * x; }
// function for the 2nd integral test:
double i_f2(double x) { return 1 / x; }
// function for the 3rd integral test:
double i_f3(double x) { return exp(x); }
// function for the 4th integral test:
double i_f4(double x) { return 5 - x * x; }
// array of test functions:
double (*f_i[N]) (double) = {i_f0, i_f1, i_f2, i_f3, i_f4};
// array of functions in human-readable form:
char *f_i_hr[5] = {"f(x) = x", "f(x) = x^2", "f(x) = 1 / x", 
                    "f(x) = e^x", "f(x) = 5 - x^2"};

// this function is testing the known functions root and integral
// what function it is: root or integral is defined by string
// func(func == "i" => function is integral and if
// func == "r" => function is root); the test_mode "all"
// means that you requested the testing of function func
// on all the test and test_mode custom stands for 
// testing the function func on the functions from test(0-4)
// with test_num index on segment [a;b] with eps precision:
void test(char *func, char *test_mode, int test_num, double a, double b, double eps)
{
    // for test's result output:
    char *s1 = "OK", *s2 = "wrong answer";
    if (!strcmp(func, "i"))
    {
        if (!strcmp(test_mode, "all"))
        {
            // array of the left and right segments' ends:
            double a_i[N] = {0, 0, 1, 0, -2}, b_i[N] = {10, 10, 10, 10, 2};
            // array of answers for each test:
            double ans_i[N] = {50.0, 333.3333333333333, 2.30258, 22026, 
                               14.66666666666};
            // array of eps2 precisions for each test(4 different precisions
            // for each function):
            double eps2_1[N] = {0.1, 0.1, 0.1, 100, 0.1};
            double eps2_2[N] = {0.01, 0.01, 0.01, 10, 0.01};
            double eps2_3[N] = {0.0000000001, 0.000000001, 0.00001, 1, 
                                0.0000000001};
            for (int i = 0; i < N; i++)
            {
                double integral_ans;
                printf("============Test of integral function #%d============\n", i);
                printf("the function for this the test is %s,\n", f_i_hr[i]);
                printf("the segment is [%.2lf, %.2lf],\n", a_i[i], b_i[i]);
                puts("----------------------------------------------------");
                printf("correct answer: %.10lf\n", ans_i[i]);
                printf("1) the first precision: %.10lf\n", eps2_1[i]);
                integral_ans = integral(f_i[i], a_i[i], b_i[i], eps2_1[i]);
                printf("   the tested function's answer: %.10lf\n", integral_ans);
                printf("   verdict for the first presicion: ");
                printf("%s\n", fabs(integral_ans - ans_i[i]) < eps2_1[i] ? s1 : s2);
                printf("   amount of iterations: %d\n", integral_it_cnt());
                printf("2) the second precision: %.10lf\n", eps2_2[i]);
                integral_ans = integral(f_i[i], a_i[i], b_i[i], eps2_2[i]);
                printf("   the tested function's answer: %.10lf\n", integral_ans);
                printf("   verdict for the second presicion: ");
                printf("%s\n", fabs(integral_ans - ans_i[i]) < eps2_2[i] ? s1 : s2);
                printf("   amount of iterations: %d\n", integral_it_cnt());
                printf("3) the third precision: %.10lf\n", eps2_3[i]);
                integral_ans = integral(f_i[i], a_i[i], b_i[i], eps2_3[i]);
                printf("   the tested function's answer: %.10lf\n", integral_ans);
                printf("   verdict for the third presicion: ");
                printf("%s\n", fabs(integral_ans - ans_i[i]) < eps2_3[i] ? s1 : s2);
                printf("   amount of iterations: %d\n", integral_it_cnt());
                puts("====================================================\n");
            }
        }
        else// test_mode == "custom"
        {
            puts("====================custom test=====================");
            printf("You requested integral of function %s\n", 
                                            f_i_hr[test_num]);
            printf("on segment %lf, %lf\n", a, b);
            printf("with %lf precision\n", eps);
            printf("the answer is: %lf\n", integral(f_i[test_num], 
                                                    a, b, eps));
            printf("iterations required: %d\n", integral_it_cnt());
            puts("====================================================\n");
        }
    }
    else// func == "r"
    {
        if (!strcmp(test_mode, "all"))
        {
            // array of the left and right segments' ends:
            double a_r[N] = {-10, 1, -10, 3, 1}, b_r[N] = {10, 10, -1, 12, 5};
            // array of answers for each test:
            double ans_r[N] = {0.5, 1.490216, -0.703, 8.090717405, 1.43342766};
            // array of eps1 precisions for each test(3 precisions
            // for each function):
            double eps1_1[N] = {0.1, 0.1, 0.1, 0.1, 0.1};
            double eps1_2[N] = {0.01, 0.01, 0.01, 0.01, 0.01};
            double eps1_3[N] = {0.0000001, 0.0001, 0.001, 0.00000001, 0.000001};
            for (int i = 0; i < N; i++)
            {
                double root_ans;
                printf("==============Test of root function #%d==============\n", i);
                printf("the first function is %s,\n", f_r_hr[i]);
                printf("the second function is %s,\n", g_r_hr[i]);
                printf("the segment is [%.2lf, %.2lf],\n", a_r[i], b_r[i]);
                puts("----------------------------------------------------");
                printf("correct answer: %.10lf\n", ans_r[i]);

                printf("1) the first precision: %.10lf\n", eps1_1[i]);
                root_ans = root(f_r[i], g_r[i], a_r[i], b_r[i], eps1_1[i]);
                printf("   the tested function's answer: %.10lf\n", root_ans);
                printf("   verdict for the first presicion: ");
                printf("%s\n", fabs(root_ans - ans_r[i]) < eps1_1[i] ? s1 : s2);
                printf("   amount of iterations: %d\n", root_it_cnt());

                printf("2) the second precision: %.10lf\n", eps1_2[i]);
                root_ans = root(f_r[i], g_r[i], a_r[i], b_r[i], eps1_2[i]);
                printf("   the tested function's answer: %.10lf\n", root_ans);
                printf("   verdict for the second presicion: ");
                printf("%s\n", fabs(root_ans - ans_r[i]) < eps1_2[i] ? s1 : s2);
                printf("   amount of iterations: %d\n", root_it_cnt());

                printf("3) the third precision: %.10lf\n", eps1_3[i]);
                root_ans = root(f_r[i], g_r[i], a_r[i], b_r[i], eps1_3[i]);
                printf("   the tested function's answer: %.10lf\n", root_ans);
                printf("   verdict for the third presicion: ");
                printf("%s\n", fabs(root_ans - ans_r[i]) < eps1_3[i] ? s1 : s2);
                printf("   amount of iterations: %d\n", root_it_cnt());
                puts("====================================================\n");
            }
        }
        else// test_mode == "custom"
        {
            puts("====================custom test=====================");
            puts("You requested the abcissa of functions's");
            printf("%s and %s intersection\n", f_r_hr[test_num], 
                                               g_r_hr[test_num]);
            printf("on segment %lf, %lf\n", a, b);
            printf("with %lf precision\n", eps);
            double x = root(f_r[test_num], g_r[test_num], a, b, eps);
            // the answer can be wrong only in case the segments' ends were incorrect;
            // |F(x)| < |F(x + eps) - F(x - eps)|: 
            if (fabs(f_r[test_num](x) - g_r[test_num](x)) < 
                fabs(f_r[test_num](x + eps) - g_r[test_num](x) - 
                     f_r[test_num](x - eps) + f_r[test_num](x - eps))
                && x >= a && x <= b)
            {
                printf("the answer is: %lf\n", x);
                printf("iterations required: %d\n", root_it_cnt());
            }
            else
                printf("Invalid segments' ends, try './main -help'.\n");
            puts("====================================================\n");
        }
        
    }
}