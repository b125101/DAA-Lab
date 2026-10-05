/*
DAA Lab-07 - Q2: Super Egg Testing Experiment

Generalized dynamic programming solution for E eggs and F floors.

dp[e][f] = minimum number of drops needed in the worst case
           with e eggs and f floors.

If we drop from floor x:
  - egg breaks: solve e-1 eggs and x-1 floors
  - egg survives: solve e eggs and f-x floors

Therefore:
dp[e][f] = 1 + min over x of
            max(dp[e-1][x-1], dp[e][f-x])

Base cases:
  dp[e][0] = 0
  dp[e][1] = 1
  dp[1][f] = f

Complexity:
  Time  = O(E * F^2)
  Space = O(E * F)
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main(void)
{
    int E, F;

    printf("Enter number of eggs E: ");
    scanf("%d", &E);
    printf("Enter number of floors F: ");
    scanf("%d", &F);

    if (E <= 0 || F < 0) {
        printf("Invalid input.\n");
        return 0;
    }

    int **dp = (int **)malloc((E + 1) * sizeof(int *));
    for (int e = 0; e <= E; e++)
        dp[e] = (int *)malloc((F + 1) * sizeof(int));

    for (int e = 0; e <= E; e++) {
        dp[e][0] = 0;
        if (F >= 1)
            dp[e][1] = 1;
    }

    for (int f = 0; f <= F; f++)
        dp[1][f] = f;

    for (int e = 2; e <= E; e++) {
        for (int f = 2; f <= F; f++) {
            dp[e][f] = INF;

            for (int x = 1; x <= f; x++) {
                int worst = 1 +
                    (dp[e - 1][x - 1] > dp[e][f - x]
                     ? dp[e - 1][x - 1]
                     : dp[e][f - x]);

                if (worst < dp[e][f])
                    dp[e][f] = worst;
            }
        }
    }

    printf("\nMinimum drops for %d eggs and %d floors = %d\n",
           E, F, dp[E][F]);

    if (E == 2 && F == 100)
        printf("For 2 eggs and 100 floors: %d drops.\n", dp[E][F]);

    for (int e = 0; e <= E; e++)
        free(dp[e]);
    free(dp);

    return 0;
}
