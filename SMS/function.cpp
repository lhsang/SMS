#include"function.h"
#include"SupportFunc.h"
#define DATABASE "StudentManagementSystem.db"


void showMenu()
{

}
void viewInfo()
{
	cout << "\n--------------------------View your information-----------------------------\n\n";
	cout << "Your information : \n";
	
	int rc;		char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}

	string sql = "select * from user where username = '" + userCurrent + "'";
	char *zErrMsg = 0;
	string data = "--------------------";
	rc = sqlite3_exec(db, sql.c_str(),output, (void*)data.c_str(), &zErrMsg);

	sqlite3_close(db);

	cout << "\n Press any key to return main Menu \n";
	system("pause");
	system("cls");
	mainMenu();
}
void changePassword()
{
	cout << "\n----------------------------Change password----------------------------------\n\n";
	string oldPass, newPass;
	cout << "Enter old password : "; cin >> oldPass;
	cout << "Enter new password : "; cin >> newPass;
	//change
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	string sql = "update user set password ='" + newPass + "' where username='"+userCurrent+"' and password ='"+oldPass+"'";
	char *zErrMsg = 0;
	string data = "----";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
	//-------------------------------------------------------------------------------------
	cout << "\n Press any key to return main Menu \n";
	system("pause");
	system("cls");
	mainMenu();
}
void logOut()
{
	userCurrent = "";
	userType = -1;
	mainMenu();
}
bool login()
{
	system("cls");
	string userName, pass;
	cout << "\n--------------------SIGN IN-----------------------\n";
	cout << "Enter username : "; cin >> userName;
	cout << "Enter password : "; cin >> pass;
	
	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return 1;
	}
	string sql = "select * from user where username = '" + userName + "' and  password = '" + pass + "'";
	char *zErrMsg = 0;
	string data = "----";
	rc = sqlite3_exec(db, sql.c_str(), getDB, (void*)data.c_str(), &zErrMsg);

	sqlite3_close(db);
	return userCurrent.size() != 0;
}


//Staff's function

//----------------Student-----------------------------------------------
//1
void importStudentsOfAClassFromCSV()
{
	cout << "\n-----------------------Import students of class from csv file---------------------------\n\n";
	system("cls");
	string fileName;
	cout << "------------------Your file csv must be formated in the following format :------------------\n";
	cout << "First line :            class | nameClass\nSecond line is title:      NO | STUDENT_ID  | FULL NAME  | EMAIL | PHONE | PASSWORD\n";
	cout << "Enter file name csv : "; cin >> fileName;
	if (fileName.size()<4||fileName.substr(fileName.size() - 3, 3).compare("csv") != 0)
		fileName += ".csv";

	string className, title;
	ifstream f(fileName);
	if(!f)
	{
		cout << "Not found this file\n"; f.close();
		mainMenu();
	}
	getline(f, className);
	className = subUntil(className, className.find(',') + 1, ',');

	getline(f, title);//no,id,name,email,phone,pass
	string sql = "";

	//connect DB
	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "----";
	
	//read file
	while (f.good())
	{
		string buff;
		getline(f, buff);
		if (buff == "")
			break;
		sql = splitData(buff, className);
		rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	}
	sqlite3_close(db);
	cout << "Imported !" << endl;
	f.close();
	mainMenu();
}

//2+6
void addANewStudentToClass()	//2
{
	cout << "\n----------------------------Add a new student to class----------------------------------\n\n";
	string sql;
	User sv;
	system("cls");
	cout << "Enter student's info : " << endl;
	cout << "Student ID : "; cin >> sv.userName;
	cin.ignore();
	cout << "Full name : "; getline(cin, sv.fullName);
	cout << "Email : "; cin >> sv.email;
	cout << "Phone : "; cin >> sv.phone;
	cin.ignore();
	cout << "Password : "; getline(cin, sv.password);
	cout << "Class : "; cin >> sv.className;
	sv.type = 0;

	sql = "insert into user values('" + sv.userName + "','" + sv.fullName + "','" + sv.email + "','" + sv.phone + "'," + to_string(sv.type) + ",'" + sv.password + "','" + sv.className + "')";

	int rc;		char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;
	string data = "--------------------";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);

	sqlite3_close(db);
	cout << "Addition is successful !";
	mainMenu();
} //2

//3
void editAStudent()
{
	cout << "\n----------------------------Edit a student----------------------------------\n\n";
	int select; string student;

	cout << "Which student do you want to edit ? (enter username ) : ";
	cin >> student;

	string sql = "update user set ";
	string t1= "where username='" + student + "'";

	system("cls");
	cout << "What is your infomation want to edit ?\n";
	cout << "1. UserName\n";
	cout << "2. Full name\n";
	cout << "3. Email\n";
	cout << "4. Phone\n";
	cout << "5. Password\n";
	cout << "6. Class\n";
	cout << "Your selection : ";
	cin >> select;
	system("cls");

	string newinfo;
	switch (select)
	{
	case 1: {
			
			cout << "New username : "; cin >> newinfo;
			sql = sql + "username = '" + newinfo + "' " + t1;
		} break;
	case 2: {
			cout << "New full name : "; getline(cin, newinfo);
			sql = sql + "fullname = '" + newinfo + "' " + t1;
	} break;
	case 3: {
			cout << "New email : "; cin >> newinfo;
			sql = sql + "email = '" + newinfo + "' " + t1;
	} break;
	case 4: {
			cout << "New phone number : "; cin >> newinfo;
			sql = sql + "phone = '" + newinfo + "' " + t1;
	} break;
	case 5: {
			cout << "New password : "; getline(cin,newinfo);
			sql = sql + "password = '" + newinfo + "' " + t1;
	}break;
	case 6: {
			cout << "New class : "; cin >> newinfo;
			sql = sql + "class = '" + newinfo + "' " + t1;
	}break;
	default: {
			cout << "Your select is incorrect !";
			return;
	} break;
	}
	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
   //---------------------------------------
	cout << "Info was changed !\n-------------------------------\n";
	mainMenu();
} //3

//4
void removeAStudent()
{
	cout << "\n----------------------------Remove a student----------------------------------\n\n";
	cout << "Enter studentID you want to remove : ";
	string id; cin >> id;
	string sql_user = "delete from user where username='" + id + "'";
	string sql_score = "delete from score where studentid='" + id + "'";
	string sql_presence = "delete from presence where studentid='" + id + "'";
	//------------------------------------------------------
	int rc;		char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;
	string data = "--------------------";
	rc = sqlite3_exec(db, sql_presence.c_str(), output, (void*)data.c_str(), &zErrMsg);
	rc = sqlite3_exec(db, sql_score.c_str(), output, (void*)data.c_str(), &zErrMsg);
	rc = sqlite3_exec(db, sql_user.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);

	//---------------------------------------
	cout << "Removed !\n-------------------------------\n";
	mainMenu();
}

//5
void moveClass()
{
	cout << "\n----------------------------Move class----------------------------------\n\n";
	int select; 
	string student, newClass;

	cout << "Which student do you want to move class ? (enter username ) : ";	cin >> student;
	cout << "Enter new class : ";	cin >> newClass;

	string sql = "update user set class='"+newClass+"' where username='" + student + "'";

	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
	//---------------------------------------
	cout << "Class was changed !\n-------------------------------\n";
	mainMenu();
}

//7
void viewListOfClasses()
{
	cout << "\n----------------------------View list of classes----------------------------------\n\n";
	string sql = "select class from user where class !='' and class is not null";
	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----------------";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);

	cout << "\n\n--------------------------------------------------------------------------\n\n\n";
	mainMenu();
}

//8
void viewListOfStudentOfAClass()
{
	cout << "\n---------------------------View list of student of a class----------------------------------\n\n";
	string className;
	cout << "Enter class name which you want to view : "; cin >> className;

	string sql = "select * from user where class='" + className + "'";
	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----------------";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
	//---------------------------------------
	

	cout << "\n\n--------------------------------------------------------------------------\n\n\n";
	mainMenu();
}

//----------------------------Course-------------------------------------
//1
void importCoursesFromCSV() {
	cout << "\n----------------------------Import courses from csv file----------------------------------\n\n";
	cout << formatDate("20/6/2018");
	system("cls");
	string fileName;
	cout << "------------------Your file csv must be formated in the following format :------------------\n";
	cout << "First line is title:     COURSE CODE | YEAR  | SMESTER  | COURSE NAME | LECTURER USERNAME | START DATE | END DATE | START TIME | END TIME | DATE OF WEEK\n";
	cout << "Enter file name csv : "; cin >> fileName;
	if (fileName.size()<4 || fileName.substr(fileName.size() - 3, 3).compare("csv") != 0)
		fileName += ".csv";

	string title;
	ifstream f(fileName);
	if (!f)
	{
		cout << "Not found this file\n"; f.close();
		mainMenu();
	}

	getline(f, title);//no,id,name,email,phone,pass
	string sql = "";

	//connect DB
	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "----";

	//read file
	while (f.good())
	{
		string buff;
		getline(f, buff);
		if (buff == "")
			break;
		sql = splitDataForCourse(buff);
		rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	}
	sqlite3_close(db);
	cout << "Imported !" << endl;
	f.close();
	mainMenu();
}

//2
void addANewCourse() {
	cout << "\n----------------------------Add a course----------------------------------\n\n";
	string sql;
	Course cour;
	system("cls");

	cout << "Course Code : "; cin >> cour.courseCode;
	cin.ignore();
	cout << "Course Name : "; getline(cin, cour.courseName);
	cout << "Year : "; getline(cin,cour.year);
	cout << "Semester : "; cin >> cour.semester;
	cout << "Lecturer's UserName : "; cin >> cour.lecturerUserName;
	cin.ignore();
	cout << "This course start at  (date): "; getline(cin, cour.startAt); cour.startAt = formatDate(cour.startAt);
	cout << "This course end at (date) : "; getline(cin, cour.endAt); cour.endAt = formatDate(cour.endAt);

	cout << "This course from (time): "; getline(cin, cour.from);
	cout << "This course to (time) : "; getline(cin, cour.to);
	cout << "Date of week : "; getline(cin, cour.dateOfWeek);

	sql = "insert into course values('" + cour.courseCode + "','" + cour.year + "'," + to_string(cour.semester) + 
		",'" + cour.courseName + "','" + cour.lecturerUserName + "','" + cour.startAt + "','" + cour.endAt + "','" + cour.from + "','" + cour.to + "','" + cour.dateOfWeek + "')";
	
	//----------------------------------------------------------------------
	int rc;		char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "--------------------";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		cout << "Addition is successful !\n";
	}
	sqlite3_close(db);
	mainMenu();
}
void editACourse()
{
	cout << "\n----------------------------Edit a course----------------------------------\n\n";
	int select; string coursecode;

	cout << "Which course do you want to edit ? (enter course code ) : ";
	cin >> coursecode;

	string sql = "update course set ";
	string t1 = " where coursecode='" +coursecode+ "'";

	system("cls");
	cout << "What is your infomation want to edit ?\n";
	cout << "1. Coursecode\n";
	cout << "2. Course name\n";
	cout << "3. Year\n";
	cout << "4. Semester\n";
	cout << "5. Start date :\n";
	cout << "6. End date : \n";
	cout << "7. Start time : \n";
	cout << "8. End time : \n";
	cout << "9. Date of week : \n";
	cout << "Your selection : ";
	cin >> select;
	system("cls");

	string newinfo;
	switch (select)
	{
	case 1: {

		cout << "New course code : "; cin >> newinfo;
		sql = sql + "coursecode = '" + newinfo + "' " + t1;
	} break;
	case 2: {
		cout << "New course name : "; getline(cin, newinfo);
		sql = sql + "coursename = '" + newinfo + "' " + t1;
	} break;
	case 3: {
		cout << "New year : "; cin >> newinfo;
		sql = sql + "year = '" + newinfo + "' " + t1;
	} break;
	case 4: {
		cout << "New semester : "; cin >> newinfo;
		sql = sql + "semester = " + newinfo + t1;
	} break;
	case 5: {
		cout << "New start date : "; cin >> newinfo;
		sql = sql + "start = '" + newinfo + "' " + t1;
	}break;
	case 6: {
		cout << "New end date : "; cin >> newinfo;
		sql = sql + "end = '" + newinfo + "' " + t1;
	}break;
	case 7: {
		cout << "New start time : "; cin >> newinfo;
		sql = sql + "startfrom = '" + newinfo + "' " + t1;
	}break;
	case 8: {
		cout << "New end time : "; cin >> newinfo;
		sql = sql + "startto = '" + newinfo + "' " + t1;
	}break;
	case 9: {
		cout << "New date of week : "; cin >> newinfo;
		sql = sql + "dateofweek = '" + newinfo + "' " + t1;
	}break;
	default: {
		cout << "Your select is incorrect !";
		return;
	} break;
	}
	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
	//---------------------------------------
	cout << "Info was changed !\n-------------------------------\n";
	mainMenu();
}
void removeACourse() {
	cout << "\n----------------------------Remove a course----------------------------------\n\n";
	cout << "Enter coursecode you want to remove : ";
	string id; cin >> id;
	string sql_user = "delete from course where coursecode ='" + id + "'";
	string sql_score = "delete from score where coursecode ='" + id + "'";
	string sql_presence = "delete from presence where coursecode ='" + id + "'";
	//------------------------------------------------------
	int rc;		char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;
	string data = "--------------------";
	rc = sqlite3_exec(db, sql_presence.c_str(), output, (void*)data.c_str(), &zErrMsg);
	rc = sqlite3_exec(db, sql_score.c_str(), output, (void*)data.c_str(), &zErrMsg);
	rc = sqlite3_exec(db, sql_user.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);

	//---------------------------------------
	cout << "Removed !\n-------------------------------\n";
	mainMenu();
}
void viewListOfCourse() {

	cout << "\n----------------------------View list of courses----------------------------------\n\n";
	string sql = "select * from course";
	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----------------";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);

	cout << "\n\n--------------------------------------------------------------------------\n\n\n";
	mainMenu();
}


//---------------------------------------student--------------------------
void checkIn()
{
	cout << "\n----------------------------Check in----------------------------------\n\n";
	string code, year;
	int semester, week;
	cout << "Welcome to attendence :\n";
	cout << "Enter your courseCode : "; getline(cin, code);
	cout << "Enter your school year(ex: 2017-2018) : "; getline(cin, year);
	cout << "Semester : "; cin >> semester;
	cout << "Week : "; cin >> week;

	//connect DB
	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "----",sql;

	sql = "insert into Presence values('" + code + "','" + year + "'," + to_string(semester) + ",'" + userCurrent + "'," + to_string(week) + ")";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
}
void viewCheckInResult()
{
	cout << "\n---------------------------View check in result----------------------------------\n\n";
	string code;
	cout << "Enter course code you want to view checkin : "; getline(cin, code);

	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "----", sql;

	sql = "select * from presence where studentid='" + userCurrent + "'";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
}
void viewScoreOfACourse()
{
	cout << "\n----------------------------View score of a course----------------------------------\n";
	string code;
	cout << "Enter course code you want to view scoreboard : "; getline(cin, code);

	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "----", sql;
	sql = "select * from score where studentid='"+userCurrent+"'";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);
}
void viewSchedules()
{
	cout << "\n----------------------------View schedules----------------------------------\n";
	cout << "processing";
}

//----------------------------------------Lecturer---------------------------
void importScoreboardOfACourse()
{
	cout << "\n----------------------------Import scoreboard of a course----------------------------------\n";
}
void editGradeOfAStudent()
{
	string code, id, temp; int semester; char selection; float newScore;
	cout << "\n----------------------------Edit grade----------------------------------\n";
	cin.ignore();
	cout << "Course code : "; getline(cin, code);
	cout << "Student ID : "; getline(cin, id);
	cout << "Semester : "; cin >> semester;
	LOOP1:cout << "-------Grade---------";
	cout << "\n1.Midterm score\n2.Labscore\n3.Finalscore\nYour selection: "; cin >> selection;
	
	string sql = "update score set ";
	string t ="  where coursecode = '" + code + "' and studentid = '" + id + "' and semester = " + to_string(semester);
	switch (selection)
	{
	case '1':temp = "midtermscore"; break;
	case '2': temp = "labscore"; break;
	case '3':temp = "finalscore"; break;
	default: goto LOOP1;
		break;
	}
	cout << "Set new " << temp << " = "; cin >> newScore;

	string t1 = temp + " = " + to_string(newScore);

	sql = sql + t1 + t;
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----";
	rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	cout << "Edited !\n";
	sqlite3_close(db);
}
void viewAScoreBoard()
{
	string code;
	cout << "\n----------------------------View a scoreboard----------------------------------\n";
	cin.ignore();
	cout << "Enter course code: "; getline(cin, code);

	string sql = "select * from score where coursecode = '"+code+"'";
	//-------------------------------------
	int rc;	char *error;
	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	if (rc)
	{
		cerr << L"Lỗi mở CSDL: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;
	}
	char *zErrMsg = 0;	string data = "----------------";
	rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	sqlite3_close(db);

	cout << "\n\n--------------------------------------------------------------------------\n\n\n";
	mainMenu();
}
