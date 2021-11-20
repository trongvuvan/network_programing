#include "subject.h"

void addStudent(Student **rootStudent, Student *newStudent) {
    if((*rootStudent) == NULL) {
        *rootStudent = newStudent;
    }else {
        newStudent->next = *rootStudent;
        *rootStudent = newStudent;
    }
};

void addSubject(Subject **rootSubject, Subject *newSubject) {
    if(*rootSubject == NULL) {
        *rootSubject = newSubject;
    }else {
        newSubject->next = *rootSubject;
        *rootSubject = newSubject;
    }
};

Subject *findBySubjectIDAndSemesterID(Subject *rootSubject, char *subjectID, char *semesterID) {
    for(Subject *subject = rootSubject; subject; subject = subject->next) {
        if(strcmp(subject->subjectID, subjectID) == 0 && strcmp(subject->semesterID, semesterID) == 0) {
            return subject;
        }
    }
    return NULL;
};

Student *findByStudentID(Subject *rootSubject, char *subjectID, char *semesterID, char *studentID) {
    Subject *subject = rootSubject;
    for(; subject; subject = subject->next) {
        if(strcmp(subject->subjectID, subjectID) == 0) {
            if(strcmp(subject->semesterID, semesterID) == 0) {
                for(Student *student = subject->student; student; student = student->next) {
                    if(strcmp(student->StudentID, studentID) == 0) {
                        return student;
                    }
                }
            }
        }
    }
    return NULL;
};

void readFileSubject(Subject **rootSubject, char *fileName) {
    FILE *file = fopen(fileName, "r");
    char str[255], *token, delimiter[2] = "|";
    Subject *subject = (Subject*)malloc(sizeof(Subject));
    while(fgets(str, 255, file) != NULL) {
        token = strtok(str, delimiter);
        if(strcmp(token, "SubjectID") == 0) {
            token = strtok(NULL, delimiter);
            strcpy(subject->subjectID, trimRight(token));
        }else if(strcmp(token, "Subject") == 0) {
            token = strtok(NULL, delimiter);
            strcpy(subject->subjectName, trimRight(token));
        }else if(strcmp(token, "F") == 0) {
            token = strtok(NULL, delimiter);
            sscanf(token, "%d", &(subject->mid_ratio));
            subject->last_ratio = 100 - subject->mid_ratio;
        }else if(strcmp(token, "Semester") == 0) {
            token = strtok(NULL, delimiter);
            strcpy(subject->semesterID, trimRight(token));
        }else if(strcmp(token, "StudentCount") == 0) {
            token = strtok(NULL, delimiter);
            sscanf(token, "%d", &(subject->countStudent));
        }else if(strcmp(token, "S") == 0){
            Student* student = (Student*)malloc(sizeof(Student));
            token = strtok(NULL, delimiter);
            strcpy(student->StudentID, token);
            token = strtok(NULL, delimiter);
            strcpy(student->firstName, token);
            token = strtok(NULL, delimiter);
            strcpy(student->lastName, token);
            token = strtok(NULL, delimiter);
            sscanf(token, "%f", &(student->mid_score));
            token = strtok(NULL, delimiter);
            sscanf(token, "%f", &(student->last_score));
            token = strtok(NULL, delimiter);
            strcpy(student->final_score, token);
            addStudent(&(subject->student), student);
            student = NULL;
            free(student);
        }
    }
    fclose(file);
    addSubject(rootSubject, subject);
    subject = NULL;
    free(subject);
};

void addNewScoreBoard(Subject **rootSubject) {
    char fileName[50];
    Subject *subject = (Subject*)malloc(sizeof(Subject));
    printf("Moi nhap ma mon hoc: ");
    scanf("%s", subject->subjectID);
    getchar();
    printf("Moi nhap ten mon hoc: ");
    fgets(subject->subjectName, sizeof(subject->subjectName) + 1, stdin);
    strcpy(subject->subjectName, trimRight(subject->subjectName));
    printf("Moi nhap he so giua ky: ");
    scanf("%d", &subject->mid_ratio);
    subject->last_ratio = 100 - subject->mid_ratio;
    getchar();
    printf("Moi nhap ma hoc ky: ");
    fgets(subject->semesterID, sizeof(subject->semesterID) + 1, stdin);
    strcpy(subject->semesterID, trimRight(subject->semesterID));
    printf("Moi nhap so luong sinh vien: ");
    scanf("%d", &subject->countStudent);
    getchar();
    printf("***************************\n");

    strcpy(fileName, subject->subjectID);
    strcat(fileName, "_");
    strcat(fileName, subject->semesterID);
    strcat(fileName, ".txt");

    FILE *file = fopen(fileName, "w");
    fprintf(file, "SubjectID|%s\n", subject->subjectID);
    fprintf(file, "Subject|%s\n", subject->subjectName);
    fprintf(file, "F|%d|%d\n", subject->mid_ratio, subject->last_ratio);
    fprintf(file, "Semester|%s\n", subject->semesterID);
    fprintf(file, "StudentCount|%d\n", (subject->countStudent));

    fclose(file);

    addSubject(rootSubject, subject);
    subject = NULL;
    free(subject);
};

void addScore(Subject *rootSubject) {
    char subjectID[10], semesterID[10], fileName[50], studentID[10], firstName[20], lastName[25], anphaScore[2];
    float gk, ck, score;
    printf("Moi nhap ma mon hoc: ");
    fgets(subjectID, sizeof(subjectID) + 1, stdin);
    strcpy(subjectID, trimRight(subjectID));
    printf("Moi nhap ma hoc ky: ");
    scanf("%s", semesterID);
    getchar();
    Subject *subject = findBySubjectIDAndSemesterID(rootSubject, subjectID, semesterID);
    if(subject != NULL) {
        if(subject->countStudent == lengthStudentList(subject->student)) {
            printf("Da day danh sach sinh vien");
            return;
        }
        printf("Moi nhap ma sinh vien: ");
        scanf("%s", studentID);
        getchar();
        printf("Moi nhap ho ten dem sinh vien: ");
        fgets(firstName, sizeof(firstName) + 1, stdin);
        strcpy(firstName, trimRight(firstName));
        printf("Moi nhap ten sinh vien: ");
        fgets(lastName, sizeof(lastName) + 1, stdin);
        strcpy(lastName, trimRight(lastName));
        printf("Moi nhap diem gk: ");
        scanf("%f", &gk);
        printf("Moi nhap diem ck: ");
        scanf("%f", &ck);
        score = (gk * subject->mid_ratio + ck * subject->last_ratio) / 100;
        if(score >= 8.5) {
            strcpy(anphaScore, "A");
        }else if(score >= 7.0 && score <= 8.4) {
            strcpy(anphaScore, "B");
        }else if(score >= 5.5 && score < 7.0) {
            strcpy(anphaScore, "C");
        }else if(score >= 4.0 && score < 5.5) {
            strcpy(anphaScore, "D");
        }else {
            strcpy(anphaScore, "F");
        }
        printf("***************************\n");
        strcpy(fileName, subjectID);
        strcat(fileName, "_");
        strcat(fileName, semesterID);
        strcat(fileName, ".txt");

        FILE *file = fopen(fileName, "a+");
        fprintf(file, "S|%s|%s|%s|%.1f|%.1f|%s|\n", studentID, firstName, lastName, gk, ck, anphaScore);
        fclose(file);
    }else {
        printf("Khong tim thay ma mon hoc hoac ma hoc ky: ");
        return;
    }
};

int lengthStudentList(Student *rootStudent) {
    int count = 0;
    for(Student *student = rootStudent; student; student = student->next) {
        count++;
    }
    return count;
};

void removeScore(Subject *rootSubject) {
    char subjectID[10], semesterID[10], studentID[10], fileName[50];
    printf("Moi nhap ma mon hoc: ");
    fgets(subjectID, sizeof(subjectID) + 1, stdin);
    strcpy(subjectID, trimRight(subjectID));
    printf("Moi nhap ma hoc ky: ");
    scanf("%s", semesterID);
    printf("Moi nhap ma sinh vien: ");
    scanf("%s", studentID);

    printf("***************************\n");

    strcpy(fileName, subjectID);
    strcat(fileName, "_");
    strcat(fileName, semesterID);
    strcat(fileName, ".txt");

    Subject *subject = findBySubjectIDAndSemesterID(rootSubject, subjectID, semesterID);

    FILE *file = fopen(fileName, "w");
    fprintf(file, "SubjectID|%s\n", subjectID);
    fprintf(file, "Subject|%s\n", subject->subjectName);
    fprintf(file, "F|%d|%d\n", subject->mid_ratio, subject->last_ratio);
    fprintf(file, "Semester|%s\n", semesterID);
    fprintf(file, "StudentCount|%d\n", (subject->countStudent));

    for(Student *student = subject->student; student; student = student->next) {
        if(strcmp(student->StudentID, studentID) == 0) {
            fprintf(file, "S|%s|%s|%s| | | |\n", student->StudentID, student->firstName, student->lastName);
            continue;
        }
        fprintf(file, "S|%s|%s|%s|%.1f|%.1f|%s|\n", student->StudentID, student->firstName, student->lastName, student->mid_score, student->last_score, student->final_score);
    }

    fclose(file);
};

bool isAnphaCharacter(char c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        return true;
    }
    return false;
};

char *trimRight(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(isAnphaCharacter(str[i]) || (!isAnphaCharacter(str[i]) && isAnphaCharacter(str[i+1]))) {
            continue;
        }
        str[i] = '\0';
    }
    return str;
};

Student* minScore(Subject *rootSubject, char *subjectID, char *semesterID) {
    Subject *subject = findBySubjectIDAndSemesterID(rootSubject, subjectID, semesterID);
    if(subject->student == NULL) {
        return NULL;
    }
    Student *student = subject->student;
    Student *minStudent;
    float min = student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio;
    for(; student; student = student->next) {
        if(min >= student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio) {
            min = student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio;
            minStudent = student;
        }
    }
    free(student);
    return minStudent;
};

Student* maxScore(Subject *rootSubject, char *subjectID, char *semesterID) {
    Subject *subject = findBySubjectIDAndSemesterID(rootSubject, subjectID, semesterID);
    if(subject->student == NULL) {
        return NULL;
    }
    Student *student = subject->student;
    Student *maxStudent;
    float max = student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio;
    for(; student; student = student->next) {
        if(max <= student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio) {
            max = student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio;
            maxStudent = student;
        }
    }
    student = NULL;
    free(student);
    return maxStudent;
};

float averageScore(Subject *rootSubject, char *subjectID, char *semesterID) {
    Subject *subject = findBySubjectIDAndSemesterID(rootSubject, subjectID, semesterID);
    if(subject == NULL){ 
        return 0;
    }
    float sum = 0;
    for(Student *student = subject->student; student; student = student->next) {
        sum += student->mid_score * subject->mid_ratio + student->last_score * subject->last_ratio;
    }
    return sum / subject->countStudent;
};

void searchScore(Subject *rootSubject) {
    char subjectID[10], semesterID[10], studentID[10];
    printf("Moi nhap ma mon hoc: ");
    scanf("%s", subjectID);
    printf("Moi nhap ma hoc ky: ");
    scanf("%s", semesterID);
    printf("Moi nhap ma so sinh vien: ");
    scanf("%s", studentID);

    Student *student = findByStudentID(rootSubject, subjectID, semesterID, studentID);

    if(student != NULL) {
        printf("Tim thay sinh vien\n");
    }else {
        printf("Khong tim thay sinh vien !!!\n");
    }

    printf("***************************\n");
};

void displayScore(Subject *rootSubject) {
    char subjectID[10], semesterID[10], fileName[50];
    int arrPoint[5]={0,0,0,0,0};
    char anphaPoint[5] = {'A', 'B', 'C', 'D', 'F'};
    printf("Moi nhap ma mon hoc: ");
    fgets(subjectID, sizeof(subjectID) + 1, stdin);
    strcpy(subjectID, trimRight(subjectID));
    printf("Moi nhap ma hoc ky: ");
    scanf("%s", semesterID);

    printf("***************************\n");

    for(Subject *subject = rootSubject; subject; subject = subject->next) {
        if(strcmp(subject->subjectID, subjectID) == 0 && strcmp(subject->semesterID, semesterID) == 0) {
            printf("%s\t%s\t%d\t%d\t%s\t%d\n", subject->subjectID, subject->subjectName, subject->mid_ratio, subject->last_ratio, subject->semesterID, subject->countStudent);
            printf("***************************\n");
            if(subject->student != NULL) {
                for(Student *student = subject->student; student; student = student->next) {
                    printf("%s\t%s\t%s\t%.1f\t%.1f\t%s\n", student->StudentID, student->firstName, student->lastName, student->mid_score, student->last_score, student->final_score);
                }
            }
        } 
    }

    printf("***************************\n");

    strcpy(fileName, subjectID);
    strcat(fileName, "_");
    strcat(fileName, semesterID);
    strcat(fileName, "_rp.txt");

    FILE *file = fopen(fileName, "w+");
    for(Subject *subject = rootSubject; subject; subject = subject->next) {
        if(strcmp(subject->subjectID, subjectID) == 0 && strcmp(subject->semesterID, semesterID) == 0) {
            for(Student *student = subject->student; student; student = student->next) {
                if(strcmp(student->final_score, "A") == 0) {
                    arrPoint[0]++;
                }else if(strcmp(student->final_score, "B") == 0) {
                    arrPoint[1]++;
                }else if(strcmp(student->final_score, "C") == 0) {
                    arrPoint[2]++;
                }else if(strcmp(student->final_score, "D") == 0) {
                    arrPoint[3]++;
                }else {
                    arrPoint[4]++;
                }
            }
        }
        else {
        printf("Subject ID or semesterID wrong \n");
        break;
        }
    }

    fprintf(file, "The student with the highest mark is: %s\t%s\n", maxScore(rootSubject, subjectID, semesterID) ? maxScore(rootSubject, subjectID, semesterID)->firstName : "NONE", maxScore(rootSubject, subjectID, semesterID) ? maxScore(rootSubject, subjectID, semesterID)->lastName : "NONE");
    fprintf(file, "The student with the lowest mark is: %s\t%s\n", minScore(rootSubject, subjectID, semesterID) ? minScore(rootSubject, subjectID, semesterID)->firstName : "NONE", minScore(rootSubject, subjectID, semesterID) ? minScore(rootSubject, subjectID, semesterID)->lastName : "NONE");
    fprintf(file, "The average mark is: %.1f\n", averageScore(rootSubject, subjectID, semesterID));

    fprintf(file, "A histogram of the subject %s is: \n", subjectID);
    for(int i = 0; i < 10; i++) {
        fprintf(file, "%c: ", anphaPoint[i]);
        if(arrPoint[i]!=0 )
        {
            for (int j=i;j<arrPoint[i];j++)
            {
                fprintf(file,"*");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
};