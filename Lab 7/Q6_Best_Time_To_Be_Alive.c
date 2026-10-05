/*
DAA Lab-07 - Q6: The Best Time to Be Alive

Input:
  n people, each with birth year and death year.

The problem states that if one person dies in the same year
another is born, the death happens first. Therefore:
  death at year Y must be processed before birth at year Y.

We use a sorted event list:
  birth -> +1
  death -> -1

For equal years, death events are processed before birth events.

Complexity:
  Sorting events: O(n log n)
  Scan: O(n)
  Total: O(n log n)
  Space: O(n)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int type; /* -1 = death, +1 = birth */
} Event;

int compareEvents(const void *a, const void *b)
{
    const Event *x = (const Event *)a;
    const Event *y = (const Event *)b;

    if (x->year != y->year)
        return x->year - y->year;

    /* Death before birth in the same year. */
    return x->type - y->type;
}

int main(void)
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of scientists.\n");
        return 0;
    }

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    for (int i = 0; i < n; i++) {
        int birth, death;

        printf("Enter birth and death year for scientist %d: ",
               i + 1);
        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = +1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++) {
        alive += events[i].type;

        if (alive > maximum) {
            maximum = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nMaximum number alive = %d\n", maximum);
    printf("A time/year with the maximum = %d\n", bestYear);

    free(events);
    return 0;
}
