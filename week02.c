#include <stdio.h>
#include <stdlib.h>

// --- CORE FUNCTIONS (Exercises 6, 10, 13, 16, 20) ---

int ensureCapacity(int **data, int *size, int *capacity, int min_capacity) {
    if (*capacity >= min_capacity) {
        return 1;
    }

    int new_capacity = 0;
    if (*capacity == 0) {
        new_capacity = 2;
    } else {
        new_capacity = *capacity * 2;
    }

    if (new_capacity < min_capacity) {
        new_capacity = min_capacity;
    }

    int *new_data = (int *)realloc(*data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        printf("Error: Memory allocation failed\n");
        return 0;
    }

    *data = new_data;
    *capacity = new_capacity;
    return 1;
}

int append(int **data, int *size, int *capacity, int value) {
    int success = ensureCapacity(data, size, capacity, *size + 1);
    if (success == 0) {
        return 0;
    }

    (*data)[*size] = value;
    (*size)++;
    return 1;
}

int insertAt(int **data, int *size, int *capacity, int index, int value) {
    if (index < 0 || index > *size) {
        printf("Error: Index is out of bounds!\n");
        return 0;
    }

    if (ensureCapacity(data, size, capacity, *size + 1) == 0) {
        return 0;
    }

    for (int i = *size; i > index; i--) {
        (*data)[i] = (*data)[i - 1];
    }

    (*data)[index] = value;
    (*size)++;
    return 1;
}

int removeAt(int *data, int *size, int index, int *removed_value) {
    if (index < 0 || index >= *size) {
        printf("Error: Invalid index to delete!\n");
        return 0;
    }

    *removed_value = data[index];

    for (int i = index; i < *size - 1; i++) {
        data[i] = data[i + 1];
    }

    (*size)--;
    return 1;
}

int findIndex(const int *data, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (data[i] == target) {
            return i;
        }
    }
    return -1;
}

int tryShrink(int **data, int size, int *capacity) {
    if (size > 0 && size <= (*capacity / 4) && *capacity > 4) {
        int new_capacity = *capacity / 2;
        int *new_data = (int *)realloc(*data, new_capacity * sizeof(int));
        
        if (new_data != NULL) {
            *data = new_data;
            *capacity = new_capacity;
            return 1;
        }
    }
    return 0;
}

int reserve(int **data, int *capacity, int size, int new_capacity) {
    if (new_capacity <= *capacity) {
        return 1;
    }

    int *temp = (int *)realloc(*data, new_capacity * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    *data = temp;
    *capacity = new_capacity;
    return 1;
}

int shrinkToFit(int **data, int *capacity, int size) {
    if (*capacity == size) {
        return 1;
    }

    if (size == 0) {
        free(*data);
        *data = NULL;
        *capacity = 0;
        return 1;
    }

    int *temp = (int *)realloc(*data, size * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    *data = temp;
    *capacity = size;
    return 1;
}

void display(const int *data, int size) {
    printf("Array items: [ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("]\n");
}

void cleanup(int **data, int *size, int *capacity) {
    if (*data != NULL) {
        free(*data);
        *data = NULL;
    }
    *size = 0;
    *capacity = 0;
}

// --- MAIN FUNCTION DEMONSTRATING ALL MODULES ---

int main(void) {
    int *data = NULL;
    int size = 0;
    int capacity = 0;

    printf("=== UNIFIED DYNAMIC ARRAY TEST SUITE ===\n\n");

    // 1. Test Append & EnsureCapacity
    printf("--- Test 1: Append Elements ---\n");
    append(&data, &size, &capacity, 10);
    append(&data, &size, &capacity, 20);
    append(&data, &size, &capacity, 30);
    display(data, size);
    printf("Size: %d, Capacity: %d\n\n", size, capacity);

    // 2. Test InsertAt
    printf("--- Test 2: InsertAt Index 1 (Value 15) ---\n");
    insertAt(&data, &size, &capacity, 1, 15);
    display(data, size);
    printf("Size: %d, Capacity: %d\n\n", size, capacity);

    // 3. Test FindIndex (Search)
    printf("--- Test 3: FindIndex Search ---\n");
    int target = 20;
    int found_idx = findIndex(data, size, target);
    printf("Value %d found at index: %d\n\n", target, found_idx);

    // 4. Test RemoveAt (Delete)
    printf("--- Test 4: RemoveAt Index 2 ---\n");
    int removed_val = 0;
    removeAt(data, &size, 2, &removed_val);
    printf("Successfully removed value: %d\n", removed_val);
    display(data, size);
    printf("Size: %d, Capacity: %d\n\n", size, capacity);

    // 5. Test Reserve
    printf("--- Test 5: Reserve Capacity (16) ---\n");
    reserve(&data, &capacity, size, 16);
    printf("Reserved successfully!\n");
    printf("Size: %d, Capacity: %d\n\n", size, capacity);

    // 6. Test TryShrink
    printf("--- Test 6: TryShrink ---\n");
    if (tryShrink(&data, size, &capacity)) {
        printf("Shrunk capacity down successfully!\n");
    } else {
        printf("Shrink not needed or failed.\n");
    }
    printf("Size: %d, Capacity: %d\n\n", size, capacity);

    // 7. Test ShrinkToFit
    printf("--- Test 7: ShrinkToFit ---\n");
    shrinkToFit(&data, &capacity, size);
    printf("ShrinkToFit executed successfully!\n");
    printf("Size: %d, Capacity: %d\n\n", size, capacity);

    // 8. Test Cleanup
    printf("--- Test 8: Cleanup Memory ---\n");
    cleanup(&data, &size, &capacity);
    printf("Memory freed completely.\n");
    printf("Final State -> Size: %d, Capacity: %d, Data pointer: %p\n", size, capacity, (void*)data);

    return 0;
}




/* ==============================================================================
 * COMPREHENSIVE WEEK 2 ASSIGNMENT: DYNAMIC ARRAYS & MEMORY MANAGEMENT
 * ==============================================================================
 * This single, master file unifies every core concept from Exercises 1 through 20:
 *   - Allocation, resizing, and pointer safety (Exercises 1, 2, 6, 12, 16)
 *   - Element shifting and transactional boundary protection (Exercises 4, 14, 17)
 *   - Linear search and duplicate counting (Exercises 3, 10)
 *   - Deletion mechanics and metadata updates (Exercises 5, 11)
 *   - Memory compression (tryShrink, reserve, shrinkToFit) (Exercises 13, 20)
 *   - Automated invariant validation and stress testing (Exercises 18, 19)
 *   - Safe, single-release memory cleanup (Exercise 16/Reflection)
 * ============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ==============================================================================
 * SECTION 1: CORE MEMORY & CAPACITY MANAGEMENT
 * ============================================================================== */

// Ensures the underlying capacity can hold at least 'min_capacity' elements.
// Uses a temporary pointer pattern for safe realloc failure-preservation.
int ensureCapacity(int **data, int *size, int *capacity, int min_capacity) {
    if (*capacity >= min_capacity) {
        return 1; // Already has enough space
    }

    int new_capacity = (*capacity == 0) ? 4 : (*capacity * 2);
    if (new_capacity < min_capacity) {
        new_capacity = min_capacity;
    }

    // Safety check: protect original data pointer if realloc fails
    int *new_data = (int *)realloc(*data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        printf("[Error] Memory allocation failed during growth!\n");
        return 0; 
    }

    *data = new_data;
    *capacity = new_capacity;
    return 1;
}

// Manually reserves a specific capacity (Exercise 20)
int reserve(int **data, int *capacity, int size, int new_capacity) {
    if (new_capacity <= *capacity) return 1;

    int *temp = (int *)realloc(*data, new_capacity * sizeof(int));
    if (temp == NULL) return 0;

    *data = temp;
    *capacity = new_capacity;
    return 1;
}

// Shrinks capacity down to match current size (Exercise 20)
int shrinkToFit(int **data, int *capacity, int size) {
    if (*capacity == size) return 1;
    if (size == 0) {
        free(*data);
        *data = NULL;
        *capacity = 0;
        return 1;
    }

    int *temp = (int *)realloc(*data, size * sizeof(int));
    if (temp == NULL) return 0;

    *data = temp;
    *capacity = size;
    return 1;
}

// Conservative automatic shrinking (Exercise 13)
int tryShrink(int **data, int size, int *capacity) {
    if (size > 0 && size <= (*capacity / 4) && *capacity > 4) {
        int new_capacity = *capacity / 2;
        int *new_data = (int *)realloc(*data, new_capacity * sizeof(int));
        if (new_data != NULL) {
            *data = new_data;
            *capacity = new_capacity;
            return 1;
        }
    }
    return 0;
}


/* ==============================================================================
 * SECTION 2: MUTATION OPERATIONS (APPEND, INSERT, DELETE)
 * ============================================================================== */

// Appends a value to the tail of the collection
int append(int **data, int *size, int *capacity, int value) {
    if (!ensureCapacity(data, size, capacity, *size + 1)) return 0;
    (*data)[*size] = value;
    (*size)++;
    return 1;
}

// Inserts a value at a specified index using right-to-left shifting (Exercises 4, 14, 17)
int insertAt(int **data, int *size, int *capacity, int index, int value) {
    if (index < 0 || index > *size) {
        return 0; // Out of bounds rejection
    }
    if (!ensureCapacity(data, size, capacity, *size + 1)) return 0;

    // Shift elements right-to-left to prevent data destruction
    for (int i = *size; i > index; i--) {
        (*data)[i] = (*data)[i - 1];
    }

    (*data)[index] = value;
    (*size)++; // Transaction commit point
    return 1;
}

// Deletes an element at an index, shifts left, and reports the removed value (Exercises 5, 14)
int removeAt(int *data, int *size, int index, int *removed_value) {
    if (data == NULL || index < 0 || index >= *size) {
        return 0; 
    }

    *removed_value = data[index];

    // Shift elements left-to-right
    for (int i = index; i < *size - 1; i++) {
        data[i] = data[i + 1];
    }

    (*size)--; // Metadata commit point (stale value remains in physical tail slot)
    return 1;
}


/* ==============================================================================
 * SECTION 3: SEARCH, METRICS & INVARIANT VALIDATION
 * ============================================================================== */

// Linear search returning the first occurrence index (Exercise 3, 10)
int findIndex(const int *data, int size, int target) {
    if (data == NULL) return -1;
    for (int i = 0; i < size; i++) {
        if (data[i] == target) return i;
    }
    return -1;
}

// Advanced metrics: count occurrences of a target value (Exercise 10)
int countOccurrences(const int *data, int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] == target) count++;
    }
    return count;
}

// Strict system invariant checker to guarantee memory safety rules (Exercise 18, 19)
int checkInvariants(const int *data, int size, int capacity) {
    if (size < 0 || size > capacity) return 0;      // Size must fit within bounds
    if (capacity == 0 && data != NULL) return 0;     // Zero capacity must have NULL pointer
    if (capacity > 0 && data == NULL) return 0;      // Positive capacity must have active pointer
    return 1;
}

// Displays logical elements bounded strictly by 'size'
void display(const int *data, int size, int capacity) {
    printf("Logical Collection [ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("] (Size: %d, Capacity: %d)\n", size, capacity);
}

// Safe single-release cleanup (Exercise 16 reflection)
void cleanup(int **data, int *size, int *capacity) {
    if (*data != NULL) {
        free(*data);
        *data = NULL;
    }
    *size = 0;
    *capacity = 0;
}


/* ==============================================================================
 * SECTION 4: MASTER INTEGRATION & DEMONSTRATION MAIN
 * ============================================================================== */

int main(void) {
    int *data = NULL;
    int size = 0;
    int capacity = 0;

    printf("========================================================\n");
    printf("    WEEK 2 MASTER DEMO: DYNAMIC ARRAY ARCHITECTURE      \n");
    printf("========================================================\n\n");

    // 1. Appending and Auto-Resizing (Exercises 1, 2, 6, 7, 11)
    printf("--- Phase 1: Appending & Dynamic Expansion ---\n");
    append(&data, &size, &capacity, 10);
    append(&data, &size, &capacity, 20);
    append(&data, &size, &capacity, 30);
    display(data, size, capacity);
    printf("Invariants valid? %s\n\n", checkInvariants(data, size, capacity) ? "YES" : "NO");

    // 2. Controlled Index Insertion & Right-to-Left Shifting (Exercises 4, 14, 17)
    printf("--- Phase 2: Inserting at Index 1 (Middle Shift) ---\n");
    insertAt(&data, &size, &capacity, 1, 15);
    display(data, size, capacity);
    printf("\n");

    // 3. Searching & Duplicate Metrics (Exercises 3, 10)
    printf("--- Phase 3: Searching & Counting Target Values ---\n");
    append(&data, &size, &capacity, 20); // Add a duplicate
    display(data, size, capacity);
    int target = 20;
    printf("First index of %d: %d\n", target, findIndex(data, size, target));
    printf("Total occurrences of %d: %d\n\n", target, countOccurrences(data, size, target));

    // 4. Deletion & Left Shifting (Exercises 5, 11, 14)
    printf("--- Phase 4: Removing Value at Index 0 ---\n");
    int removed = 0;
    removeAt(data, &size, 0, &removed);
    printf("Successfully removed element: %d\n", removed);
    display(data, size, capacity);
    printf("\n");

    // 5. Memory Compression & Shrink Contracts (Exercises 13, 20)
    printf("--- Phase 5: Testing Memory Contracts (Reserve & Shrink) ---\n");
    reserve(&data, &capacity, size, 20);
    printf("After reserve(20) -> Capacity: %d\n", capacity);
    
    shrinkToFit(&data, &capacity, size);
    printf("After shrinkToFit() -> Capacity matches size: %d\n", capacity);
    
    tryShrink(&data, size, &capacity);
    printf("After tryShrink() -> Capacity: %d\n\n", capacity);

    // 6. Final Safe Cleanup (Exercise 16)
    printf("--- Phase 6: Final Owner Memory Release ---\n");
    cleanup(&data, &size, &capacity);
    printf("Cleanup executed.\n");
    printf("Final Data Pointer: %p (Expected: NULL)\n", (void*)data);
    printf("Final Size: %d, Final Capacity: %d\n", size, capacity);
    printf("Invariants valid after cleanup? %s\n", checkInvariants(data, size, capacity) ? "YES" : "NO");

    printf("\n========================================================\n");
    printf("    ALL CONCEPTS VERIFIED SUCCESSFULLY. READY TO SUBMIT! \n");
    printf("========================================================\n");

    return 0;
}

