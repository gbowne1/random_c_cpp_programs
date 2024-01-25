cmake_minimum_required(VERSION 3.0)

project(gradebook)

# Copy CSV files
configure_file(assignmentdata.csv assignmentdata.csv COPYONLY)
configure_file(classdata.csv classdata.csv COPYONLY)
configure_file(grades.csv grades.csv COPYONLY)
configure_file(studentdata.csv studentdata.csv COPYONLY)
configure_file(teacherdata.csv teacherdata.csv COPYONLY)


add_executable(${PROJECT_NAME} gradebook.cpp dataframe.cpp)