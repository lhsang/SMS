#pragma once
#include"dataStructures.h"
 int userType =-1;
string userCurrent = "";
ofstream ex;
int editDB(void *data, int argc, char **argv, char **azColName)
{
	return 0;
}
int getDB(void *data, int argc, char **argv, char **azColName)
{
	if (argc == 0)
		return 0;
	userCurrent = argv[0];
	userType = atoi(argv[4]);
	return 0;
}
int output(void *data, int argc, char **argv, char **azColName)
{
	int i;
	cout << (const char*)data << "\n";
	for (i = 0; i<argc; i++)
	{
		if (string(azColName[i]).compare("PASSWORD") == 0)
			continue;
		fprintf(stderr, "%s = %s     ", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	cout << endl;
	return 0;
}
string formatDate(string date);

int exporting(void *data, int argc, char **argv, char **azColName)
{
	int i; string clause = "";
	cout << (const char*)data << "\n";
	for (i = 0; i<argc; i++)
	{
		clause =clause+ argv[i] + ',';
	}
	clause += "\n";
	ex << clause;
	cout << endl;
	return 0;
}
int exportDB(void *data, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i<argc; i++)
	{

		if (string(azColName[i]).compare("PASSWORD") == 0)
			continue;
		fprintf(stderr, "%s = %s     ", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	cout << endl;
	return 0;
}
string subUntil(string s, int pos, char x)
{
	string ans = "";
	while (pos < s.size() && s[pos] != x)
		ans += s[pos++];
	return ans;
}
string splitData(string buff, string className)
{
	User u; u.className = className;
	string sql = "insert into user values('";
	buff.erase(0, buff.find(',') + 1);	u.userName = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.fullName = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.email = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.phone = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.password = subUntil(buff, 0, ',');
	sql += u.userName + "','" + u.fullName + "','" + u.email + "','" + u.phone + "'," + "0,'" + u.className + "','" + u.password + "')";
	return sql;
}
string split(string &buff) {
	buff.erase(0, buff.find(',') + 1);
	string temp;
	if(buff.find(',') != std::string::npos)
		temp= buff.substr(0, buff.find(','));
	else temp = subUntil(buff, 0, ',');
	return temp;
}
string splitDataForCourse(string buff)
{
	string sql = "insert into course values('", temp = "";
	Course c;

	c.courseCode = split(buff);	c.year = split(buff);c.semester = atoi( split(buff).c_str()); 
	c.courseName = split(buff);	c.lecturerUserName = split(buff);	c.startAt = formatDate(split(buff));
	c.endAt =formatDate(split(buff));	c.from = split(buff);	c.to = split(buff);	c.dateOfWeek = split(buff);

	sql = sql + c.courseCode + "','" + c.year + "'," + to_string(c.semester) + ",'" + c.courseName + "','" + c.lecturerUserName + "','"
		+ c.startAt + "','" + c.endAt + "','" + c.from + "','" + c.to + "','" + c.dateOfWeek + "')";
	return sql;
}
string splitDataForScore(string buff)
{
	string sql = "insert into score values('";
	Score s;
	s.courseCode = split(buff); s.year = split(buff); s.semester = atoi(split(buff).c_str());
	s.studentID = split(buff); s.midtermScore = std::stof(split(buff).c_str(), NULL);
	s.labScore = std::stof(split(buff).c_str(), NULL); 
	s.finalScore = std::stof(split(buff).c_str(), NULL);;
	s.bonus= std::stof(split(buff).c_str(), NULL);

	sql = sql + s.courseCode + "','" + s.year + "'," + to_string(s.semester) + ",'" + s.studentID + "'," 
		+ to_string(s.midtermScore) + "," + to_string(s.labScore) + "," + to_string(s.finalScore) + "," + to_string(s.bonus) + ")";
	return sql;
}
string splitDataForSchedule(string buff)
{
	string code, start, end, dateofweek;
	code = split(buff);
	start = split(buff);
	end = split(buff);
	dateofweek = split(buff);
	string sql = "update course set startsection=" + start + " , endsection=" + end + " , dateofweek='" + dateofweek + "' where coursecode='" + code + "'";
	return sql;
}
string formatDate(string date)
{
	// 20/6/2018
	char link = '-';
	string ans = "";
	if (date.find('/') != std::string::npos)
		link = '/';
	string t1, t2, t3;
	t1 = date.substr(0, date.find(link)); if (t1.size() == 1) t1 = "0" + t1;
	date.erase(0, date.find(link) + 1);
	t2 = date.substr(0,date.find(link)); if (t2.size() == 1) t2 = "0" + t2;
	date.erase(0, date.find(link) + 1);
	t3 = subUntil(date,0,link); if (t3.size() == 1) t3 = "0" + t3;
	if (t1.size() == 4)
		ans = t1 + "-" + t2 + "-" + t3;
	else ans = t3 + "-" + t2 + "-" + t1;
	return ans;
}