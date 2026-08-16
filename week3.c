#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NAME_LEN 50

// Record Structure Definition
typedef struct {
    int id;
    char name[MAX_NAME_LEN + 1];
    double score;
} Student;

// ============================================================================
// PART A — EASY: RECORD FOUNDATIONS
// ============================================================================

// Question 1: Define and print one record
void question1_demo(void) {
    Student s = {101, "Dara", 78.5};
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Score: %.1f\n", s.score);
}

// Question 3: Read-only print function
void printStudent(const Student *s) {
    if (!s) {
        printf("[Invalid Student Pointer]\n");
        return;
    }
    printf("ID: %d | Name: %s | Score: %.1f\n", s->id, s->name, s->score);
}

// Question 4: Validated score update
bool updateScore(Student *s, double value) {
    if (!s || value < 0.0 || value > 100.0) return false;
    s->score = value;
    return true;
}

// ============================================================================
// PART B — MEDIUM: MODULAR RECORD OPERATIONS
// ============================================================================

// Question 6: Display logical records only
void displayAll(const Student records[], int size) {
    if (size <= 0) {
        printf("(No records to display)\n");
        return;
    }
    for (int i = 0; i < size; ++i) {
        printf("[%d] ", i);
        printStudent(&records[i]);
    }
}

// Question 7: Search by unique ID
int findById(const Student records[], int size, int targetId) {
    for (int i = 0; i < size; ++i) {
        if (records[i].id == targetId) {
            return i;
        }
    }
    return -1;
}

// Question 8: Validated add
bool addStudent(Student records[], int *size, int capacity, const Student *candidate) {
    if (!records || !candidate || *size >= capacity) return false;

    // Validate ID
    if (candidate->id <= 0) return false;

    // Validate Name
    size_t nameLen = strlen(candidate->name);
    if (nameLen == 0 || nameLen > MAX_NAME_LEN) return false;

    // Validate Score
    if (candidate->score < 0.0 || candidate->score > 100.0) return false;

    // Check Duplicate ID
    if (findById(records, *size, candidate->id) != -1) return false;

    records[*size] = *candidate;
    (*size)++;
    return true;
}

// Question 9: Search then update
bool updateStudentScore(Student records[], int size, int targetId, double newScore) {
    int index = findById(records, size, targetId);
    if (index == -1) return false;
    return updateScore(&records[index], newScore);
}

// Question 10: Sort complete records descending
void sortByScoreDescending(Student records[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (records[j].score < records[j + 1].score) {
                Student temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

// Question 11: Design a test file generator
void createTestFile(const char *filename) {
    FILE *out = fopen(filename, "w");
    if (!out) return;
    fprintf(out, "101|Dara|78.5\n");
    fprintf(out, "-5|InvalidID|80.0\n");
    fprintf(out, "102|Sopheap|92.0\n");
    fprintf(out, "103||85.0\n");
    fprintf(out, "104|SreyMom|105.0\n");
    fprintf(out, "105|Vibol|abc\n");
    fprintf(out, "101|DuplicateDara|88.0\n");
    fprintf(out, "106|Bopha|65.0\n");
    fprintf(out, "107|ExtraField|70.0|Extra\n");
    fclose(out);
}

// Questions 12 & 13: Robust C file loader
bool loadStudents(const char *filename, Student records[], int *size, 
                  int capacity, int *accepted, int *rejected) {
    FILE *in = fopen(filename, "r");
    if (!in) {
        printf("[Error] Cannot open file: %s\n", filename);
        return false;
    }

    char line[256];
    int lineNumber = 0;
    *accepted = 0;
    *rejected = 0;

    while (fgets(line, sizeof(line), in)) {
        lineNumber++;

        // Strip newline characters
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        // Locate delimiters '|'
        char *p1 = strchr(line, '|');
        char *p2 = p1 ? strchr(p1 + 1, '|') : NULL;
        
        if (!p1 || !p2) {
            printf("Line %d REJECTED: Incomplete fields / Wrong delimiter.\n", lineNumber);
            (*rejected)++;
            continue;
        }

        if (strchr(p2 + 1, '|')) {
            printf("Line %d REJECTED: Extra fields detected.\n", lineNumber);
            (*rejected)++;
            continue;
        }

        // Extract field substrings
        size_t idLen = p1 - line;
        size_t nameLen = p2 - (p1 + 1);
        char *scoreStart = p2 + 1;

        if (idLen >= 64 || nameLen >= 64 || strlen(scoreStart) >= 64) {
            printf("Line %d REJECTED: Field overflow.\n", lineNumber);
            (*rejected)++;
            continue;
        }

        char idStr[64] = {0}, name[64] = {0}, scoreStr[64] = {0};
        strncpy(idStr, line, idLen);
        strncpy(name, p1 + 1, nameLen);
        strcpy(scoreStr, scoreStart);

        // Validate numeric ID
        char *endPtr;
        long idVal = strtol(idStr, &endPtr, 10);
        if (*endPtr != '\0' || idStr[0] == '\0') {
            printf("Line %d REJECTED: Invalid integer for ID ('%s').\n", lineNumber, idStr);
            (*rejected)++;
            continue;
        }
        if (idVal <= 0) {
            printf("Line %d REJECTED: Non-positive ID (%ld).\n", lineNumber, idVal);
            (*rejected)++;
            continue;
        }

        // Validate Name
        if (nameLen == 0 || nameLen > MAX_NAME_LEN) {
            printf("Line %d REJECTED: Invalid name length.\n", lineNumber);
            (*rejected)++;
            continue;
        }

        // Validate Score
        double scoreVal = strtod(scoreStr, &endPtr);
        if (*endPtr != '\0' || scoreStr[0] == '\0') {
            printf("Line %d REJECTED: Invalid double for score ('%s').\n", lineNumber, scoreStr);
            (*rejected)++;
            continue;
        }
        if (scoreVal < 0.0 || scoreVal > 100.0) {
            printf("Line %d REJECTED: Score out of range 0-100 (%.1f).\n", lineNumber, scoreVal);
            (*rejected)++;
            continue;
        }

        // Validate Duplicate ID
        if (findById(records, *size, (int)idVal) != -1) {
            printf("Line %d REJECTED: Duplicate ID (%ld).\n", lineNumber, idVal);
            (*rejected)++;
            continue;
        }

        // Validate Capacity
        if (*size >= capacity) {
            printf("Line %d REJECTED: Collection full (Capacity: %d).\n", lineNumber, capacity);
            (*rejected)++;
            continue;
        }

        // Commit valid record
        records[*size].id = (int)idVal;
        strncpy(records[*size].name, name, MAX_NAME_LEN);
        records[*size].name[MAX_NAME_LEN] = '\0';
        records[*size].score = scoreVal;
        (*size)++;
        (*accepted)++;
    }

    fclose(in);
    return true;
}

// Question 14: Checked save
bool saveStudents(const char *filename, const Student records[], int size) {
    FILE *out = fopen(filename, "w");
    if (!out) return false;

    for (int i = 0; i < size; ++i) {
        if (fprintf(out, "%d|%s|%.1f\n", records[i].id, records[i].name, records[i].score) < 0) {
            fclose(out);
            return false;
        }
    }

    return (fclose(out) == 0);
}

// ============================================================================
// PART C — HARD: FULL RECORD MANAGER
// ============================================================================

// Question 17: Dynamic-array resizing in standard C
bool ensureCapacity(Student **records, int size, int *capacity, int required) {
    if (required <= *capacity) return true;

    int newCap = (*capacity == 0) ? 4 : (*capacity * 2);
    while (newCap < required) {
        newCap *= 2;
    }

    Student *newRecords = (Student *)realloc(*records, newCap * sizeof(Student));
    if (!newRecords) {
        // Preservation Guarantee: Old memory block remains valid on failure
        return false;
    }

    *records = newRecords;
    *capacity = newCap;
    return true;
}

// Question 18: Safe replacement save (atomic overwrite)
bool safeSaveStudents(const char *filename, const Student records[], int size) {
    char tempFilename[256];
    snprintf(tempFilename, sizeof(tempFilename), "%s.tmp", filename);

    FILE *out = fopen(tempFilename, "w");
    if (!out) return false;

    for (int i = 0; i < size; ++i) {
        if (fprintf(out, "%d|%s|%.1f\n", records[i].id, records[i].name, records[i].score) < 0) {
            fclose(out);
            remove(tempFilename);
            return false;
        }
    }

    if (fclose(out) != 0) {
        remove(tempFilename);
        return false;
    }

    remove(filename);
    if (rename(tempFilename, filename) != 0) {
        remove(tempFilename);
        return false;
    }

    return true;
}

// Helper to flush stdin buffer
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Question 16: Menu-driven manager CLI
void menuSystem(Student **records, int *size, int *capacity) {
    int choice = 0;
    while (choice != 8) {
        printf("\n=========================================\n");
        printf("       STUDENT RECORD MANAGER (C)\n");
        printf("=========================================\n");
        printf("1. Load Students from File\n");
        printf("2. Display All Records\n");
        printf("3. Add New Student\n");
        printf("4. Search Student by ID\n");
        printf("5. Update Student Score\n");
        printf("6. Sort Students by Score (Desc)\n");
        printf("7. Save Records to File (Safe Save)\n");
        printf("8. Exit Menu\n");
        printf("Enter choice (1-8): ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid selection! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                char fname[128];
                printf("Enter filename to load [default: students_mixed.txt]: ");
                clearInputBuffer();
                if (!fgets(fname, sizeof(fname), stdin) || fname[0] == '\n') {
                    strcpy(fname, "students_mixed.txt");
                } else {
                    fname[strcspn(fname, "\r\n")] = '\0';
                }

                int acc = 0, rej = 0;
                if (loadStudents(fname, *records, size, *capacity, &acc, &rej)) {
                    printf("Load Complete -> Accepted: %d | Rejected: %d\n", acc, rej);
                }
                break;
            }
            case 2:
                printf("\n--- Current Records (%d/%d) ---\n", *size, *capacity);
                displayAll(*records, *size);
                break;
            case 3: {
                Student candidate;
                printf("Enter ID: ");
                scanf("%d", &candidate.id);
                printf("Enter Name: ");
                scanf("%50s", candidate.name);
                printf("Enter Score: ");
                scanf("%lf", &candidate.score);

                ensureCapacity(records, *size, capacity, *size + 1);
                if (addStudent(*records, size, *capacity, &candidate)) {
                    printf("Student successfully added!\n");
                } else {
                    printf("Failed to add student. Invalid data, duplicate ID, or full capacity.\n");
                }
                break;
            }
            case 4: {
                int searchId;
                printf("Enter ID to search: ");
                scanf("%d", &searchId);
                int idx = findById(*records, *size, searchId);
                if (idx != -1) {
                    printf("Record Found at Index [%d]: ", idx);
                    printStudent(&(*records)[idx]);
                } else {
                    printf("Student with ID %d not found.\n", searchId);
                }
                break;
            }
            case 5: {
                int targetId;
                double newScore;
                printf("Enter ID: ");
                scanf("%d", &targetId);
                printf("Enter New Score (0-100): ");
                scanf("%lf", &newScore);

                if (updateStudentScore(*records, *size, targetId, newScore)) {
                    printf("Score updated successfully!\n");
                } else {
                    printf("Update failed. Student not found or score invalid.\n");
                }
                break;
            }
            case 6:
                sortByScoreDescending(*records, *size);
                printf("Records sorted by score descending!\n");
                break;
            case 7: {
                char fname[128];
                printf("Enter target filename [default: students_output.txt]: ");
                clearInputBuffer();
                if (!fgets(fname, sizeof(fname), stdin) || fname[0] == '\n') {
                    strcpy(fname, "students_output.txt");
                } else {
                    fname[strcspn(fname, "\r\n")] = '\0';
                }

                if (safeSaveStudents(fname, *records, *size)) {
                    printf("Records saved successfully via Safe Replacement Save!\n");
                } else {
                    printf("Failed to save records to file.\n");
                }
                break;
            }
            case 8:
                printf("Exiting menu system...\n");
                break;
            default:
                printf("Invalid option! Enter 1-8.\n");
                break;
        }
    }
}

// Question 20: Integration Proof Driver
void runIntegrationProof(void) {
    printf("\n==================================================\n");
    printf("   RUNNING QUESTION 20: INTEGRATION PROOF TEST    \n");
    printf("==================================================\n");

    const char *inputFile = "students_mixed.txt";
    const char *outputFile = "students_output.txt";

    createTestFile(inputFile);

    int cap = 10;
    int sz = 0;
    Student *arr = (Student *)malloc(cap * sizeof(Student));

    // Load file
    int accepted = 0, rejected = 0;
    printf("\n--- STEP 1: Loading Dataset ---\n");
    loadStudents(inputFile, arr, &sz, cap, &accepted, &rejected);
    printf("Accepted Records: %d | Rejected Records: %d\n", accepted, rejected);

    // Perform updates
    printf("\n--- STEP 2: Performing Updates ---\n");
    printf("Update 101 score to 82.0: %s\n", updateStudentScore(arr, sz, 101, 82.0) ? "SUCCESS" : "FAIL");
    printf("Update 102 score to 105.0 (invalid): %s\n", updateStudentScore(arr, sz, 102, 105.0) ? "SUCCESS" : "FAIL");

    // Perform sort
    printf("\n--- STEP 3: Sorting Records Descending ---\n");
    sortByScoreDescending(arr, sz);
    displayAll(arr, sz);

    // Safe save
    printf("\n--- STEP 4: Safe Saving to %s ---\n", outputFile);
    bool saveStatus = safeSaveStudents(outputFile, arr, sz);
    printf("Save Status: %s\n", saveStatus ? "SUCCESS" : "FAIL");

    // Reload test to verify preservation
    printf("\n--- STEP 5: Reloading Saved Data to Prove Equivalency ---\n");
    int cap2 = 10, sz2 = 0, acc2 = 0, rej2 = 0;
    Student *reloadedArr = (Student *)malloc(cap2 * sizeof(Student));
    loadStudents(outputFile, reloadedArr, &sz2, cap2, &acc2, &rej2);

    bool match = (sz == sz2);
    if (match) {
        for (int i = 0; i < sz; ++i) {
            if (arr[i].id != reloadedArr[i].id || 
                strcmp(arr[i].name, reloadedArr[i].name) != 0 || 
                fabs(arr[i].score - reloadedArr[i].score) > 0.001) {
                match = false;
                break;
            }
        }
    }

    printf("\nPreservation Check: %s\n", match ? "PASSED (Collections are Identical)" : "FAILED");

    free(arr);
    free(reloadedArr);
}

// MAIN FUNCTION — Driver
int main(void) {
    printf("==================================================\n");
    printf("   C RECORD FOUNDATIONS & MANAGEMENT SUITE        \n");
    printf("==================================================\n\n");

    printf("--- Question 1 Output ---\n");
    question1_demo();

    runIntegrationProof();

    int initialCap = 5;
    int initialSize = 0;
    Student *recordsArray = (Student *)malloc(initialCap * sizeof(Student));

    printf("\nStarting Interactive Menu System (Q16)...\n");
    menuSystem(&recordsArray, &initialSize, &initialCap);

    free(recordsArray);
    return 0;
}


#include <stdio.h>
#include <string.h>

// This is our data package structure
typedef struct {
    int id;
    char name[30];
    float score;
} Student;

// The function that runs the 5-step safe save process
int safe_save_database(Student records[], int size) {
    
    // --- STEP 1: OPEN TEMPORARY OUTPUT ---
    // Open a blank temp file with "w" mode. The original file is untouched!
    FILE *temp_fp = fopen("temp_students.txt", "w");
    if (temp_fp == NULL) {
        printf("Error: Could not create temporary file!\n");
        return 0; // Stop immediately. Safety preserved.
    }

    // --- STEP 2 & 3: WRITE ALL RECORDS & CHECK FPRINTF RESULT ---
    // Loop through every single student sitting in active memory
    for (int i = 0; i < size; i++) {
        
        // fprintf prints the active memory data into the temp file
        int result = fprintf(temp_fp, "%d|%s|%.1f\n", 
                             records[i].id, 
                             records[i].name, 
                             records[i].score);
        
        // Check if fprintf failed (returns a negative number if out of space or disconnected)
        if (result < 0) {
            printf("Error: Disk is full or writing broken mid-sentence!\n");
            fclose(temp_fp);            // Close the broken temp file door
            remove("temp_students.txt"); // Throw away the corrupted temp file
            return 0;                   // Exit. Original data is still 100% safe.
        }
    }

    // --- STEP 4: CLOSE AND CHECK FCLOSE ---
    // Lock the temporary file door securely
    if (fclose(temp_fp) != 0) {
        printf("Error: Temporary file failed to close correctly!\n");
        remove("temp_students.txt"); // Throw away temp file if lock fails
        return 0;
    }

    // --- STEP 5: REPLACE ORIGINAL ONLY AFTER SUCCESS ---
    // If we made it here, the temporary file is 100% perfect and complete.
    
    // Delete the old file permanently
    remove("students.txt"); 
    
    // Rename the perfect temp file to become the official database file
    rename("temp_students.txt", "students.txt");

    printf("Success: Database updated safely!\n");
    return 1; // Return 1 to show complete victory
}




   
    
   

   
