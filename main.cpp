#include "User.h"
#include "Session.h"
#include "Question.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <assert.h>
using namespace std;

vector<User> users;
Session session;
void loadUserInfo(const string &filename);
void loginSystem();
void inputUsername();
void inputPassword();
void authenticateUsername(const string &username);
void authenticatePassword(const string &password);

vector<Question> questions;
void loadQuestionInfo(const string &filename);
void submitAnswer();
void printQuestion();

int main(int argc, char const *argv[])
{
	loadUserInfo("user.txt");

	loginSystem();

	loadQuestionInfo("question.txt");

	cout << "登陆成功" << endl;
	printQuestion();

	return 0;
}

void loadUserInfo(const string &filename)
{
	ifstream infile(filename.c_str());
	if(!infile)
		throw runtime_error("用户资料打开失败");

	users.clear();

	string line;
	string username;
	string password;
	while(getline(infile, line))
	{
		istringstream is(line);
		is >> username >> password;
		users.push_back(User(username, password));
	}

	infile.close();
}


void loginSystem()
{
	inputUsername();
	inputPassword();
}


void inputUsername()
{
	cout << "请输入用户名: ";
	while(1)
	{
		try
		{
			string username;
			cin >> username;
			authenticateUsername(username);
			//走到这里，说明用户名正确
			session.setUsername(username);
			break;
		}
		catch(logic_error &e)
		{
			cout << "用户名错误，请重新输入：" << endl;
		}
	}
}

void inputPassword()
{
	cout << "请输入密码:";
	while(1)
	{
		try
		{
			string password;
			cin >> password;
			authenticatePassword(password);
			session.makeValid();
			break;
		}
		catch(logic_error &e)
		{
			cout << "密码错误，请重新输入" << endl;
		}
	}
}

//验证用户名，查看用户是否存在
void authenticateUsername(const string &username)
{
	vector<User>::iterator it;
	for(it = users.begin();
		it != users.end();
		++it)
	{
		if(it->getUserName() == username)
			break;
	}

	if(it == users.end())
		throw logic_error("用户名错误");
}


void authenticatePassword(const string &password)
{
	string username = session.getUsername();

	vector<User>::iterator it;
	for(it = users.begin();
		it != users.end();
		++it)
	{
		if(it->getUserName() == username)
			break;
	}

	assert(it != users.end());
	if(it->authentication(password) == false)
		throw logic_error("密码错误");
}



void loadQuestionInfo(const string &filename)
{
	ifstream infile(filename.c_str());
	if(!infile)
		throw runtime_error("问题资料打开失败");

	questions.clear();

	string line;
	Question ques;
	while(getline(infile, line)) //题干
	{
		ques.stem_ = line;
		for(int i = 0; i < 4; ++i)
		{
			getline(infile, line);
			if(!infile)
				throw runtime_error("问题格式错误!");
			ques.option_[i] = line;
		}
		getline(infile, line);
		istringstream is(line);
		string ans; is >> ans;
		if(ans.size() == 1 && ((ans[0] >= 'a' && ans[0] <= 'd') || (ans[0] >= 'A' && ans[0] <= 'D')))
		{
			ques.answer_ = ans[0];
		}
		else
			throw runtime_error("问题答案错误");

		questions.push_back(ques);
	}
}

void printQuestion()
{
	for(Question q : questions)
	{
		cout << q.stem_ << endl;
		for (int i = 0; i < 4; ++i)
		{
			cout << char('A' + i) << ")" << q.option_[i] << endl;
		}
		cout << q.answer_ << endl;
	}
}
