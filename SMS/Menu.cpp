#include"Menu.h"
void studentMenu()
{
	LL:system("cls");
	char selection;

	cout << "1.Check in\n";
	cout << "2.View check in result\n";
	cout << "3.View your score of a course\n";
	cout << "4.View schedules\n";
	cout << "Your selection : "; cin >> selection;
	cin.ignore();
	switch (selection)
	{
	case '1': checkIn(); break;
	case '2': viewCheckInResult(); break;
	case '3': viewScoreOfACourse(); break;
	case '4': viewSchedules(); break;
	default: goto LL; break;
	}
	cout << endl << endl;
	cout << "---------------------------------\n";
	mainMenu();
}
void showMenuStaff(int n)
{
	system("cls");
	if (n == '1')			//student and class
	{
		L2:cout << "1. Import students of a class from a csv file\n";
		cout << "2. Add a new student to a class\n";
		cout << "3. Edit an existing student\n";
		cout << "4. Remove a student\n";
		cout << "5. Change students from class A to class B\n";
		cout << "6. Add a new empty class\n";
		cout << "7. View list of classes\n";
		cout << "8. View list of students in a class\n";
		char select;
		cout << "Your selection : ";
		cin >> select;
		switch (select)
		{
		case '1': importStudentsOfAClassFromCSV(); break;
		case '2': addANewStudentToClass(); break;
		case '3': editAStudent(); break;
		case '4': removeAStudent(); break;
		case '5': moveClass(); break;
		case '6': addANewEmptyClass(); break;
		case '7': viewListOfClasses(); break;
		case '8': viewListOfStudentOfAClass(); break;
		default: {system("cls"); goto L2;  }
		}
	}
	else if (n == '2')			//course
	{
		L3:cout << "1. Import courses from	a csv file\n";
		cout << "2.  Add a new course\n";
		cout << "3. Edit an existing course\n";
		cout << "4. Remove a course\n";
		cout << "5. View list of courses\n";
		char select;
		cout << "Your selection : ";
		cin >> select;
		switch (select)
		{
		case '1': importCoursesFromCSV(); break;
		case '2': addANewCourse(); break;
		case '3': editACourse(); break;
		case '4': removeACourse(); break;
		case '5': viewListOfCourse(); break;
		default: {system("cls"); goto L3;  }
		}
	}
	else if (n == '3')		//schedules
	{
		cout << "1. Import courses's schuedules from a csv file\n";
		cout << "2. Add a course's schedules\n";
		cout << "3. Edit a course's schedules\n";
		cout << "4. Remove a course's schedules\n";
		cout << "5. View list of schedules \n";
		char select;
		cout << "Your selection : ";
		cin >> select;
		switch (select)
		{
		case '1': importCourseScheduleFromCSV(); break;
		case '2': addACourseSchedule(); break;
		case '3': editASchedule(); break;
		case '4': removeSchedule(); break;
		case '5': viewListSchedule(); break;
		default: {system("cls"); goto L3;  }
		}
	}
	else if (n == '4') {		//   attendence
		L5:cout << "1. Search and view attendence list of a course\n";
		cout << "2. Export attendence list to a csv file \n";
		char select;
		cout << "Your selection : ";
		cin >> select;
		switch (select)
		{
		case '1': viewAttendanceListOfACourse(); break;
		case '2':exportAttendanceListToCSV(); break;
		default: {system("cls"); goto L5;  }
		}
	}
	else if (n == '5') {		// score
		L6:cout << "1. Search and view scoreboard of a course\n";
		cout << "2. Export a scoreboard to a csv file \n";
		char select;
		cout << "Your selection : ";
		cin >> select;
		switch (select)
		{
		case '1': viewScoreBoardOfACourse(); break;
		case '2':exportScoreBoardToCSV(); break;
		default: {system("cls"); goto L6;  }
		}
	}
	cout << endl << endl;
	cout << "---------------------------------\n";
	mainMenu();
}
void staffMenu()
{
	
	L1:system("cls");
	cout << "------------------------Menu-----------------------" << endl;
	cout << "1. Student and Class\n";
	cout << "2. Course\n";
	cout << "3. Schedule\n";
	cout << "4. Attendance\n";
	cout << "5. ScoreBoard\n";
	cout << "Your selection : ";
	char select; cin >> select;
	if (select < '1' || select>'5')
		goto L1;
	showMenuStaff(select);
}

void lecturerMenu()
{
	LL1:system("cls");
	char selection;
	cout << "1.Import score board of a course\n";
	cout << "2.Edit grade of a student\n";
	cout << "3.View a scoreboard\n";
	cout << "Your selection : ";
	cin >> selection;
	switch (selection)
	{
	case '1': importScoreboardOfACourse(); break;
	case '2': editGradeOfAStudent(); break;
	case '3': viewAScoreBoard(); break;
	default: goto LL1; break;
	}
	cout << endl << endl;
	cout << "---------------------------------\n";
	mainMenu();
}

void mainMenu()
{
	
	//login
	if (userCurrent.size() == 0)
	{
		bool logined = 0;
		logined = login();
		while (!logined)
		{
			cout << "Password or username incorrect \n";
			logined = login() ? 1 : 0;
		}
		system("cls");
	}

	//menu selection
	char select;
	LOOP:cout << "Please choose selection :" << endl;
	cout << "1. Show menu\n2. View info\n3. Change Password\n4. Log out\n5. Exit\n";
	cout << "Your selection :   ";
	cin >> select;
	system("cls");
	switch (select)
	{
		case '1': switch (userType)
				{
					case 0: studentMenu(); break;
					case 1: staffMenu(); break;
					case 2: lecturerMenu(); break;
				} break;
		case '2':viewInfo();  break;
		case '3':changePassword();  break;
		case '4':logOut(); break;
		case '5': exit(0); break;
		default: goto LOOP; break;
	}
}