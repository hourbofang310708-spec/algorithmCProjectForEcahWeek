#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Please enter a positive integer.\n");
        return 1;
    }

    int *arr = calloc((size_t)n, sizeof(*arr));
    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    printf("\n--- Initial Values (allocated with calloc) ---\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: %d\n", i + 1, arr[i]);
    }

    // Safely collect user input
    printf("\n--- Enter New Values ---\n");
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error: Invalid input. Please enter an integer.\n");
            free(arr);
            return 1;
        }
    }

    // Display updated values
    printf("\n--- Updated Values ---\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: %d\n", i + 1, arr[i]);
    }

    // Clean up memory
    free(arr);
    arr = NULL;

    return 0;
}
