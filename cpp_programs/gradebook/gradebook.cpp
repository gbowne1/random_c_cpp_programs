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
#include <fstream>
#include <cstring>
#include <iomanip>

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
		memset(&t, 0, sizeof(struct tm));
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

DataFrame GradeBook::studentsToDataFrame() const {
	DataFrame studentDF;
	std::vector<std::string> header = { "student_id", "name", "grade_level", "gpa" };
	studentDF.initialize(header);

	for (auto it = this->students.begin(); it != this->students.end(); it++) {
		std::map<std::string, std::string> studentMap;
		Student student = it->second;

		std::stringstream gpaFormat;
		gpaFormat << std::fixed << std::setprecision(1) << student.gpa;

		studentMap["student_id"] = it->first;
		studentMap["name"] = student.name;
		studentMap["grade_level"] = std::to_string(student.gradeLevel);
		studentMap["gpa"] = gpaFormat.str();
		studentDF.append(studentMap);
	}

	return studentDF;
}

DataFrame GradeBook::teachersToDataFrame() const {
	DataFrame teacherDF;
	std::vector<std::string> header = { "teacher_id", "name" };
	teacherDF.initialize(header);

	for (auto it = this->teachers.begin(); it != this->teachers.end(); it++) {
		std::map<std::string, std::string> teacherMap;
		Teacher teacher = it->second;

		teacherMap["teacher_id"] = it->first;
		teacherMap["name"] = teacher.name;
		teacherDF.append(teacherMap);
	}

	return teacherDF;
}

DataFrame GradeBook::classesToDataFrame() const{
	DataFrame classDF;
	std::vector<std::string> header = { "class_id", "name", "grade_level", "teacher_id" };
	classDF.initialize(header);

	for (auto it = this->classes.begin(); it != this->classes.end(); it++) {
		std::map<std::string, std::string> classMap;
		Class clss = it->second;

		classMap["class_id"] = it->first;
		classMap["name"] = clss.name;
		classMap["grade_level"] = std::to_string(clss.gradeLevel);
		classMap["teacher_id"] = std::to_string(clss.teacherId);
		classDF.append(classMap);
	}

	return classDF;
}

DataFrame GradeBook::assignmentsToDataFrame() const {
	DataFrame assignmentDF;
	std::vector<std::string> header = { "assignment_id", "name", "due_date", "class_id" };
	assignmentDF.initialize(header);

	for (auto it = this->assignments.begin(); it != this->assignments.end(); it++) {
		std::map<std::string, std::string> assignmentMap;
		Assignment assignment = it->second;

		char dueDateChr[11];
		std::strftime(dueDateChr, sizeof(dueDateChr), "%Y-%m-%d", std::localtime(&assignment.dueDate));
		std::string dueDateStr = dueDateChr;

		assignmentMap["assignment_id"] = it->first;
		assignmentMap["name"] = assignment.name;
		assignmentMap["due_date"] = dueDateStr;
		assignmentMap["class_id"] = std::to_string(assignment.classId);
		assignmentDF.append(assignmentMap);
	}

	return assignmentDF;
}

DataFrame GradeBook::gradesToDataFrame() const {
	DataFrame gradeDF;
	std::vector<std::string> header = { "assignment_id", "student_id", "score" };
	gradeDF.initialize(header);

	for (auto it = this->grades.begin(); it != this->grades.end(); it++) {
		std::map<std::string, std::string> gradeMap;
		Grade grade = it->second;

		gradeMap["assignment_id"] = it->first.first;
		gradeMap["student_id"] = it->first.second;
		gradeMap["score"] = std::to_string(grade.score);
		gradeDF.append(gradeMap);
	}

	return gradeDF;
}

bool GradeBook::checkFileExists(const std::string &fileName) const {
	std::ifstream file(fileName);
	return file.good();
}

void GradeBook::saveGrades(const std::string &fileName) const {
	this->gradesToDataFrame().save(fileName);
}

void GradeBook::loadGrades(const std::string &fileName) {
	if (!this->checkFileExists(fileName)) {
		std::cout << "File " << fileName << " does not exist!" << std::endl;
		return;
	}

	// TODO: Checks to validate the CSV file data, telling whether the load was successful or not
	this->addGradesFromCSV(fileName);
	std::cout << "Grades have been loaded successfully!" << std::endl;
}

void GradeBook::saveStudents(const std::string &fileName) const {
	this->studentsToDataFrame().save(fileName);
}

void GradeBook::loadStudents(const std::string &fileName) {
	if (!this->checkFileExists(fileName)) {
		std::cout << "File " << fileName << " does not exist!" << std::endl;
		return;
	}

	// TODO: Checks to validate the CSV file data, telling whether the load was successful or not
	this->addStudentsFromCSV(fileName);
	std::cout << "Students have been loaded successfully!" << std::endl;
}

int main(int argc, char const *argv[])
{
	GradeBook gradebook;

	int choice;
    while (true)
    {
        std::cout << "1. Load Grades\n";
        std::cout << "2. Save Grades\n";
        std::cout << "3. Show Grades\n";
        std::cout << "4. Add Student\n";
        std::cout << "5. Remove Student\n";
        std::cout << "6. Load Students\n";
        std::cout << "7. Save Students\n";
        std::cout << "8. Show Students\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

		// TODO: Probably put each of these cases into functions for better readability
        switch (choice)
        {
            case 1: {
				std::string fileName;
				std::cout << "Please type the name of the CSV file to load the grades from: ";
				std::getline(std::cin >> std::ws, fileName);
                gradebook.loadGrades(fileName);
                break;
			}
            case 2: {
				std::string fileName;
				std::cout << "Please type the name of the CSV file to save the grades to: ";
				std::getline(std::cin >> std::ws, fileName);
                gradebook.saveGrades(fileName);
                break;
			}
            case 3: {
				gradebook.gradesToDataFrame().print();
				std::cout << "Press ENTER to continue...";
				std::cin.ignore();
				std::getchar();
                break;
			}
            case 4: {
				std::string studentID, studentName;
				unsigned short gradeLevel;
				float gpa;

				std::cout << "Student ID: ";
				std::cin >> studentID;

				std::cout << "Student Name: ";
				std::cin >> studentName;

				std::cout << "Grade Level: ";
				std::cin >> gradeLevel;

				std::cout << "GPA: ";
				std::cin >> gpa;

				Student student = { studentName, gradeLevel, gpa };
                gradebook.addStudent(studentID, student);
                break;
			}
            case 5: {
				std::string studentID;
				std::cout << "Please type the student ID to be removed: ";
				std::cin >> studentID;
                gradebook.removeStudent(studentID);
                break;
			}
			case 6: {
				std::string fileName;
				std::cout << "Please type the name of the CSV file to load the students from: ";
				std::getline(std::cin >> std::ws, fileName);
                gradebook.loadStudents(fileName);
				break;
			}
			case 7: {
				std::string fileName;
				std::cout << "Please type the name of the CSV file to save the students to: ";
				std::getline(std::cin >> std::ws, fileName);
                gradebook.saveStudents(fileName);
				break;
			}
			case 8: {
				gradebook.studentsToDataFrame().print();
				std::cout << "Press ENTER to continue...";
				std::cin.ignore();
				std::getchar();
				break;
			}
            case 9:
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

	return 0;
}