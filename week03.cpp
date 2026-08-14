
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <limits>
#include <new>

using namespace std;
namespace fs = std::filesystem;

// Record Structure Definition
struct Student {
    int id;
    string name;
    double score;
};

// ============================================================================
// PART A — EASY: RECORD FOUNDATIONS
// ============================================================================

// ----------------------------------------------------------------------------
// Question 1: Define and print one record [3 points] - Group 1
// Prompt: Define Student with id, name, and score. Initialize ID 101, name Dara, 
// score 78.5, then print every field.
// ----------------------------------------------------------------------------
void question1_demo() {
    Student s{101, "Dara", 78.5};
    cout << "ID: " << s.id << endl;
    cout << "Name: " << s.name << endl;
    cout << "Score: " << fixed << setprecision(1) << s.score << endl;
}

// ----------------------------------------------------------------------------
// Question 2: Dot versus arrow [3 points] - Group 2
// Prompt: Given Student s and Student *p = &s, write one expression using . and 
// one using -> to read the score. Explain why the operators differ.
//
// Object expression:  s.score
// Pointer expression: p->score  (or (*p).score)
//
// Explanation:
// The dot operator (.) is used for direct member access on an actual object instance.
// The arrow operator (->) is used when accessing members through a pointer to an object.
// The expression `p->score` is syntactically equivalent to `(*p).score`, automatically
// dereferencing the pointer before accessing the member variable.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Question 3: Read-only print function [3 points] - Group 3
// Prompt: Write printStudent(const Student *s) using cout and one decimal place.
// Explain why const is appropriate.
// ----------------------------------------------------------------------------
void printStudent(const Student *s) {
    if (!s) {
        cout << "[Invalid Student Pointer]\n";
        return;
    }
    cout << "ID: " << s->id 
         << " | Name: " << s->name 
         << " | Score: " << fixed << setprecision(1) << s->score << "\n";
}
// Explanation of const:
// Passing a pointer to const (`const Student *`) guarantees read-only semantics. It prevents
// accidental modification of the original student object inside the function while avoiding
// the performance overhead of passing large objects by value (copying std::string).

// ----------------------------------------------------------------------------
// Question 4: Validated score update [3 points] - Group 4
// Prompt: Write updateScore(Student *s, double value). Accept only 0–100.
// Return true on success and false on failure. An invalid value must preserve old score.
// ----------------------------------------------------------------------------
bool updateScore(Student *s, double value) {
    if (!s) return false;
    
    // Validate first
    if (value < 0.0 || value > 100.0) {
        return false;
    }
    
    // Commit second
    s->score = value;
    return true;
}
