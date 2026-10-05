/*
DAA Lab-07 - Q7: Matrix Chain Multiplication

Given matrices:
  A1: p[0] x p[1]
  A2: p[1] x p[2]
  ...
  An: p[n-1] x p[n]

Find the minimum number of scalar multiplications and the
corresponding parenthesization.

DP recurrence:
  m[i][j] = min over i <= k < j of
            m[i][k] + m[k+1][j]
            + p[i-1] * p[k] * p[j]

Complexity:
  Time  = O(n^3)
  Space = O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printOptimal(int **split, int i, int j)
{
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");
    printOptimal(split, i, split[i][j]);
    printOptimal(split, split[i][j] + 1, j);
    printf(")");
}

int main(void)
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of matrices.\n");
        return 0;
    }

    long long *p =
        (long long *)malloc((n + 1) * sizeof(long long));

    printf("Enter %d dimensions p0 p1 ... p%d:\n", n + 1, n);
    for (int i = 0; i <= n; i++)
        scanf("%lld", &p[i]);

    long long **m =
        (long long **)malloc((n + 1) * sizeof(long long *));
    int **split =
        (int **)malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++) {
        m[i] = (long long *)malloc((n + 1) * sizeof(long long));
        split[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int length = 2; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            m[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost =
                    m[i][k] +
                    m[k + 1][j] +
                    p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum scalar multiplications = %lld\n",
           m[1][n]);

    printf("Optimal parenthesization = ");
    printOptimal(split, 1, n);
    printf("\n");

    for (int i = 0; i <= n; i++) {
        free(m[i]);
        free(split[i]);
    }

    free(m);
    free(split);
    free(p);

    return 0;
}
