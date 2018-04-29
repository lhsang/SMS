#pragma once
#include"dataStructures.h"
 int userType =-1;
string userCurrent = "";

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
	for (i = 0; i<argc ; i++)
	{
		if(string(azColName[i]).compare("PASSWORD") == 0)
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
string formatDate(string date)
{
	char link = '-';
	string ans = "";
	if (date.find('/') != std::string::npos)
		link = '/';
	string t1, t2, t3;
	t1 = date.substr(0, date.find(link)); if (t1.size() == 1) t1 = "0" + t1;
	t2 = date.substr(date.find_first_not_of(link) + 1, date.find_last_of(link) - date.find_first_of(link) - 1); if (t2.size() == 1) t2 = "0" + t2;
	t3 = subUntil(date, date.find_last_of(link) + 1, link); if (t3.size() == 1) t3 = "0" + t3;
	if (t1.size() == 4)
		ans = t1 + "-" + t2 + "-" + t3;
	else ans = t3 + "-" + t2 + "-" + t1;
	return ans;
}