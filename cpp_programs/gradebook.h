// File:   gradebook.h
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   23:39:08
// Brief:  This is the header file for gradebook.cpp This program is a gradebook program.
//         This program is meant for grades K through 12 in the United States of America.

#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#define MAX_NAME_LENGTH 50
#define MAX_GRADES 10
#define MAX_STUDENTS 100

class GradeBook {
private:
    std::vector<Student> students;
public:
    void addStudent(const Student &student);
    void removeStudent(const std::string &studentID);
    void addGrade(Student &student, const Grade &grade);
    void removeGrade(Student &student, size_t index);
    float calculateAverage(const Student &student);
    float calculateClassAverage() const;
    void save(const std::string &filename) const;
    void load(const std::string &filename);
};

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} Grade;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Grade grades[MAX_GRADES];
    int numGrades;
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    int numStudents;
} GradeBook;

#endif