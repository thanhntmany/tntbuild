#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// core
double oneRealCubicRoot(double a, double b, double c, double d)
{
    double _3a = a * 3,
           D = b * b - _3a * c;
    if (D < 0)
    {
        double sqrtDa = sqrt(-D),
               k = (9 * a * b * c - 2 * b * b * b - 27 * a * a * d) / (2 * sqrtDa * sqrtDa * sqrtDa),
               M = cbrt(k + sqrt(k * k + 1));
        return (sqrtDa * (M - 1 / M) - b) / _3a;
    }
    else if (D > 0)
    {
        double sqrtDa = sqrt(D),
               k = (9 * a * b * c - 2 * b * b * b - 27 * a * a * d) / (2 * sqrtDa * sqrtDa * sqrtDa),
               s = 1;

        if (k < 0)
        {
            k = -k;
            s = -1;
        };

        if (k > 1)
        {
            double M = cbrt(k + sqrt(k * k - 1));
            return (s * sqrtDa * (M + 1 / M) - b) / _3a;
        }
        else
            return (2 * sqrtDa * cos(acos(s * k) / 3) - b) / _3a;
    }

    return (cbrt(b * b * b - 27 * a * a * d) - b) / _3a;
};

double oneCorrectedRealCubicRoot(double a, double b, double c, double d)
{
    double _3a = a * 3,
           D = b * b - _3a * c,
           r = 0, t = 0;

    if (D < 0)
    {
        double sqrtDa = sqrt(-D),
               k = (9 * a * b * c - 2 * b * b * b - 27 * a * a * d) / (2 * sqrtDa * sqrtDa * sqrtDa),
               M = cbrt(k + sqrt(k * k + 1));
        r = (sqrtDa * (M - 1 / M) - b) / _3a;
    }
    else if (D > 0)
    {
        double sqrtDa = sqrt(D),
               k = (9 * a * b * c - 2 * b * b * b - 27 * a * a * d) / (2 * sqrtDa * sqrtDa * sqrtDa),
               s = 1;

        if (k < 0)
        {
            k = -k;
            s = -1;
        };

        if (k > 1)
        {
            double M = cbrt(k + sqrt(k * k - 1));
            r = (s * sqrtDa * (M + 1 / M) - b) / _3a;
        }
        else
            r = (2 * sqrtDa * cos(acos(s * k) / 3) - b) / _3a;
    }
    else
        r = (cbrt(b * b * b - 27 * a * a * d) - b) / _3a;

    // Correcting with Newton's method
    if (t = a * r * r * r + b * r * r + c * r + d)
    {
        r -= t / (_3a * r * r + 2 * b * r + c);
    }
    else
        return r;

    if (t = a * r * r * r + b * r * r + c * r + d)
    {
        r -= t / (_3a * r * r + 2 * b * r + c);
    }
    else
        return r;

    if (t = a * r * r * r + b * r * r + c * r + d)
        r -= t / (_3a * r * r + 2 * b * r + c);

    return r;
};
// test

double drand(double low, double high)
{
    return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
}

double test()
{
    double a, b, c, d, r, t;

    a = drand(drand(-100, 1000), drand(-100, 1000));
    b = drand(drand(-100, 1000), drand(-100, 1000));
    c = drand(drand(-100, 1000), drand(-100, 1000));
    d = drand(drand(-100, 1000), drand(-100, 1000));

    r = oneCorrectedRealCubicRoot(a, b, c, d);
    t = a * r * r * r + b * r * r + c * r + d;

    return t;
};

int main()
{
    size_t l = 100000;
    double sumErr = 0;

    for (size_t i = 0; i < l; i++)
    {
        sumErr += fabs(test());
    }
    printf("sumErr     = %f\n", sumErr);
    printf("sumErr Avg = %f\n", sumErr / (double)l);

    return 0;
};