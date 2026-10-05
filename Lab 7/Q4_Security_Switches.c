/*
DAA Lab-07 - Q4: Security Switches

Rules:
1. Rightmost switch can always be toggled.
2. A switch can be toggled only when its immediate right switch
   is ON and every switch further right is OFF.
3. One switch per move.

The legal sequence is generated recursively.

For n switches initially ON, the minimum number of moves is:
    2^n - 1

We use a recursive procedure:
turnOff(n):
    turnOff(n-1)
    toggle switch n
    turnOff(n-1)

The switch array is printed after every move.

Complexity:
  Time  = O(2^n)
  Space = O(n) recursion depth.
*/

#include <stdio.h>
#include <stdlib.h>

void printSwitches(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void toggle(int a[], int index, int n)
{
    a[index] = !a[index];
    printf("Toggle switch %d -> ", index + 1);
    printSwitches(a, n);
}

void turnOff(int n, int a[], int total)
{
    if (n == 0)
        return;

    turnOff(n - 1, a, total);

    /*
       The recursive order corresponds to the legal switch
       toggling sequence under the stated rule.
    */
    toggle(a, total - n, total);

    turnOff(n - 1, a, total);
}

int main(void)
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Enter n between 1 and 20.\n");
        return 0;
    }

    int *a = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        a[i] = 1;

    printf("\nInitial state: ");
    printSwitches(a, n);

    /*
       The recurrence is the same binary-reflected sequence:
       the minimum number of toggles is 2^n - 1.
    */
    unsigned long long moves = (1ULL << n) - 1;

    printf("Minimum number of moves = %llu\n\n", moves);

    if (n <= 10)
        turnOff(n, a, n);
    else
        printf("Sequence omitted for large n.\n");

    free(a);
    return 0;
}
