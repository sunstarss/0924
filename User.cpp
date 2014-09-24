#include "User.h"
using namespace std;


User::User(const string &username, 
		   const string &password)
	:username_(username), 
	 password_(password)
{

}

const string &User::getUserName() const
{
	return username_;
}

bool User::authentication(const string &password) const
{
	return password == password_;
}
