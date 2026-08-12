
#include <iostream>
#include <string>
using namespace std;

struct Student {
int id;
string name;
double score;
};

void loadStudents(Student list[], int *count, int capacity) {
FILE *fp = fopen("C:/CC++/C++/text.txt", "r");
if (fp == NULL) {
cout << "Could not open file" << endl;
*count = 0;
return;
}

char line[300];
char nameBuf[50];
int n = 0;
int skipped = 0;

while (n < capacity && fgets(line, sizeof(line), fp) != NULL) {
Student s;

Structured Records • Modular Functions • C++ Text-File Processing

ALGORITHM III | WEEK 3 | STUDENT WORKSHEET

int fields = sscanf(line, "%d|%49[^|]|%lf", &s.id, nameBuf, &s.score);
if (fields == 3 && s.score >= 0 && s.score <= 100) {
s.name = nameBuf;
list[n] = s;
n++;
} else {
skipped++;
}
}

fclose(fp);
*count = n;
printf("Loaded %d record(s), skipped %d malformed line(s).\n", n, skipped);
}

void displayAll(const Student records[], int size) {
for (int i = 0; i < size; i++) {
cout << records[i].id << "|" << records[i].name << "|" << records[i].score <<
endl;
}
}

int findById(const Student records[], int size, int targetId) {
for (int i = 0; i < size; i++) {
if (targetId == records[i].id) return i;
}
return -1;
}

bool updateStudentScore(Student *records, int *size, int *capacity,float newScore, int
targetId) {
if (newScore < 0 || newScore > 100) {
cout << "Invalid score" << endl;
return false;
}
int targetIndex = findById(records, *size, targetId);




