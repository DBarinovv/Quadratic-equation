//{----------------------------------------------------------------------------
//! SOLVE QUADRATIC EQUATION
//}----------------------------------------------------------------------------

#include <math.h>
#include <cstdio>

//{----------------------------------------------------------------------------
//! Infinite number of roots
//}----------------------------------------------------------------------------

const int INF = -1;
const double epsilon = 1/1000000;

//{----------------------------------------------------------------------------
//! Find roots of quadratic equation
//! @param a coefficient with x ^ 2
//! @param b coefficient with x ^ 1
//! @param c coefficient with x ^ 0
//! @param x1_orig [out] first root
//! @param x2_orig [out] second root
//! @see INF
//! @see epsilon
//}----------------------------------------------------------------------------

int Find_Roots (double a,double b,double c, double *x1_orig, double *x2_orig);

//{----------------------------------------------------------------------------
//! Checking if x is 0
//}----------------------------------------------------------------------------

bool Is_zero(double x);


//{----------------------------------------------------------------------------
//! Tests for program
//}----------------------------------------------------------------------------

int Tests ();

//-----------------------------------------------------------------------------

int main()
{
    int d = 0;
    printf("Type 1 if you want tests, another for square solve\n");
    if ((d = getchar()) == '1')
    {
        Tests();
    }
    else
    {
        int cnt = 0;
        double a = 0, b = 0, c = 0;
        double x1 = 0, x2 = 0;

//-----------------------------------------------------------------------------
//                       check for correct input
//-----------------------------------------------------------------------------

        int scanf_result = 0;
        while (scanf_result != 3)
        {
            printf("Enter 3 numbers\n");
            char endchar = 0;
            scanf_result = scanf("%lg %lg %lg%*[ \t]", &a, &b, &c);
            endchar = getchar();
            if ((endchar != '\n') || (scanf_result != 3)) {
                scanf("%*[^\n]");
                scanf_result = -1;
            }

        }

//-----------------------------------------------------------------------------

        cnt = Find_Roots(a, b, c, &x1, &x2);
        switch (cnt)
        {
            case INF:
                printf("Any solution is suitable");
                break;
            case 0:
                printf("No solutions\n");
                break;
            case 1:
                printf("1 solution: %lg", x1);
                break;
            case 2:
                printf("2 solutions: %lg and %lg", x1, x2);
                break;
            default:
                printf("Something went wrong and we got: %d", cnt);
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------

int Find_Roots (double a,double b,double c, double *x1_orig, double *x2_orig)
{
    if (Is_zero(a) && Is_zero(b) && Is_zero(c))
    {
        return INF;                ;
    }
    else if (Is_zero(a) && Is_zero(b) && !Is_zero(c))
    {
        return 0;
    }
    else if (Is_zero(a) && !Is_zero(b))
    {
        *x1_orig = c / b;
        return 1;
    }
    else /* if (!Is_zero(a)) */
    {
        double d = 0;
        d = b * b - 4 * a * c;
        if (d > 0 + epsilon)
        {
            d = sqrt(d);
            *x1_orig = (-b + d) / (2 * a);
            *x2_orig = (-b - d) / (2 * a);
            return 2;
        }
        else if (d < 0 - epsilon)
        {
            x1_orig = x2_orig = 0;
            return 0;
        }
        else
        {
            *x1_orig = (-b) / (2 * a);
            *x2_orig = *x1_orig;
            return 1;
        }
    }

{
    if (Is_zero(a))
    {
        if (Is_zero(b))
        {
            if (Is_zero(c))
            {
                return INF;
            }
            else
            {
                x1_orig = x2_orig = 0;
                return 0;
            }

        }
        else
        {
            *x1_orig = c / b;
            *x2_orig = *x1_orig;
            return 1;
        }
    }
    else
    {
        double d = 0;
        d = b * b - 4 * a * c;
        if (d > 0 + epsilon)
        {
            d = sqrt(d);
            *x1_orig = (-b + d) / (2 * a);
            *x2_orig = (-b - d) / (2 * a);
            return 2;
        }
        else if (d < 0 - epsilon)
        {
            x1_orig = x2_orig = 0;
            return 0;
        }
        else
        {
            *x1_orig = (-b) / (2 * a);
            *x2_orig = *x1_orig;
            return 1;
        }

    }

}
}
//-----------------------------------------------------------------------------

bool Is_zero (double x)
{
    return ! (x > epsilon || x < epsilon);
}

//{============================================================================
//! UNIT TESTS
//}============================================================================

int Tests ()
{
    struct polynominal
    {
        double a, b, c;
        double x1, x2;
        int nRoots;
    };

//-----------------------------------------------------------------------------
// array for testing

//------------------------------ a -- b -- c ---- x1 --- x2 - nr---------------
    struct polynominal A[]   = {{1,   2,   1,     -1,    -1,  1},
                                {1,   1,   1,      0,     0,  0},
                                {1,   1, -20,      4,    -5,  2},
                                {1,   5,   6,     -2,    -3,  2},
                                {1, -10,  21,      7,     3,  2},
                                {2,   3, -20,    2.5,    -4,  2},
                                {1, -14,  49,      7,     7,  1},
                                {12,  5,  -2, -2.0/3,  0.25,  2},
                                {7,   3,   2,      0,     0,  0},
                                {0,   0,   0,      0,     0, -1}};

//-----------------------------------------------------------------------------

    for (int num = 0; num < 10; num++)
    {
        double a = A[num].a;
        double b = A[num].b;
        double c = A[num].c;
        double x1 = A[num].x1;
        double x2 = A[num].x2;
        int nRoots = A[num].nRoots;

        int cnt = Find_Roots (a, b, c, &x1, &x2);

        if ((cnt == nRoots && Is_zero(x1 - A[num].x1) && Is_zero(x2 - A[num].x2))
         || (cnt == nRoots && Is_zero(x2 - A[num].x1) && Is_zero(x1 - A[num].x2)))
        {
            printf ("Test #%d passed\n", num);
        }
        else
        {
            printf ("Error in test #%d, %lgx^2 + %lgx + %lg = 0\n", num, a, b, c);
            printf ("Expected: %d roots: (%lg, %lg)\n", nRoots, A[num].x1, A[num].x2);
            printf ("Actual:   %d roots: (%lg, %lg)\n", cnt,    x1,        x2);
            return num;
        }
    }
return -1;
}
