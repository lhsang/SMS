#include"function.h"
#include"SupportFunc.h"
#define DATABASE "QLDT.db"

using namespace std;
void queryDB(std::string sql, int t)
{
	int rc;
	char *error;	sqlite3 *db;
	rc = sqlite3_open(DATABASE, &db);
	char *zErrMsg = 0;
	string data = "----";
	if (t == 1)		// ouput
	{
		rc = sqlite3_exec(db, sql.c_str(), output, (void*)data.c_str(), &zErrMsg);
	}
	else if(t==-1)		//get data to login
		rc = sqlite3_exec(db, sql.c_str(), getDB, (void*)data.c_str(), &zErrMsg);
	else if(t==2)			//export to csv
		rc = sqlite3_exec(db, sql.c_str(),exporting, (void*)data.c_str(), &zErrMsg);
	else     // edit database (not output)
		rc = sqlite3_exec(db, sql.c_str(),editDB, (void*)data.c_str(), &zErrMsg);
}
void viewInfo()
{
	cout << "\n--------------------------View your information-----------------------------\n\n";
	cout << "Your information : \n";
	string sql = "select * from user where username = '" + userCurrent + "'";
	queryDB(sql, 1);
}
void changePassword()
{
	cout << "\n----------------------------Change password----------------------------------\n\n";
	string oldPass, newPass;
	cout << "Enter old password : "; cin >> oldPass;
	cout << "Enter new password : "; cin >> newPass;
	string sql = "update user set password ='" + newPass + "' where username='" + userCurrent + "' and password ='" + oldPass + "'";
	queryDB(sql, 0);
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
	cout << "Enter password : ";
	char key = _getch();
	while (key!=13)
	{
		pass.push_back(key); cout << "*"; key = _getch();
	}
	string sql = "select * from user where username = '" + userName + "' and  password = '" + pass + "'";
	queryDB(sql, -1);
	return userCurrent.size() != 0;
}


//Staff's function

//----Student-------
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
}

//2
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

	queryDB(sql, 0);
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
	cin.ignore();
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
	queryDB(sql, 0);
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

	queryDB(sql, 0);
}

//6
void addANewEmptyClass()
{
	cout << "\n----------------------------Add a new empty class----------------------------------\n\n";
	string sql;
	string className, id, startyear, endyear;
	cin.ignore();
	cout << "Enter class name : "; getline(cin, className);
	cout << "Class ID : "; getline(cin, id);
	cout << "Start year : "; getline(cin, startyear);
	cout << "End year : "; getline(cin, endyear);

	sql = "insert into class values('" + id + "','" + className + "'," + startyear + "," + endyear + ")";
	queryDB(sql, 0);
}

//7
void viewListOfClasses()
{
	cout << "\n----------------------------View list of classes----------------------------------\n\n";
	string sql = "select * from class";
	queryDB(sql, 1);
}

//8
void viewListOfStudentOfAClass()
{
	cout << "\n---------------------------View list of student of a class----------------------------------\n\n";
	string className;
	cout << "Enter class ID which you want to view (Ex:17CNTN): "; cin >> className;

	string sql = "select * from user where class='" + className + "'";
	queryDB(sql, 1);
}

//------Course-------
//1
void importCoursesFromCSV() {
	system("cls");
	cout << "\n----------------------------Import courses from csv file----------------------------------\n\n";
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

	cout << "This course from section(1-10): "; getline(cin, cour.from);
	cout << "This course to section(1-10) : "; getline(cin, cour.to);
	cout << "Date of week : "; getline(cin, cour.dateOfWeek);

	sql = "insert into course values('" + cour.courseCode + "','" + cour.year + "'," + to_string(cour.semester) + 
		",'" + cour.courseName + "','" + cour.lecturerUserName + "','" + cour.startAt + "','" + cour.endAt + "'," + cour.from + "," + cour.to + ",'" + cour.dateOfWeek + "')";
	
	queryDB(sql, 0);
}
//3
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
	cout << "7. Start section : \n";
	cout << "8. End section : \n";
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
		cout << "New start section : "; cin >> newinfo;
		sql = sql + "startsection = " + newinfo +  t1;
	}break;
	case 8: {
		cout << "New end section : "; cin >> newinfo;
		sql = sql + "endsection = " + newinfo +  t1;
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
	queryDB(sql, 0);
}
//4
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
//5
void viewListOfCourse() {

	cout << "\n----------------------------View list of courses----------------------------------\n\n";
	string year, semester;
	cin.ignore();
	cout << "Year (ex:2017-2018) : "; getline(cin, year);
	cout << "Semester (ex: 1) : "; getline(cin, semester);
	string sql = "select * from course where year='"+year+"' and semester ="+semester;
	queryDB(sql, 1);
}

//----schedule-----
//1
void importCourseScheduleFromCSV()
{
	system("cls");
	cout << "\n-----------------------Import course's schedule from csv file---------------------------\n\n";

	string fileName;
	cout << "------------------Your file csv must be formated in the following format :------------------\n";
	cout << "First line :             First line is title:      NO | COURSE'S CODE  | START SECTION  | END SECTION | DATE OF WEEK\n";
	cout << "Enter file name csv : "; cin >> fileName;
	if (fileName.size()<4 || fileName.substr(fileName.size() - 3, 3).compare("csv") != 0)
		fileName += ".csv";

	string title;
	ifstream f(fileName);
	if (!f)
	{
		cout << "Not found this file\n"; f.close();
		return;
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
		sql = splitDataForSchedule(buff);
		rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	}
	sqlite3_close(db);
	cout << "Imported !" << endl;
	f.close();
}
//2
void addACourseSchedule()
{
	system("cls");
	string sql, start, end, dateofweek,code;
	cout << "\n-----------------------Import course's schedule from csv file---------------------------\n\n";
	cin.ignore();
	cout << "Enter course'code : "; getline(cin, code);
	cout << "Start section : "; getline(cin, start);
	cout << "End section : "; getline(cin, end);
	cout << "Date of week : "; getline(cin, dateofweek);
	sql = "update course set startsection=" + start + " , endsection=" + end + " , dateofweek='" + dateofweek + "' where coursecode='" + code + "'";
	queryDB(sql, 0);
}
//3
void editASchedule()
{
	std::cout << "\n----------------------------Edit a course's shedule ----------------------------------\n\n";
	int select; string coursecode;

	cout << "Enter course's code  : ";
	cin >> coursecode;

	string sql = "update course set ";
	string t1 = " where coursecode='" + coursecode + "'";

	system("cls");
	cout << "What is your infomation want to edit ?\n";
	cout << "1. Start section : \n";
	cout << "2. End section : \n";
	cout << "3. Date of week : \n";
	cout << "Your selection : ";
	cin >> select;
	system("cls");
	string newinfo;
	switch (select)
	{
	case 1: {

		cout << "New start section(1,2,3) : "; cin >> newinfo;
		sql = sql + "startsection = " + newinfo + " " + t1;
	} break;
	case 2: {
		cout << "New end section : "; getline(cin, newinfo);
		sql = sql + "endsection = " + newinfo + " " + t1;
	} break;
	case 3: {
		cout << "Date of week (MON,TUE,WED,...): "; cin >> newinfo;
		sql = sql + "dateofweek = '" + newinfo + "' " + t1;
	} break;
	default: {
		cout << "Your select is incorrect !";
		return;
	} break;
	}
	queryDB(sql, 0);

}
//4
void removeSchedule()
{
	std::cout << "\n----------------------------Remove a course's shedule ----------------------------------\n\n";
	int select; string coursecode;
	cout << "If you remove schedule of a course , Schedule will be set default values\n";
	cout << "Enter course's code  : ";
	cin >> coursecode;
	string sql = "update course set startsection= 1,endsection=1,dateofweek='SUN' where coursecode='" + coursecode + "'";
	queryDB(sql, 0);
}
//5
void viewListSchedule()
{
	cout << "\n----------------------------View list schedules----------------------------------\n";
	string sql,year, semester;
	cin.ignore();
	cout << "Enter school year (ex: 2017-2018) : "; getline(cin, year);
	cout << "Enter semester (1,2,3): "; getline(cin, semester);
	sql = "select coursename,startsection,endsection,dateofweek from course where  year='" + year + "' and semester =" + semester;
	queryDB(sql, 1);
}

//---attendence----
//1
void viewAttendanceListOfACourse() {
	string code;
	cout << "\n--------------Search and view attendance list of a course---------------------------\n";
	cout << "Enter course code : "; cin >> code;
	string sql="select * from presence where coursecode='" + code + "'";
	queryDB(sql, 1);
}
//2
void exportAttendanceListToCSV() {
	string code, year, semester, sql, filename, title;
	cout << "\n--------------Export attendance to CSV file---------------------------\n";
	cin.ignore();
	cout << "Enter course's code which you want to export attendance : "; getline(cin, code);
	cout << "year (ex: 2017-2018) :"; getline(cin, year);
	cout << "Semester "; cin >> semester;
	filename = "attendance_" + code + ".csv";
	sql = "select * from presence  where coursecode='" + code + "' and year ='" + year + "' and semester=" + semester;

	title = "Course,Year,Semester,Student ID,Week\n";
	ex.open(filename);
	ex.clear();
	ex << title;
	queryDB(sql, 2);
	ex.close();
	cout << endl << "Exported !\n";
}

//-----score-----
//1
void viewScoreBoardOfACourse() {
	string code;
	cout << "\n--------------Search and view score board of a course---------------------------\n";
	cout << "Enter course code : "; cin >> code;
	string sql = "select * from score where coursecode='" + code + "'";
	queryDB(sql, 1);
}
//2
void  exportScoreBoardToCSV() {
	string code,year,semester, sql,filename,title;
	cout << "\n--------------Export score board to CSV file---------------------------\n";
	cin.ignore();
	cout << "Enter course's code which you want to export score board : "; getline(cin, code);
	cout << "year (ex: 2017-2018) :"; getline(cin, year);
	cout << "Semester "; cin >> semester;
	filename = "scoreboard_" + code + ".csv";
	sql = "select * from score  where coursecode='" + code + "' and year ='" + year + "' and semester=" + semester;

	title = "Course,Year,Semester,Student ID,Midterm Score,Lab score,Final Score,Bonus\n";
	ex.open(filename);
	ex.clear();	
	ex << title;
	queryDB(sql, 2);
	ex.close();
}


//--------------------//Student's function----------------------
//1
void checkIn()
{
	cout << "\n----------------------------Check in----------------------------------\n\n";
	string code, year;
	int semester, week;
	cout << "Enter your courseCode : "; getline(cin, code);
	cout << "Enter your school year(ex: 2017-2018) : "; getline(cin, year);
	cout << "Semester : "; cin >> semester;
	cout << "Week : "; cin >> week;
	string sql= "insert into Presence values('" + code + "','" + year + "'," + to_string(semester) + ",'" + userCurrent + "'," + to_string(week) + ")";
	queryDB(sql, 0);
}
//2
void viewCheckInResult()
{
	cout << "\n---------------------------View check in result----------------------------------\n\n";
	string code,sql;
	cout << "Enter course's code you want to view checkin : "; getline(cin, code);
	sql = "select * from presence where studentid='" + userCurrent + "' and coursecode = '"+code+"'";
	queryDB(sql, 1);
}
//3
void viewScoreOfACourse()
{
	cout << "\n----------------------------View score of a course----------------------------------\n";
	string code,sql;
	cout << "Enter course code you want to view scoreboard : "; getline(cin, code);
	sql = "select * from score where studentid='"+userCurrent+"'";
	queryDB(sql, 1);
}
//4
void viewSchedules()
{
	cout << "\n----------------------------View schedules----------------------------------\n";
	string sql;
	string year,semester;
	cout << "Enter school year (ex: 2017-2018) : "; getline(cin, year);
	cout << "Enter semester (1,2,3): "; getline(cin, semester);
	sql = "select coursename,lecturerusername,start,end,startsection,endsection,dateofweek from course where coursecode in (select coursecode from presence where studentid='" + userCurrent + "') and year='" + year + "' and semester =" + semester;
	queryDB(sql, 1);
}



//------------------Lecturer's function-----------------------
//1
void importScoreboardOfACourse()
{
	system("cls");
	cout << "\n----------------------------Import scoreboard of a course----------------------------------\n";
	string fileName;
	cout << "------------------Your file csv must be formated in the following format :------------------\n";
	cout << "First line is title:     COURSE CODE | YEAR  | SMESTER  | STUDENT ID | MIDTERM SCORE | FINAL SOCRE | LAB SCORE | BONUS \n";
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

	getline(f, title);
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
		sql = splitDataForScore(buff);
		rc = sqlite3_exec(db, sql.c_str(), editDB, (void*)data.c_str(), &zErrMsg);
	}
	sqlite3_close(db);
	cout << "Imported !" << endl;
	f.close();
}
//2
void editGradeOfAStudent()
{
	string code, id, temp; int semester; char selection; float newScore;
	cout << "\n----------------------------Edit grade----------------------------------\n";
	cin.ignore();
	cout << "Course code : "; getline(cin, code);
	cout << "Student ID : "; getline(cin, id);
	cout << "Semester : "; cin >> semester;
	LOOP1:cout << "-------Grade---------";
	cout << "\n1.Midterm score\n2.Labscore\n3.Finalscore\n4.Bonus\nYour selection: "; cin >> selection;
	
	string sql = "update score set ";
	string t ="  where coursecode = '" + code + "' and studentid = '" + id + "' and semester = " + to_string(semester);
	switch (selection)
	{
	case '1':temp = "midtermscore"; break;
	case '2': temp = "labscore"; break;
	case '3':temp = "finalscore"; break;
	case '4':temp = "bonus"; break;
	default: goto LOOP1;
		break;
	}
	cout << "Set new " << temp << " = "; cin >> newScore;

	string t1 = temp + " = " + to_string(newScore);

	sql = sql + t1 + t;
	queryDB(sql, 0);
}
//3
void viewAScoreBoard()
{
	string code;
	cout << "\n----------------------------View a scoreboard----------------------------------\n";
	cin.ignore();
	cout << "Enter course code: "; getline(cin, code);
	string sql = "select * from score where coursecode = '"+code+"'";
	queryDB(sql, 1);
}
