#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

double f(double x) {
    return 2.0 * x * x * x + (-1.0) * x * x + (-5.0) * x + 15.0;
}

double integrand(double x) {
    double val = f(x);
    return (val >= 0.0) ? val : -val;
}

double simpson(double a, double b, int n) {
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double sum = integrand(a) + integrand(b);
    int i;
    for (i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2.0 * integrand(x);
        else
            sum += 4.0 * integrand(x);
    }
    return sum * h / 3.0;
}

double runge_error(double a, double b, int n) {
    double I1 = simpson(a, b, n);
    double I2 = simpson(a, b, n * 2);
    return fabs(I2 - I1) / 15.0;
}

void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void input_limits(double *a, double *b) {

    do {
        printf("\n  Enter lower limit (a): ");
        scanf("%lf", a);
        clear_buffer();

        if (*a < -1000.0) {
            printf("  Error! Value %.2f is too small!\n", *a);
            printf("  Please enter value greater than -1000\n");
        }

    } while (*a < -1000.0);

    do {
        printf("  Enter upper limit (b): ");
        scanf("%lf", b);
        clear_buffer();

        if (*b < -1000.0) {
            printf("  Error! Value %.2f is too small!\n", *b);
            printf("  Please enter value greater than -1000\n");
        }

    } while (*b < -1000.0);

    if (*a > *b) {
        double tmp = *a;
        *a = *b;
        *b = tmp;
        printf("  [Limits swapped: a=%.4f, b=%.4f]\n", *a, *b);
    }
}

void print_function_values(double a, double b, int points) {
    int i;
    printf("\n  f(x) = 2x^3 - x^2 - 5x + 15\n");
    printf("  %-12s %-15s\n", "x", "f(x)");
    printf("  ----------------------------\n");
    double step = (b - a) / (points - 1);
    for (i = 0; i < points; i++) {
        double x = a + i * step;
        printf("  %-12.4f %-15.6f\n", x, f(x));
    }
}

void compute_area(double a, double b) {
    int n;
    printf("\n  Enter number of partitions (e.g. 100): ");
    scanf("%d", &n);
    clear_buffer();

    if (n <= 0) {
        printf("  Error: must be positive!\n");
        return;
    }
    if (n % 2 != 0) {
        n++;
        printf("  Rounded to even: %d\n", n);
    }

    double area  = simpson(a, b, n);
    double error = runge_error(a, b, n);

    printf("\n  ============================================\n");
    printf("  RESULTS:\n");
    printf("  ============================================\n");
    printf("  Interval        : [%.4f, %.4f]\n", a, b);
    printf("  Partitions      : %d\n", n);
    printf("  Area (Simpson)  : %.8f\n", area);
    printf("  Error (Runge)   : %.2e\n", error);
    printf("  ============================================\n");
}

void print_help(void) {
    printf("\n  ============================================\n");
    printf("  HELP:\n");
    printf("  ============================================\n");
    printf("  f(x) = 2x^3 - x^2 - 5x + 15\n\n");
    printf("  Simpson method:\n");
    printf("  I ~ (h/3)*[f(x0)+4f(x1)+2f(x2)+...+f(xn)]\n");
    printf("  h = (b-a)/n\n\n");
    printf("  Runge error estimate:\n");
    printf("  eps = |I(2n) - I(n)| / 15\n");
    printf("  ============================================\n");
}

void show_menu(void) {
    printf("\n");
    printf("  ============================================\n");
    printf("  Lab work #3  |  Variant 9\n");
    printf("  Area under curve (Simpson method)\n");
    printf("  ============================================\n");
    printf("  1. Enter integration limits\n");
    printf("  2. Calculate area\n");
    printf("  3. Print function values\n");
    printf("  4. Help\n");
    printf("  0. Exit\n");
    printf("  ============================================\n");
    printf("  Choose: ");
}

int main(void) {
    int    choice;
    double a = 0.0, b = 1.0;
    int    limits_set = 0;

    do {
        show_menu();

        if (scanf("%d", &choice) != 1) {
            clear_buffer();
            choice = -1;
        } else {
            clear_buffer();
        }

        switch (choice) {
            case 1:
                input_limits(&a, &b);
                limits_set = 1;
                printf("  Limits set: a=%.4f, b=%.4f\n", a, b);
                break;

            case 2:
                if (!limits_set)
                    printf("  Please set limits first (option 1)!\n");
                else
                    compute_area(a, b);
                break;

            case 3:
                if (!limits_set) {
                    printf("  Please set limits first (option 1)!\n");
                } else {
                    int pts;
                    printf("  How many points? ");
                    scanf("%d", &pts);
                    clear_buffer();
                    if (pts < 2) pts = 2;
                    print_function_values(a, b, pts);
                }
                break;

            case 4:
                print_help();
                break;

            case 0:
                printf("\n  Goodbye!\n\n");
                break;

            default:
                printf("  Wrong choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
