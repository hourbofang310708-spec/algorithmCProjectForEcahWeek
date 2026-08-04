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
