// // #include <stdio.h>
// // #include <stdlib.h>
// // int main (){
// //     int n;
// //     printf ("Please Enter a number of elements in your array: ");
// //     if (scanf("%d", &n) != 1 || n <= 0){
// //         printf("Invalid input. Please enter a positive integer.\n");
// //         return 1;
// //     }
// //     else {
// //         int *p = ( int *) malloc( (size_t)n * sizeof * p );
// //         if ( p == NULL ){
// //             printf("Memory allocation failed, \n");
// //             return 1;
// //         }
// //         for ( int k = 0; k < n; k++ ){
// //             printf("before input, the %d element of your array is: %d\n", k + 1, *(p+k));
// //         }
// //         for ( int i = 0 ; i < n ; i++ ){
// //                 printf( "please input the %d element of your array:", i + 1);
// //                 if ( scanf("%d", &*(p+i)) != 1 ) {
// //                     printf("Invalid input.Please enter an integer.\n");
// //                     free(p);
// //                     return 1;
// //                 }
// //             }
// //         for ( int j = 0; j < n; j ++){
// //                 printf("after input, the %d element of your array is: %d\n", j + 1, *(p+j));
// //             }
// //             free(p);
// //             p = NULL;       
// //     }
// // }

// #include <stdio.h>
// #include <stdlib.h>
// int main (){
//     int n; 
//     printf ("Please Enter a number of elements in your array: ");
//     if (scanf("%d", &n) != 1 || n <= 0){
//         printf("Invalid input. Please enter a positive integer. \n " );
//         return 1;
//     }else{
//         int *p = ( int *)malloc( (size_t)n * sizeof * p);
//         if ( p == NULL){
//           printf("Memory allocation failed, \n");
//           return 1;
//         } 
//         for ( int i = 0 ; i < n ; i++ ){
//             printf( "please input the %d element of your array:", i + 1);
//             if ( scanf("%d", &*(p+i)) != 1 ) {
//                 printf("Invalid input.Please enter an integer.\n");
//                 free(p);
//                 return 1;
//             }
//         }
//         int max = *p;
//         int min = *p;
//         for ( int j = 0; j < n; j ++){
//             printf("after input, the %d element of your array is: %d\n", j + 1, *(p+j));
//             if ( *(p+j) > max){
//                 max = *(p + j);
//             }
//             if ( *(p+j) < min){
//                 min = *(p + j);
//             }
//         }
//         printf("The maximum element in the array is: %d\n", max);
//         printf("The minimum element in the array is: %d\n", min);
//     free(p);
//     p = NULL;
//     }
// }
//Write a function int sumArray(const int *arr, int n) and use it with a dynamically allocated array.
// #include <stdio.h>
// #include <stdlib.h>
// int sumArray(const int *arr, int n){
//     int sum = 0;
//     for ( int i = 0; i < n; i++){
//         sum += *(arr+i);
//     }
//     return sum;
// }
// int main (){
//     int elements;
//     printf("Please enter the number of elements in your array: ");
//     if (scanf("%d", &elements) != 1 || elements <= 0){
//         printf("Invalid input. Please enter a positive integer.\n");
//         return 1;
//     }
//         int *array = ( int *)malloc ((size_t)elements * sizeof * array);
//         if ( array == NULL ) {
//             printf("Memory allocation failed.\n");
//             return 1;
//         }
//         for ( int i = 0; i < elements; i++){
//             printf("Please input the %d element of your array: ", i + 1);
//             if (scanf("%d", &*(array+i)) != 1){
//                 printf("Invalid input. Please enter an integer.\n");
//                 free(array);
//                 return 1;
//             }
//         }
//         int total_sum = sumArray(array, elements);
//         printf("The sum of all elements in the array is: %d\n", total_sum);
//         free(array);
//         array = NULL;
//     }
// #include <stdio.h>
// #include <stdlib.h>
// int sumArray(const int *arr, int n){
//     int sum = 0;
//     for ( int i = 0; i < n; i++){
//         sum += *(arr+i);
//     }
//     return sum;
// }
// int main (){
//     int elements;
//     printf("Please enter the number of elements in your array: ");
//     if (scanf("%d", &elements) != 1 || elements <= 0){
//         printf("Invalid input. Please enter a positive integer.\n");
//         return 1;
//     }// === LIFETIME START: Allocate dynamic memory ===
//         int *array = ( int *)malloc ((size_t)elements * sizeof * array);
//         if ( array == NULL ) {
//             printf("Memory allocation failed.\n");
//             return 1;
//         }// === LIFETIME ACTIVE: Process and populate the memory ===
//         for ( int i = 0; i < elements; i++){
//             printf("Please input the %d element of your array: ", i + 1);
//             if (scanf("%d", &*(array+i)) != 1){
//                 printf("Invalid input. Please enter an integer.\n");
//                 free(array);
//                 return 1;
//             }// Release memory early if input fails during processing
//         }//=== LIFETIME ACTIVE: Read/use the allocated data ===
//         int total_sum = sumArray(array, elements);
//         printf("The sum of all elements in the array is: %d\n", total_sum);
//         free(array);// Deallocates the heap memory block
//         array = NULL;// Assigns NULL to prevent a dangling pointer
//     }

// one similarity 
// they both allocate memory for that array.

// One difference
// calloc clears the memory, but malloc does not: calloc automatically sets all bytes in the new memory to zero. 
// malloc leaves the old, random data (junk values) inside the memory

// One safety rule is always check for NULL

//Write a complete dynamic score processor: validate n, allocate n scores, 
//handle allocation failure, input scores, compute sum, average, minimum, and maximum, 
//print the results, release memory, and set the pointer to NULL.
// #include <stdio.h>
// #include <stdlib.h>

// int findmin(const int *arr, int n){
//     int min = *arr;
//     for (int i = 0; i < n; i++){
//         if (*(arr + i) < min){
//             min = *(arr + i);
//         }
//     } 
//     return min;
// }

// int findmax(const int *arr, int n){
//     int max = *arr;
//     for (int i = 0; i < n; i++){
//         if (*(arr + i) > max){
//             max = *(arr + i);
//         }
//     } 
//     return max;
// }

// int findsum(const int *arr, int n ){
//     int sum = 0;
//     for (int i = 0; i < n; i ++){
//         sum += *(arr + i);
//     }
//     return sum;
// }

// double findaverage(const int *arr, int n){
//     int sum = findsum(arr, n);
//     return (double)sum / n;
// }

// int main(void){
//     int n;
//     printf("Enter the number of elements in your array: ");
    
//     if (scanf("%d", &n) != 1 || n <= 0) {
//         printf("Invalid input. Please enter a positive integer.\n");
//         return 1;
//     }
//     else {
//         int *array = (int *)malloc((size_t)n * sizeof *array);
//         if (array == NULL){
//             printf("Memory allocation failed.\n");
//             return 1;
//         }
//         for (int i = 0; i < n; i++){
//             printf("Please input the %d element of your array: ", i + 1);
//             if (scanf("%d", &*(array + i)) != 1){
//                 printf("Invalid input. Please enter an integer.\n");
//                 free(array);
//                 array = NULL;
//                 return 1;
//             }
//         }
//         int finalmin = findmin(array, n);
//         int finalmax = findmax(array, n);
//         int finalsum = findsum(array, n);
//         double finalaverage = findaverage(array, n);
        
//         printf("The minimum element in the array is: %d\n", finalmin);
//         printf("The maximum element in the array is: %d\n", finalmax);
//         printf("The sum of all elements in the array is: %d\n", finalsum);
//         printf("The average of all elements in the array is: %.2f\n", finalaverage);
        
//         free(array);
//         array = NULL;
//     }
//     return 0; 
// }
//Write a function int *createArray(int n) that returns a newly allocated integer array or NULL. 
//In main, clearly identify the caller as the owner and release the block correctly.
// #include <stdio.h>
// #include <stdlib.h>
// int *createArray( int n ){
//     if (n <= 0){
//         printf("Invalid input. Please enter a positive integer.\n");
//         return NULL;
//     }
//     int *array = (int *) malloc ( (size_t)n * sizeof * array );
//     if ( array == NULL ){
//         printf("Memory allocation failed.\n");
//     }
//     return array;
// }
// int main (void){
//     int n;
//     printf("enter the number of elements in ur array: " );
//     if ( scanf( "%d", &n) != 1 || n <= 0){
//         printf("Invalid input. Please enter a positive integer.\n");
//         return 1;
//     }
//     else {
//         int *array = createArray(n);
//         if ( array == NULL ){
//             return 1;
//         }
//         for ( int i = 0; i < n; i++){
//             printf("please input the %d element of your array: ", i + 1);
//             if ( scanf("%d", &*(array+i)) != 1){
//                 printf("Invalid input. Please enter an integer.\n");
//                 free(array);
//                 array = NULL;
//                 return 1;
//             }
//         }
//         for ( int j = 0; j < n; j++){
//             printf("the %d element of your array is: %d\n", j + 1, *(array+j));
//         }
//         free(array);
//         array = NULL;
//     }
// }
// #include <stdio.h>
// #include <stdlib.h>
// int main (){
//     int *a = malloc(5 * sizeof *a);
//     for (int i = 0; i <= 5; i++) {
//     a[i] = i; free(a); printf("%d", a[0]); free(a);
//     }
// }
// wrong version 

// here is the correct version of the code:

// #include <stdio.h>
// #include <stdlib.h>

// int main (){
//     int *a = malloc(5 * sizeof *a);
//     if (a == NULL) return 1; 
//     for (int i = 0; i < 5; i++) {
//         a[i] = i; 
//         printf("%d\n", a[i]); 
//     }
//     free(a);
//     a = NULL;

//     return 0;
// }
// // the very wrong version 
// #include <stdio.h>
// #include <stdlib.h>

// int main(void) {
//     int *block = NULL;

//     for (int i = 0; i < 3; i++) {
//         // WRONG: We grab new memory and overwrite the 'block' pointer variable.
//         // The address of the previous memory block is completely lost!
//         block = (int *)malloc(5 * sizeof *block);
        
//         if (block == NULL) return 1;

//         block[0] = (i + 1) * 100;
//         printf("Loop %d: Allocated block at %p\n", i + 1, (void*)block);
//     } // <-- The loop ends here

//     // CRITICAL BUG: This only frees the 3rd (final) block.
//     // Block 1 and Block 2 are trapped in memory forever (Memory Leak).
//     free(block); 
//     block = NULL;

//     return 0;
// }
// // the right version 
// #include <stdio.h>
// #include <stdlib.h>

// int main(void) {
//     // Run the loop 3 times to demonstrate
//     for (int i = 0; i < 3; i++) {
        
//         // 1. ALLOCATION: Grab a unique block for this specific loop turn
//         int *block = (int *)malloc(5 * sizeof *block);
        
//         // Safety check
//         if (block == NULL) {
//             printf("Allocation failed on turn %d\n", i + 1);
//             continue; // Skip to next turn if system is out of memory
//         }

//         // 2. PROCESSING: Use the dynamic memory safely
//         block[0] = (i + 1) * 100;
//         printf("Loop %d: Block allocated at address %p holding value %d\n", 
//                i + 1, (void*)block, block[0]);

//         // 3. RELEASE: Free this exact block before the loop turns again
//         free(block);
//         block = NULL; // Clear pointer before it gets overwritten
        
//         printf("Loop %d: Block successfully cleared.\n\n", i + 1);
//     }

//     return 0;
// }


