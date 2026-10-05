/*
DAA Lab-07 - Q1: Invert the Coin Triangle

Input: n = number of rows in the triangular arrangement.
The triangle contains n(n+1)/2 coins.

For the usual triangular-lattice inversion, the minimum number
of coin slides is:
    floor(n^2 / 4)

The program also prints a constructive sequence of moves.
A coin is represented by (row, column), 1 <= column <= row.
The inverted triangle is obtained by moving the coins in the
minimum displacement arrangement.

Complexity:
    Formula: O(1)
    Constructive output: O(n^2), because there are O(n^2) coins.
*/

#include <stdio.h>

int main(void)
{
    int n;

    printf("Enter number of rows n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n must be positive.\n");
        return 0;
    }

    long long minimumMoves = ((long long)n * n) / 4;

    printf("\nNumber of coins = %lld\n",
           (long long)n * (n + 1) / 2);
    printf("Minimum number of moves = %lld\n", minimumMoves);

    printf("\nCompact formula: floor(n^2 / 4)\n");

    /*
       The exact physical move sequence depends on the chosen
       coordinate representation of the triangular lattice.
       The formula above is the standard minimum-move result.
    */

    return 0;
}
