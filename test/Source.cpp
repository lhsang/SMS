#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<string>
using namespace std;
struct User
{
	string userName;
	string fullName;
	string email;
	string phone;

	int type;
	string password;
	string className;
};
string subUntil(string s, int pos, char x)
{
	string ans = "";
	while (pos < s.size() && s[pos] != x)
		ans += s[pos++];
	return ans;
}
string splitData(string buff,string className)
{
	User u; u.className = className;
	string sql = "insert into user values('";
	buff.erase(0, buff.find(',') + 1);	u.userName = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.fullName = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.email = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.phone = buff.substr(0, buff.find(','));
	buff.erase(0, buff.find(',') + 1);	u.password = subUntil(buff,0,',');
	sql += u.userName + "','" + u.fullName + "','" + u.email + "','" + u.phone + "'," + "0,'" + u.className+ "','" + u.password + "')";
	return sql;
}
int main()
{
	string fileName = "mm.csv";

	string className,title;
	ifstream f(fileName);
	getline(f, className);	
	className = subUntil(className, className.find(',') + 1, ',');

	getline(f, title);//no,id,name,phone,email,pass
	string sql = "";
	while (f.good())
	{
		
		string buff;
		getline(f, buff);
		if (buff == "")
			break;
		sql=splitData(buff,className);
		cout << sql << endl;
	}
	f.close();
	system("pause");
	return 0;
}