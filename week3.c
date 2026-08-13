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

// 01. Parse inputs into temp variables
int temp_id = 101; 
float temp_score = 85.0;

// 02. Validate field rules
if (temp_id <= 0 || temp_score < 0 || temp_score > 100) {
    printf("Rejected: Invalid fields.\n");
    return; 
}

// 03. Search for duplicate ID
for (int i = 0; i < count; i++) {
    if (list[i].id == temp_id) {
        printf("Rejected: Duplicate ID!\n");
        return; // Reject before touching array
    }
}

// 04. Check available capacity
if (count >= MAX) {
    printf("Rejected: Array is full!\n");
    return; 
}

// 05. Commit record; size++
list[count].id = temp_id;
list[count].score = temp_score;
count++; // Increment size only after all checks pass!


FILE *file = fopen("students.txt", "r"); // 01. OPEN
if (file == NULL) return; 

char line[100];
// 02. READ line by line
while (fgets(line, sizeof(line), file) != NULL) { 
    int temp_id;
    char temp_name[30];
    float temp_score;

    // 03. PARSE
    if (sscanf(line, "%d,%29[^,],%f", &temp_id, temp_name, &temp_score) != 3) {
        continue; // Bad format? Skip line!
    }

    // 04. VALIDATE (Rules + Duplicates)
    if (temp_score < 0 || temp_score > 100 || isDuplicate(list, count, temp_id)) {
        continue; // Invalid or duplicate? Skip line!
    }

    // 05. COMMIT
    list[count].id = temp_id;
    strncpy(list[count].name, temp_name, sizeof(list[count].name) - 1);
    list[count].score = temp_score;
    count++;
}

fclose(file); // 06. CLOSE
#include <stdio.h>

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[30];
    float score;
}Student;

int isDuplicateID(const Student list[], int count, int target_id){
    for ( int i = 0; i < count; i ++){
        if ( list[i].id == target_id){
            return 1; // For duplicate found, we return 1
        }
    }
    return 0; //if id is unique, 0
}
void loadStudents(Student list[], int *count, const char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        printf("Could not open the file: %s\n ", filename);
      
      return;
    }
    char line[128];
    int loaded_records = 0;
    int skipped_records = 0;

    while ( fgets(line, sizeof(line), file) != NULL){
        if ( line[0] == '#'|| line[0] == '\n'|| line[0] == '\r'){
            continue;
        }
        int temp_id;
        char temp_name[30];
        float temp_score;

        // Check with the structure 
    
        int parsed = sscanf(line, "%d|%29[^|]|%f", &temp_id, &temp_name, &temp_score);
        if (parsed != 3){
            skipped_records++;// this will be useful later.
            continue;
        }
        // check with the positive id.
        if(temp_id <= 0){
            skipped_records++;
            continue;
        }
        // check the valid score
        if (temp_score<0.0f || temp_score>100.0f){
            skipped_records++;
            continue;
        }
        // Check for duplicate
        if (isDuplicateID(list, *count, temp_id)){
            skipped_records++;
            continue;
        }
        //check for capacity if it is limit or not
        if ( *count >= MAX_STUDENTS ){
            printf("Array capacity is full. Stop reading the next lines. \n");
            break;
        }

        //since we have checked all the condition. we are now can commit

        list[*count].id = temp_id;
        strncyp(list[*count].name, temp_name, sizeof(list[*count].name)-1);
        list[*count].name[sizeof(list[*count].name)-1] = '\0';
        list[*count].score = temp_score;
        (*count)++;
        loaded_records++;
    }
fclose(file);
printf("[SUCCESS] Loaded %d valid record(s). Skipped %d invalid line(s).\n", 
           loaded_records, skipped_records);
}

void displayALL(Student list[], int * count){
    if ( *count == 0){
        printf("Nothing inside the file.\n");
        return;
    }
    printf("ID\tName\t\tScore\n");
    for ( int i = 0; i < count ; i++){
        printf("%d|%c|%.1f\n ", list[i].id , list[i].name, list[i].score);
    }
}
//This code is the process of slide 10 which is the process of testing and is easier for testing paths. 
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

