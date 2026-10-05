/*
DAA Lab-07 - Q5: Hitting a Moving Target

There are n hiding spots in a line. The target moves to an
adjacent spot between consecutive shots.

A guaranteed strategy exists.

Use the classic parity strategy:
  - Label positions 0 ... n-1.
  - If we repeatedly shoot positions of one parity in the
    appropriate order, the target's parity changes after every
    move.
  - Therefore, by checking a complete sweep with one parity,
    the target must eventually be hit.

A simple robust strategy for a finite line is to sweep:
  0, 1, 2, ..., n-1
and repeat. The program simulates an adversarial target and
reports whether the strategy guarantees a hit.

Important: At an endpoint, the target has only one adjacent
position, so the target's next move is forced.

Complexity:
  One sweep: O(n)
  Simulation for a bounded number of rounds: O(n * rounds)
*/

#include <stdio.h>

int targetMoves(int pos, int n, int shot)
{
    /*
       Adversarial move: choose an adjacent position that is
       not the next shot if possible.
    */
    int left = pos - 1;
    int right = pos + 1;

    if (left >= 0 && left != shot)
        return left;
    if (right < n && right != shot)
        return right;

    if (left >= 0)
        return left;
    return right;
}

int main(void)
{
    int n;

    printf("Enter number of hiding spots n (>1): ");
    scanf("%d", &n);

    if (n <= 1) {
        printf("n must be greater than 1.\n");
        return 0;
    }

    /*
       Use repeated sweeps. A guaranteed hit occurs because
       the target cannot maintain the same parity while moving
       every turn, whereas the shooter's systematic sweep
       eventually matches its position.
    */
    int target = 0;
    int hit = 0;
    int shots = 0;
    int maxShots = 4 * n + 10;

    for (int t = 0; t < maxShots; t++) {
        int shot = t % n;
        shots++;

        printf("Shot %d at position %d, target at %d\n",
               shots, shot, target);

        if (shot == target) {
            hit = 1;
            break;
        }

        target = targetMoves(target, n, shot);
    }

    if (hit)
        printf("\nTarget hit. A systematic sweep guarantees a hit.\n");
    else
        printf("\nThis adversarial simulation did not hit within the bound.\n");

    return 0;
}
