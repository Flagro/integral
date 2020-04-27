int r_it_cnt;// counter of function root iterations;

// this function is finding abscissa of intersection point of functions
// f and g on the segment [a;b] with eps1 precision:
double root(double (*f) (double), double (*g) (double), 
            double a, double b, double eps1)
{
    // in this function F(x) = f(x) - g(x) and we considering it
    // only on the [a;b] segment;
    // by default we thinking that F'(x) <= 0 and F''(x) <= 0;
    char dF_sign = 0, ddF_sign = 0; 
    if (f(a) - g(a) < 0)
        dF_sign = 1;// F(a) < 0 means that F'(x) > 0;
    if (f((a + b) / 2) - g((a + b) / 2) < (f(a) - g(a) + f(b) - g(b)) / 2)
        ddF_sign = 1;// F( (a+b)/2 ) < ( F(a)+F(b) )/2 means that F''(x) > 0;
    // d_xor_dd == 0 if F'(x) and F''(x) having the same signs
    // and otherwise d_xor_dd == 1:
    char d_xor_dd = dF_sign ^ ddF_sign;
    double a1 = a, b1 = b, c;// to save the a and b values;
    r_it_cnt = 0;// setting counter to zero before calculating iterations count;
    // since we moving closer to the root with every iteration
    // we can use while(1) instruction:
    do
    {
        r_it_cnt++;// updating the iteration counter;
        // iterative formula:
        double F_a1 = f(a1) - g(a1), F_b1 = f(b1) - g(b1);
        c = (a1 * F_b1 - b1 * F_a1) / (F_b1 - F_a1);
        if (d_xor_dd)
        {
            a1 = c;// moving to the root from the left side;
            // we got the answer if F(c) * F(c + eps1) <= 0:
            if ((f(c) - g(c)) * (f(c + eps1) - g(c + eps1)) <= 0)
                break;
        }
        else
        {
            b1 = c;// moving to the root from the right side;
            // we got the answer if F(c) * F(c - eps1) <= 0:
            if ((f(c) - g(c)) * (f(c - eps1) - g(c - eps1)) <= 0)
                break;
        }
    } while (1);
    return c;
}

// this functions returns the amount of iterations that last call
// of function root made:
int root_it_cnt(void)
{
    return r_it_cnt;
}