#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Student {
    char StudentID[10];
    char firstName[255], lastName[255];
    float mid_score, last_score;
    char final_score[2];
    struct Student *next;
}Student;

typedef struct Subject {
    char subjectID[10];
    char subjectName[255];
    int mid_ratio, last_ratio;
    char semesterID[10];
    int countStudent;
    Student *student;
    struct Subject *next;
}Subject;

void readFileSubject(Subject **rootSubject, char *fileName);

void addNewScoreBoard(Subject **rootSubject);

void addScore(Subject *rootSubject);

void removeScore(Subject *rootSubject);

void searchScore(Subject *rootSubject);

void displayScore(Subject *rootSubject);

void addStudent(Student **rootStudent, Student *newStudent);

void addSubject(Subject **rootSubject, Subject *newSubject);

Student* minScore(Subject *rootSubject, char *subjectID, char *semesterID);

Student* maxScore(Subject *rootSubject, char *subjectID, char *semesterID);

float averageScore(Subject *rootSubject, char *subjectID, char *semesterID);

char *trimRight(char *str);

int lengthStudentList(Student *rootStudent);

Subject *findBySubjectIDAndSemesterID(Subject *rootSubject, char *subjectID, char *semesterID);

Student *findByStudentID(Subject *rootSubject, char *subjectID, char *semesterID, char *id);