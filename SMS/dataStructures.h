#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"sqlite3.h"
//#include"SupportFunc.h"
#define DATABASE "StudentManagementSystem.db"

using namespace std;

struct User
{
	string userName;
	string fullName;
	string email;
	string phone;

	int type;
	/*0	– Student
	  1	– Academic	staff
	  2	– Lecturer	
	  */

	string password;
	string className;
};


struct Course
{
	string courseCode;
	string year;
	int semester;
	string courseName;
	string lecturerUserName;//giang vien
	
	string startAt, endAt;
	string from, to;
	string dateOfWeek;
};

struct Presence
{
	string courseCode;
	int year;
	int semester;
	string studentID;
	int week;
};

struct Score
{
	string courseCode;
	int year;
	int semester;
	string studentID;
	float midtermScore;
	float labScore;
	float finalScore;
};