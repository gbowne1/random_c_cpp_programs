// File:   gradebook.cpp
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   22:50:08
// Brief:  This program is a gradebook program.
//         This program was meant for use in grades K through 12

#include "gradebook.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

#define MAX_NAME_LENGTH 50
#define MAX_GRADES 12

typedef struct
{
	char name[MAX_NAME_LENGTH];
	int score;
} Grade;

typedef struct
{
	char name[MAX_NAME_LENGTH];
	Grade grades[MAX_GRADES];
	int numGrades;
} Student;

typedef struct
{
	Student students[MAX_GRADES];
	int numStudents;
} GradeBook;

void GradeBook::addStudent(const Student &student)
{
	students.push_back(student);
}

void GradeBook::removeStudent(const std::string &studentID) {
    // Find the student in the vector and erase it
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->name == studentID) {
            students.erase(it);
            break;
        }
    }
}

void GradeBook::addGrade(Student &student, const Grade &grade)
{
	student.grades.push_back(grade);
}

void GradeBook::removeGrade(Student &student, size_t index) {
    // Check if the index is valid
    if (index >= 0 && index < student.grades.size()) {
        student.grades.erase(student.grades.begin() + index);
    }
}

float GradeBook::calculateAverage(const Student &student) {
    // Calculate the sum of the grades
    int sum = 0;
    for (const auto &grade : student.grades) {
        sum += grade.score;
    }

    // Return the average
    return static_cast<float>(sum) / student.grades.size();
}

float GradeBook::calculateClassAverage() const
{
    int totalScore = 0;
    int totalStudents = 0;

    for (const auto& student : students)
    {
        totalScore += calculateAverage(student);
        totalStudents++;
    }

    return static_cast<float>(totalScore) / totalStudents;
}

void GradeBook::save(const std::string &filename) {
    // Assuming you have a vector of students called 'students' in your GradeBook class
    std::ofstream file(filename);  // Open the file for writing

    if (file.is_open()) {
        file << "Name,Grades\n";  // Write the header

        for (const auto& student : students) {
            file << student.name << ",";

            for (size_t i = 0; i < student.grades.size(); i++) {
                file << student.grades[i];
                if (i < student.grades.size() - 1) {
                    file << ",";
                }
            }

            file << "\n";
        }

        file.close();  // Close the file
    } else {
        std::cerr << "Error: could not open file " << filename << std::endl;
    }
}

void GradeBook::load(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header line

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string name;
        std::getline(iss, name, ',');

        Student student;
        std::strncpy(student.name, name.c_str(), MAX_NAME_LENGTH);

        Grade grade;
        while (std::getline(iss, line, ','))
        {
            grade.score = std::stoi(line);
            student.grades[student.numGrades++] = grade;
        }

        students.push_back(student);
    }

    file.close();
}

int main()
{
	GradeBook gradebook;
	gradebook.numStudents = 0;

	Student student1;
	std::strcpy(student1.name, "John Doe");
	student1.numGrades = 3;
	student1.grades[0].score = 90;
	student1.grades[1].score = 85;
	student1.grades[2].score = 95;

	gradebook.students[0] = student1;
	gradebook.numStudents++;

	// Your code here
	return 0;
}