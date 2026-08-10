#include <stdio.h>
#include <string.h>

// Define the Record Structure
typedef struct {
    int id;
    char name[30];
    float score;
} Student;

// 1. VALIDATE: Check field rules (Returns 1 if valid, 0 if invalid)
int validateStudent(int id, float score) {
    if (id <= 0) return 0;            // Rule: ID must be positive
    if (score < 0 || score > 100) return 0; // Rule: Score must be between 0 and 100
    return 1;                         // Valid!
}

// 2. DISPLAY: Show one record
void displayStudent(const Student *s) {
    printf("ID: %d | Name: %s | Score: %.1f\n", s->id, s->name, s->score);
}

// 3. SEARCH: Return matching index (-1 if not found)
int searchStudentById(const Student list[], int count, int search_id) {
    for (int i = 0; i < count; i++) {
        if (list[i].id == search_id) {
            return i; // Found matching index
        }
    }
    return -1; // Not found
}

// 4. UPDATE: Change one validated field (Returns 1 on success, 0 on failure)
int updateStudentScore(Student *s, float new_score) {
    if (new_score < 0 || new_score > 100) {
        printf("Update Failed: Invalid score.\n");
        return 0; // Unchanged state
    }
    s->score = new_score; // Commit change
    return 1;             // Success
}

// 5. LOAD: Read-validate-commit (simulating input processing)
int loadStudent(Student *s, int id, const char *name, float score) {
    if (!validateStudent(id, score)) {
        printf("Load Failed: Data failed validation rules.\n");
        return 0; // Reject & do not commit
    }
    // Commit to record
    s->id = id;
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    s.score = score;
    return 1; // Success
}

// 6. SAVE: Write and report status
int saveStudentToFile(const Student *s, FILE *file) {
    if (file == NULL) return 0; // Failure
    fprintf(file, "%d,%s,%.1f\n", s->id, s->name, s->score);
    return 1; // Success
}

int main() {
    Student database[5];
    int count = 0;

    // Test LOAD & VALIDATE
    printf("--- 1. Testing Load ---\n");
    if (loadStudent(&database[0], 101, "Dara", 85.5f)) {
        count++;
        printf("Loaded student successfully!\n");
    }

    // Test DISPLAY
    printf("\n--- 2. Testing Display ---\n");
    displayStudent(&database[0]);

    // Test SEARCH
    printf("\n--- 3. Testing Search ---\n");
    int index = searchStudentById(database, count, 101);
    if (index != -1) {
        printf("Student found at array index: %d\n", index);
    }

    // Test UPDATE
    printf("\n--- 4. Testing Update ---\n");
    if (updateStudentScore(&database[0], 92.0f)) {
        printf("Score updated successfully!\n");
        displayStudent(&database[0]);
    }

    return 0;
}
