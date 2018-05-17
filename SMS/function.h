#pragma once
#include"Menu.h"

extern int userType;
extern string userCurrent;

bool login();
void showMenu();
void viewInfo();
void changePassword();
void logOut();

//Staff's function
void importStudentsOfAClassFromCSV();
void addANewStudentToClass();
void editAStudent();
void removeAStudent();
void moveClass();
void viewListOfStudentOfAClass();
void viewListOfClasses();

void importCoursesFromCSV();
void addANewCourse();
void editACourse();
void removeACourse();
void viewListOfCourse();

void viewAttendanceListOfACourse();
void exportAttendanceListToCSV();
void viewScoreBoardOfACourse();
void  exportScoreBoardToCSV();

//Student function
void checkIn();
void viewCheckInResult();
void viewScoreOfACourse();
void viewSchedules();

// Lecturer function
void importScoreboardOfACourse();
void editGradeOfAStudent();
void viewAScoreBoard();