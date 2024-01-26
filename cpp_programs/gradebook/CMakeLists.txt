cmake_minimum_required(VERSION 3.0)

project(gradebook)

# Copy CSV files
configure_file(assets/assignmentdata.csv assets/assignmentdata.csv COPYONLY)
configure_file(assets/classdata.csv assets/classdata.csv COPYONLY)
configure_file(assets/grades.csv assets/grades.csv COPYONLY)
configure_file(assets/studentdata.csv assets/studentdata.csv COPYONLY)
configure_file(assets/teacherdata.csv assets/teacherdata.csv COPYONLY)


add_executable(${PROJECT_NAME} gradebook.cpp dataframe.cpp permissions.cpp)