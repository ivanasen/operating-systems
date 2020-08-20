// Да се напише продрама на Си, която въвежда в масив 10 цели числа.
// Отпечатва само отрицателните и техния брой.

#include <stdio.h>

int SIZE = 10;

int main() {
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", arr + i);
    }

    for (int i = 0; i < SIZE; i++) {
        if (arr[i] < 0) {
            printf("%d ", arr[i]);
        }
    }
    puts("");

    return 0;
}