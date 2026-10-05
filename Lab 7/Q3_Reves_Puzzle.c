/*
DAA Lab-07 - Q3: Reve's Puzzle (4 Peg Tower of Hanoi)

This program uses the Frame-Stewart strategy for the 4-peg
Tower of Hanoi.

Let T[n] be the minimum number of moves for n disks.
Choose k disks to move using 4 pegs, move the remaining n-k
disks using 3 pegs, then move the k disks using 4 pegs:

T[n] = min(2*T[k] + (2^(n-k) - 1)), 1 <= k < n

For n = 8, the optimum is 33 moves.

Complexity:
  DP computation: O(n^2)
  Move generation: proportional to the number of moves.
*/

#include <stdio.h>
#include <limits.h>

#define MAXN 100

unsigned long long pow2minus1(int n)
{
    unsigned long long p = 1;
    for (int i = 0; i < n; i++)
        p *= 2;
    return p - 1;
}

void hanoi3(int n, char from, char to, char aux)
{
    if (n == 0)
        return;

    hanoi3(n - 1, from, aux, to);
    printf("Move disk %d: %c -> %c\n", n, from, to);
    hanoi3(n - 1, aux, to, from);
}

void hanoi4(int n, char from, char to, char aux1, char aux2,
            unsigned long long dp[], int split[])
{
    if (n == 0)
        return;

    if (n == 1) {
        printf("Move disk 1: %c -> %c\n", from, to);
        return;
    }

    int k = split[n];

    hanoi4(k, from, aux1, to, aux2);
    hanoi3(n - k, from, to, aux2);
    hanoi4(k, aux1, to, from, aux2);
}

int main(void)
{
    int n;
    unsigned long long dp[MAXN + 1] = {0};
    int split[MAXN + 1] = {0};

    printf("Enter number of disks (recommended <= 20): ");
    scanf("%d", &n);

    if (n < 1 || n > MAXN) {
        printf("Invalid n.\n");
        return 0;
    }

    dp[0] = 0;
    if (n >= 1) {
        dp[1] = 1;
        split[1] = 0;
    }

    for (int i = 2; i <= n; i++) {
        dp[i] = ULLONG_MAX;
        for (int k = 1; k < i; k++) {
            unsigned long long candidate =
                2 * dp[k] + pow2minus1(i - k);

            if (candidate < dp[i]) {
                dp[i] = candidate;
                split[i] = k;
            }
        }
    }

    printf("\nMinimum moves for %d disks = %llu\n", n, dp[n]);

    if (n == 8)
        printf("Expected result for 8 disks = 33 moves.\n");

    if (dp[n] <= 100000) {
        printf("\nMove sequence:\n");
        hanoi4(n, 'A', 'D', 'B', 'C', dp, split);
    } else {
        printf("Move sequence is too large to print.\n");
    }

    return 0;
}
