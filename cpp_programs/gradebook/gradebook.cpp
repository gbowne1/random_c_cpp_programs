// File:   gradebook.cpp
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   22:50:08
// Brief:  This program is a gradebook program.
//         This program was meant for use in grades K through 12

#include "gradebook.h"
#include "dataframe.h"
#include <iostream>
#include <sstream>
#include <cstring>

void GradeBook::addTeachersFromCSV(const std::string &fileName) {
	DataFrame teacherData(fileName);

	for (int i = 0; i < teacherData.sizeCols(); i++) {
		Teacher teacher = { teacherData["name"][i] };
		const std::string teacherID = teacherData["teacher_id"][i];
		this->addTeacher(teacherID, teacher);
	}
}

void GradeBook::addTeacher(const std::string &teacherID, const Teacher &teacher) {
	this->teachers[teacherID] = teacher;
}

void GradeBook::removeTeacher(const std::string &teacherID) {
	this->teachers.erase(teacherID);
}

void GradeBook::addStudentsFromCSV(const std::string &fileName) {
	DataFrame studentData(fileName);

	for (int i = 0; i < studentData.sizeCols(); i++) {
		Student student = { 
			studentData["name"][i], 
			(unsigned short) std::stoi(studentData["grade_level"][i]),
			std::stof(studentData["gpa"][i])
		};
		const std::string studentID = studentData["student_id"][i];
		this->addStudent(studentID, student);
	}
}

void GradeBook::addStudent(const std::string &studentID, const Student &student) {
	this->students[studentID] = student;
}

void GradeBook::removeStudent(const std::string &studentID) {
	this->students.erase(studentID);
}

void GradeBook::addClassesFromCSV(const std::string &fileName) {
	DataFrame classData(fileName);

	for (int i = 0; i < classData.sizeCols(); i++) {
		Class clss = { 
			classData["name"][i], 
			(unsigned short) std::stoi(classData["grade_level"][i]),
			std::stoi(classData["teacher_id"][i])
		};
		const std::string classID = classData["class_id"][i];
		this->addClass(classID, clss);
	}
}

void GradeBook::addClass(const std::string &classID, const Class &clss) {
	this->classes[classID] = clss;
}

void GradeBook::removeClass(const std::string &classID) {
	this->classes.erase(classID);
}

void GradeBook::addAssignmentsFromCSV(const std::string &fileName) {
	DataFrame assignmentData(fileName);

	for (int i = 0; i < assignmentData.sizeCols(); i++) {
		struct tm t;
		if (strptime(assignmentData["due_date"][i].c_str(), "%Y-%m-%d", &t) == NULL) {
			std::cout << "Failed to read date: " << assignmentData["due_date"][i] << ". Format: YYYY-mm-dd" << std::endl;
		}

		std::time_t dueDate = std::mktime(&t);
			
		Assignment assignment = { 
			assignmentData["name"][i], 
			dueDate,
			std::stoi(assignmentData["class_id"][i])
		};
		const std::string assignmentID = assignmentData["assignment_id"][i];
		this->addAssignment(assignmentID, assignment);
	}
}

void GradeBook::addAssignment(const std::string &assignmentID, const Assignment &assignment) {
	this->assignments[assignmentID] = assignment;
}

void GradeBook::removeAssignment(const std::string &assignmentID) {
	this->assignments.erase(assignmentID);
}

void GradeBook::addGradesFromCSV(const std::string &fileName) {
	DataFrame gradeData(fileName);

	for (int i = 0; i < gradeData.sizeCols(); i++) {
		const std::string assignmentID = gradeData["assignment_id"][i];
		const std::string studentID = gradeData["student_id"][i];
		this->addGrade(assignmentID, studentID, std::stoi(gradeData["score"][i]));
	}
}

void GradeBook::addGrade(const std::string &assignmentID, const std::string &studentID, int score) {
	Grade grade = { score };
	this->grades[std::make_pair(assignmentID, studentID)] = grade;
}

void GradeBook::removeGrade(const std::string &assignmentID, const std::string &studentID) {
	this->grades.erase(std::make_pair(assignmentID, studentID));
}

float GradeBook::calculateAverage(const std::string &studentID) const {
	if (!this->students.count(studentID))
		return 0.0;

	Student student = this->students.at(studentID);
	float sum = 0.0;
	unsigned int assignmentCount = 0;
	
	for (auto it = this->assignments.begin(); it != this->assignments.end(); it++) {
		const std::string assignmentID = it->first;

		const std::pair<std::string, std::string> key = std::make_pair(assignmentID, studentID);
		// TODO: If there is no grade for that student + assignment, should we skip it or count it as a 0?
		if (!this->grades.count(key))
			continue;

		sum += this->grades.at(key).score;
		assignmentCount++;
	}

	return sum / ((float) assignmentCount);
}

float GradeBook::calculateClassAverage(const std::string &classID) const {
	// TODO: Need some data structure to link students and classes
	return 0.0;
}

void GradeBook::save(const std::string &filename) const {
	// TODO: There will be multiple file names. Pass each file name through parameters?
}

void GradeBook::load(const std::string &filename) {
	// TODO: Is this still necessary?
}

int main(int argc, char const *argv[])
{
	GradeBook gradebook;

	// Populate gradebook with CSV data
	gradebook.addTeachersFromCSV("teacherdata.csv");
	gradebook.addStudentsFromCSV("studentdata.csv");
	gradebook.addClassesFromCSV("classdata.csv");
	gradebook.addAssignmentsFromCSV("assignmentdata.csv");
	gradebook.addGradesFromCSV("grades.csv");

	int id;
	std::cout << "Insert student ID for average score calculation: ";
	std::cin >> id;
	std::cout << 
		"Average score for student ID " <<
		id <<
		": " <<
		gradebook.calculateAverage(std::to_string(id)) << 
		std::endl;

	return 0;
}