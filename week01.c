// Week 1 Exercises – Pointer Tracing and Safe Dynamic allocation 

✅ Easy (5)

1. Trace int x = 8; int *p = &amp;x; and write the meaning and result of x, &amp;x, p, and *p.
2. Given int x = 10; int *p = &amp;x; *p = 25;, state the final values of x and *p and explain why
they match.
3. Write a function void setZero(int *value) and call it with the address of an integer
variable.
4. For int arr[4] = {3, 6, 9, 12}; int *p = arr;, write the values of *p, *(p + 1), and *(p + 3).
5. For an array of length 5, write the first valid index, last valid index, and the first invalid
index after the array.

⚙️ Medium (10)

6. Trace the final values of a, b, and *p: int a = 4, b = 9; int *p = &amp;a; *p += 3; p = &amp;b; *p *=
2;.
7. Write a function void addTen(int *value) that changes the caller’s integer. Demonstrate
the call and output.
8. Input a positive integer n, allocate an integer array of length n with malloc, and print a
clear message if allocation fails.
9. Repeat Exercise 8 with calloc, then print all elements before assigning any new values.
Explain the observed initialization.
10. Allocate an array of n integers, input all values, and print them using pointer notation *(p
+ i).
11. Allocate an array of n integers and calculate its sum and average. Reject n &lt;= 0 before
allocation.
12. Allocate an array of n integers and find the minimum and maximum in one traversal.
13. Write a function int sumArray(const int *arr, int n) and use it with a dynamically allocated
array.
14. Complete a program that allocates, processes, releases, and then assigns NULL to the
owning pointer. Add comments marking the allocation lifetime.
15. Compare malloc(n * sizeof *p) and calloc(n, sizeof *p). State one similarity, one
difference, and one safety rule shared by both.

�� Hard (5)

16. Write a complete dynamic score processor: validate n, allocate n scores, handle
allocation failure, input scores, compute sum, average, minimum, and maximum, print
the results, release memory, and set the pointer to NULL.

17. Write a function int *createArray(int n) that returns a newly allocated integer array or
NULL. In main, clearly identify the caller as the owner and release the block correctly.
18. Find and fix every error in this code: int *a = malloc(5 * sizeof *a); for (int i = 0; i &lt;= 5;
i++) a[i] = i; free(a); printf(&quot;%d&quot;, a[0]); free(a);
19. A program allocates memory inside a loop but frees only the final block. Explain why this
leaks memory and rewrite the loop so every successful allocation has exactly one
matching free.
20. Draw an ownership-and-lifetime diagram for a dynamically allocated array shared
temporarily with a function. Mark the owner, borrower, allocation point, valid-use period,
release point, and any pointer that would become dangling.
�� Required Submission Method
● For tracing questions, show each statement, the pointer target, and the affected value.
● For coding questions, include at least one normal test and one boundary or invalid-input
test.
● Mark the allocation statement, ownership responsibility, and matching free statement.
● Do not execute code that intentionally dereferences NULL, goes out of bounds, uses
freed memory, or frees the same block twice.
● For every correction, explain the error and how you fixed it. Include comments in your code to clarify your reasoning.

//----------------------------------------------solution------------------------------------------------------------

/******************************************************************************
 * PROJECT: Week 1 Exercises - Pointer Tracing and Safe Dynamic Allocation
 * AUTHOR: [Your Name]
 * DESCRIPTION: Interactive console menu showcasing answers, fixes, and
 *              safely-allocated dynamic memory operations.
 * SECURITY: 100% public-safe. Contains no account tokens or private API keys.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// HELPER UTILITIES
// ============================================================================
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_divider(const char *title) {
    printf("\n====================================================================\n");
    printf("  %s\n", title);
    printf("====================================================================\n");
}

// ============================================================================
// CONCEPTUAL AND TRACING ANSWERS (Ex 1, 2, 4, 5, 6, 15, 20)
// ============================================================================
void show_exercise_1(void) {
    print_divider("EXERCISE 1: Pointer Tracing Meaning & Results");
    printf("Trace: int x = 8; int *p = &x;\n\n");
    printf("1. x  : The actual variable holding the value.\n"
           "        Result: 8\n");
    printf("2. &x : The exact memory address of variable x.\n"
           "        Result: [System Dependent Address]\n");
    printf("3. p  : The pointer variable that holds the memory address of x.\n"
           "        Result: Address of x\n");
    printf("4. *p : The dereference operator looking inside p to read the value.\n"
           "        Result: 8\n");
}

void show_exercise_2(void) {
    print_divider("EXERCISE 2: Value Modification via Dereferencing");
    printf("Given: int x = 10; int *p = &x; *p = 25;\n\n");
    printf("Final Value of x  : 25\n");
    printf("Final Value of *p : 25\n");
    printf("Explanation       : *p modifies the contents of the memory address\n"
           "                    it points to. Since p points to x, assigning 25\n"
           "                    to *p directly changes the value of x.\n");
}

void show_exercise_4(void) {
    print_divider("EXERCISE 4: Array Element Pointer Arithmetic");
    printf("Given: int arr[4] = {3, 6, 9, 12}; int *p = arr;\n\n");
    printf("Value of *p     (arr[0]) : %d\n", 3);
    printf("Value of *(p+1) (arr[1]) : %d\n", 6);
    printf("Value of *(p+3) (arr[3]) : %d\n", 12);
}

void show_exercise_5(void) {
    print_divider("EXERCISE 5: Array Boundary Index Evaluation");
    printf("For an array of length 5:\n\n");
    printf("First valid index               : 0\n");
    printf("Last valid index                : 4\n");
    printf("First invalid index after array : 5\n");
}

void show_exercise_6(void) {
    print_divider("EXERCISE 6: Complex Multi-step Pointer Tracing");
    printf("Trace: int a = 4, b = 9; int *p = &a; *p += 3; p = &b; *p *= 2;\n\n");
    printf("Final Value of a  : 7  (4 + 3)\n");
    printf("Final Value of b  : 18 (9 * 2)\n");
    printf("Final Value of *p : 18 (Points to b)\n");
}

void show_exercise_15(void) {
    print_divider("EXERCISE 15: Comparison of malloc vs calloc");
    printf("Similarity : Both allocate dynamic heap space for an array.\n");
    printf("Difference : calloc zeroes out the allocated memory block, whereas\n"
           "             malloc leaves uninitialized random junk values.\n");
    printf("Safety Rule: Always perform a NULL check immediately after allocating.\n");
}

void show_exercise_20(void) {
    print_divider("EXERCISE 20: Ownership and Lifetime Model");
    printf("Diagram Mapping:\n\n"
           "  [Allocation Point] ---> Managed inside main() via malloc/calloc\n"
           "  [Owner]            ---> main() retains primary ownership responsibility\n"
           "  [Borrower]         ---> Worker functions take a pointer temporary view\n"
           "  [Valid-use Period] ---> From verified allocation to the free() call\n"
           "  [Release Point]    ---> free(p) execution releases heap slots back\n"
           "  [Dangling Pointer] ---> Solved by assigning p = NULL directly after\n");
}

// ============================================================================
// PRACTICAL CODING EXERCISES (Ex 3, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19)
// ============================================================================

// Ex 3
void setZero(int *value) {
    if (value != NULL) {
        *value = 0;
    }
}
void run_exercise_3(void) {
    print_divider("EXERCISE 3: Passing Pointer to Function");
    int num = 5;
    printf("Before setZero: %d\n", num);
    setZero(&num);
    printf("After setZero : %d\n", num);
}

// Ex 7
void addTen(int *value) {
    if (value != NULL) {
        *value += 10;
    }
}
void run_exercise_7(void) {
    print_divider("EXERCISE 7: Mutating Caller State");
    int num;
    printf("Input an integer: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input error.\n");
        clear_input_buffer();
        return;
    }
    printf("Value before change: %d\n", num);
    addTen(&num);
    printf("Value after addTen : %d\n", num);
}

// Ex 8
void run_exercise_8(void) {
    print_divider("EXERCISE 8: Dynamic Malloc Tracking");
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        clear_input_buffer();
        return;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(*arr));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid entry.\n");
            free(arr);
            clear_input_buffer();
            return;
        }
    }

    printf("Array values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;
}

// Ex 9
void run_exercise_9(void) {
    print_divider("EXERCISE 9: Calloc Initialization Check");
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Please enter a positive integer.\n");
        clear_input_buffer();
        return;
    }

    int *arr = (int *)calloc((size_t)n, sizeof(*arr));
    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    printf("\n--- Initial Values (allocated with calloc) ---\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: %d\n", i + 1, arr[i]);
    }

    printf("\n--- Enter New Values ---\n");
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error: Invalid entry.\n");
            free(arr);
            clear_input_buffer();
            return;
        }
    }

    printf("\n--- Updated Values ---\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: %d\n", i + 1, arr[i]);
    }

    free(arr);
    arr = NULL;
}

// Ex 10
void run_exercise_10(void) {
    print_divider("EXERCISE 10: Array Access using *(p + i) Notation");
    int n;
    printf("Please Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
    }

    int *p = (int *)malloc((size_t)n * sizeof(*p));
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Reading current raw junk indices values:\n");
    for (int k = 0; k < n; k++) {
        printf("Before input, index %d holds: %d\n", k + 1, *(p + k));
    }

    for (int i = 0; i < n; i++) {
        printf("Please input element %d: ", i + 1);
        if (scanf("%d", &*(p + i)) != 1) {
            printf("Invalid data entered.\n");
            free(p);
            clear_input_buffer();
            return;
        }
    }

    printf("Result values using pointer offset syntax:\n");
    for (int j = 0; j < n; j++) {
        printf("Element %d: %d\n", j + 1, *(p + j));
    }

    free(p);
    p = NULL;
}

// Ex 11
void run_exercise_11(void) {
    print_divider("EXERCISE 11: Dynamic Sum and Average Calculations");
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input bounds checked.\n");
        clear_input_buffer();
        return;
    }

    int *p = (int *)malloc((size_t)n * sizeof(*p));
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &*(p + i)) != 1) {
            printf("Parsing error.\n");
            free(p);
            clear_input_buffer();
            return;
        }
        sum += *(p + i);
    }

    double average = (double)sum / n;
    printf("The sum of elements is: %d\n", sum);
    printf("The average of elements is: %.2f\n", average);

    free(p);
    p = NULL;
}

// Ex 12
void run_exercise_12(void) {
    print_divider("EXERCISE 12: Single-Traversal Min and Max Tracking");
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size bounded check failed.\n");
        clear_input_buffer();
        return;
    }

    int *p = (int *)malloc((size_t)n * sizeof(*p));
    if (p == NULL) {
        printf("Allocation error.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &*(p + i)) != 1) {
// Ex 13
#include <stdio.h>
#include <stdlib.h>
int sumArray(const int *arr, int n){
    int sum = 0;
    for ( int i = 0; i < n; i++){
        sum += *(arr+i);
    }
    return sum;
}
int main (){
    int elements;
    printf("Please enter the number of elements in your array: ");
    if (scanf("%d", &elements) != 1 || elements <= 0){
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
        int *array = ( int *)malloc ((size_t)elements * sizeof * array);
        if ( array == NULL ) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        for ( int i = 0; i < elements; i++){
            printf("Please input the %d element of your array: ", i + 1);
            if (scanf("%d", &*(array+i)) != 1){
                printf("Invalid input. Please enter an integer.\n");
                free(array);
                return 1;
            }
        }
        int total_sum = sumArray(array, elements);
        printf("The sum of all elements in the array is: %d\n", total_sum);
        free(array);
        array = NULL;
    }
//Ex 14
#include <stdio.h>
#include <stdlib.h>
int sumArray(const int *arr, int n){
    int sum = 0;
    for ( int i = 0; i < n; i++){
        sum += *(arr+i);
    }
    return sum;
}
int main (){
    int elements;
    printf("Please enter the number of elements in your array: ");
    if (scanf("%d", &elements) != 1 || elements <= 0){
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }// === LIFETIME START: Allocate dynamic memory ===
        int *array = ( int *)malloc ((size_t)elements * sizeof * array);
        if ( array == NULL ) {
            printf("Memory allocation failed.\n");
            return 1;
        }// === LIFETIME ACTIVE: Process and populate the memory ===
        for ( int i = 0; i < elements; i++){
            printf("Please input the %d element of your array: ", i + 1);
            if (scanf("%d", &*(array+i)) != 1){
                printf("Invalid input. Please enter an integer.\n");
                free(array);
                return 1;
            }// Release memory early if input fails during processing
        }//=== LIFETIME ACTIVE: Read/use the allocated data ===
        int total_sum = sumArray(array, elements);
        printf("The sum of all elements in the array is: %d\n", total_sum);
        free(array);// Deallocates the heap memory block
        array = NULL;// Assigns NULL to prevent a dangling pointer
    }
//Ex 16
#include <stdio.h>
#include <stdlib.h>


int findmin(const int *arr, int n){
    int min = *arr;
    for (int i = 0; i < n; i++){
        if (*(arr + i) < min){
            min = *(arr + i);
        }
    }
    return min;
}


int findmax(const int *arr, int n){
    int max = *arr;
    for (int i = 0; i < n; i++){
        if (*(arr + i) > max){
            max = *(arr + i);
        }
    }
    return max;
}


int findsum(const int *arr, int n ){
    int sum = 0;
    for (int i = 0; i < n; i ++){
        sum += *(arr + i);
    }
    return sum;
}


double findaverage(const int *arr, int n){
    int sum = findsum(arr, n);
    return (double)sum / n;
}


int main(void){
    int n;
    printf("Enter the number of elements in your array: ");
   
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    else {
        int *array = (int *)malloc((size_t)n * sizeof *array);
        if (array == NULL){
            printf("Memory allocation failed.\n");
            return 1;
        }
        for (int i = 0; i < n; i++){
            printf("Please input the %d element of your array: ", i + 1);
            if (scanf("%d", &*(array + i)) != 1){
                printf("Invalid input. Please enter an integer.\n");
                free(array);
                array = NULL;
                return 1;
            }
        }
        int finalmin = findmin(array, n);
        int finalmax = findmax(array, n);
        int finalsum = findsum(array, n);
        double finalaverage = findaverage(array, n);
       
        printf("The minimum element in the array is: %d\n", finalmin);
        printf("The maximum element in the array is: %d\n", finalmax);
        printf("The sum of all elements in the array is: %d\n", finalsum);
        printf("The average of all elements in the array is: %.2f\n", finalaverage);
       
        free(array);
        array = NULL;
    }
    return 0;
}
//Ex 17
#include <stdio.h>
#include <stdlib.h>
int *createArray( int n ){
    if (n <= 0){
        printf("Invalid input. Please enter a positive integer.\n");
        return NULL;
    }
    int *array = (int *) malloc ( (size_t)n * sizeof * array );
    if ( array == NULL ){
        printf("Memory allocation failed.\n");
    }
    return array;
}
int main (void){
    int n;
    printf("enter the number of elements in ur array: " );
    if ( scanf( "%d", &n) != 1 || n <= 0){
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    else {
        int *array = createArray(n);
        if ( array == NULL ){
            return 1;
        }
        for ( int i = 0; i < n; i++){
            printf("please input the %d element of your array: ", i + 1);
            if ( scanf("%d", &*(array+i)) != 1){
                printf("Invalid input. Please enter an integer.\n");
                free(array);
                array = NULL;
                return 1;
            }
        }
        for ( int j = 0; j < n; j++){
            printf("the %d element of your array is: %d\n", j + 1, *(array+j));
        }
        free(array);
        array = NULL;
    }
}
//Ex 18
int main (){
    int *a = malloc(5 * sizeof *a);
    for (int i = 0; i <= 5; i++) {
    a[i] = i; free(a); printf("%d", a[0]); free(a);
    }
}
wrong version


here is the correct version of the code:


#include <stdio.h>
#include <stdlib.h>


int main (){
    int *a = malloc(5 * sizeof *a);
    if (a == NULL) return 1;
    for (int i = 0; i < 5; i++) {
        a[i] = i;
        printf("%d\n", a[i]);
    }
    free(a);
    a = NULL;


    return 0;
}
// Ex 19
// the very wrong version
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int *block = NULL;


    for (int i = 0; i < 3; i++) {
        // WRONG: We grab new memory and overwrite the 'block' pointer variable.
        // The address of the previous memory block is completely lost!
        block = (int *)malloc(5 * sizeof *block);
       
        if (block == NULL) return 1;


        block[0] = (i + 1) * 100;
        printf("Loop %d: Allocated block at %p\n", i + 1, (void*)block);
    } // <-- The loop ends here


    // CRITICAL BUG: This only frees the 3rd (final) block.
    // Block 1 and Block 2 are trapped in memory forever (Memory Leak).
    free(block);
    block = NULL;


    return 0;
}
// the right version
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    // Run the loop 3 times to demonstrate
    for (int i = 0; i < 3; i++) {
       
        // 1. ALLOCATION: Grab a unique block for this specific loop turn
        int *block = (int *)malloc(5 * sizeof *block);
       
        // Safety check
        if (block == NULL) {
            printf("Allocation failed on turn %d\n", i + 1);
            continue; // Skip to next turn if system is out of memory
        }


        // 2. PROCESSING: Use the dynamic memory safely
        block[0] = (i + 1) * 100;
        printf("Loop %d: Block allocated at address %p holding value %d\n",
               i + 1, (void*)block, block[0]);


        // 3. RELEASE: Free this exact block before the loop turns again
        free(block);
        block = NULL; // Clear pointer before it gets overwritten
       
        printf("Loop %d: Block successfully cleared.\n\n", i + 1);
    }


    return 0;
}
// done



