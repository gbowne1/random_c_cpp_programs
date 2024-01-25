// File:   gradebook.h
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   23:39:08
// Brief:  This is the header file for gradebook.cpp This program is a gradebook program.
//         This program is meant for grades K through 12 in the United States of America.

#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <map>
#include <string>
#include <time.h>
#include <chrono>
#include "dataframe.h"

typedef struct {
    std::string name;
    unsigned short int gradeLevel;
    float gpa;
} Student;

typedef struct {
    std::string name;
} Teacher;

typedef struct {
    std::string name;
    unsigned short int gradeLevel;
    int teacherId;
} Class;

typedef struct {
    std::string name;
    std::time_t dueDate;
    int classId;
} Assignment;

typedef struct {
    int score;
} Grade;

class GradeBook {
private:
    std::map<std::string, Student> students;
    std::map<std::string, Teacher> teachers;
    std::map<std::string, Class> classes;
    std::map<std::string, Assignment> assignments;
    std::map<
        std::pair<std::string, std::string>, Grade> grades;

    bool checkFileExists(const std::string& fileName) const;
public:
    void addTeachersFromCSV(const std::string &fileName);
    void addTeacher(const std::string &teacherID, const Teacher &teacher);
    void removeTeacher(const std::string &teacherID);

    void addStudentsFromCSV(const std::string &fileName);
    void addStudent(const std::string &studentID, const Student &student);
    void removeStudent(const std::string &studentID);

    void addClassesFromCSV(const std::string &fileName);
    void addClass(const std::string &classID, const Class &clss);
    void removeClass(const std::string &classID);

    void addAssignmentsFromCSV(const std::string &fileName);
    void addAssignment(const std::string &assignmentID, const Assignment &assignment);
    void removeAssignment(const std::string &assignmentID);

    void addGradesFromCSV(const std::string &fileName);
    void addGrade(const std::string &assignmentID, const std::string &studentID, int score);
    void removeGrade(const std::string &assignmentID, const std::string &studentID);

    float calculateAverage(const std::string &studentID) const;
    float calculateClassAverage(const std::string &classID) const;

    DataFrame studentsToDataFrame() const;
    DataFrame teachersToDataFrame() const;
    DataFrame classesToDataFrame() const;
    DataFrame assignmentsToDataFrame() const;
    DataFrame gradesToDataFrame() const;

    void saveGrades(const std::string &fileName) const;
    void loadGrades(const std::string &fileName);

    void saveStudents(const std::string &fileName) const;
    void loadStudents(const std::string &fileName);
};

#endif