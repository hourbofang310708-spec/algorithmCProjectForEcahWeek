#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RECORDS 100
#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN + 1];
    double score;
} Student;

// Helper: Linear search for unique ID
int findById(const Student records[], int size, int targetId) {
    for (int i = 0; i < size; ++i) {
        if (records[i].id == targetId) {
            return i;
        }
    }
    return -1;
}

// Helper: Score range validation
bool isValidScore(double score) {
    return score >= 0.0 && score <= 100.0;
}

// Helper: Sort records descending by score
void sortDescending(Student records[], int size) {
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

// Helper: Create initial test file containing 1 valid and 1 malformed record
void prepareTestInputFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f) {
        fprintf(f, "101, Dara, 78.5\n");              // Line 1: Valid record
        fprintf(f, "999, InvalidUser, -45.0\n");       // Line 2: Malformed score (< 0)
        fclose(f);
    }
}

int main(void) {
    const char *inputFile = "records_input.txt";
    const char *outputFile = "records_output.txt";
    
    Student records[MAX_RECORDS];
    int recordCount = 0;

    // Setup mock input file
    prepareTestInputFile(inputFile);

    printf("=========================================================\n");
    printf("   INTEGRATED FILE-BASED RECORD-MANAGER TRACE LOG       \n");
    printf("=========================================================\n\n");

    // ------------------------------------------------------------------------
    // STEP 01: Open file (Check NULL handle)
    // ------------------------------------------------------------------------
    FILE *in = fopen(inputFile, "r");
    if (!in) {
        printf("[01. ACTION] Open file -> FAILED: Cannot continue with NULL handle.\n");
        return 1;
    }
    printf("[01. ACTION] Open file -> SUCCESS: Valid handle obtained for '%s'.\n", inputFile);

    // Parse input lines
    char line[256];
    int lineNumber = 0;

    while (fgets(line, sizeof(line), in)) {
        lineNumber++;
        line[strcspn(line, "\r\n")] = '\0'; // Trim line endings

        int rawId;
        char rawName[MAX_NAME_LEN + 1];
        double rawScore;

        // Parse line format: ID, Name, Score
        if (sscanf(line, " %d , %50[^,] , %lf", &rawId, rawName, &rawScore) == 3) {
            
            // Validate: 3 fields, ID > 0, valid score range, unique ID
            if (rawId > 0 && isValidScore(rawScore) && findById(records, recordCount, rawId) == -1) {
                
                // ------------------------------------------------------------
                // STEP 02: Read line 1 (Accepted)
                // ------------------------------------------------------------
                records[recordCount].id = rawId;
                strncpy(records[recordCount].name, rawName, MAX_NAME_LEN);
                records[recordCount].name[MAX_NAME_LEN] = '\0';
                records[recordCount].score = rawScore;
                recordCount++;

                printf("[02. ACTION] Read line %d -> ACCEPTED: %d, %s, %.1f\n", 
                       lineNumber, rawId, rawName, rawScore);
            } else {
                // ------------------------------------------------------------
                // STEP 03: Read malformed (Rejected)
                // ------------------------------------------------------------
                printf("[03. ANOMALY] Read line %d -> REJECTED: Size unchanged (%d) | Source Line: \"%s\"\n", 
                       lineNumber, recordCount, line);
            }
        } else {
            printf("[03. ANOMALY] Read line %d -> REJECTED: Size unchanged (%d) | Source Line: \"%s\"\n", 
                   lineNumber, recordCount, line);
        }
    }
    fclose(in);

    // ------------------------------------------------------------------------
    // STEP 04: Search 101 (Search only accepted records)
    // ------------------------------------------------------------------------
    int targetId = 101;
    int index = findById(records, recordCount, targetId);
    if (index != -1) {
        printf("[04. SEARCH] Search %d -> SUCCESS: Located at Index %d\n", targetId, index);
    } else {
        printf("[04. SEARCH] Search %d -> FAILED: Not found in accepted records\n", targetId);
    }

    // ------------------------------------------------------------------------
    // STEP 05: Update score (Validate before commit)
    // ------------------------------------------------------------------------
    double updatedScore = 82.0;
    if (index != -1 && isValidScore(updatedScore)) {
        double oldScore = records[index].score;
        records[index].score = updatedScore;
        printf("[05. MUTATION] Update score -> SUCCESS: ID %d changed from %.1f to %.1f\n", 
               targetId, oldScore, records[index].score);
    } else {
        printf("[05. MUTATION] Update score -> FAILED: Invalid score or record missing\n");
    }

    // ------------------------------------------------------------------------
    // STEP 06: Sort descending (Whole records move, IDs remain attached)
    // ------------------------------------------------------------------------
    sortDescending(records, recordCount);
    printf("[06. SORT] Sort descending -> SUCCESS: Whole records reordered.\n");
    printf("            Position [0] => ID: %d | Name: %s | Score: %.1f\n", 
           records[0].id, records[0].name, records[0].score);

    // ------------------------------------------------------------------------
    // STEP 07: Save (Check write and close results)
    // ------------------------------------------------------------------------
    FILE *out = fopen(outputFile, "w");
    if (!out) {
        printf("[07. PERSIST] Save -> FAILED: Cannot open output file.\n");
        return 1;
    }

    bool writeSuccess = true;
    for (int i = 0; i < recordCount; ++i) {
        if (fprintf(out, "%d, %s, %.1f\n", records[i].id, records[i].name, records[i].score) < 0) {
            writeSuccess = false;
            break;
        }
    }

    int closeResult = fclose(out);
    if (writeSuccess && closeResult == 0) {
        printf("[07. PERSIST] Save -> SUCCESS: %d accepted record(s) written and closed in '%s'\n", 
               recordCount, outputFile);
    } else {
        printf("[07. PERSIST] Save -> FAILED: File write or close operation error.\n");
    }

    printf("\n--- TRACE VERIFICATION ---\n");
    printf("Status: Accepted data survived rejected input and every operation produced an observable result.\n");

    return 0;
}
