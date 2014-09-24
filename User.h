#ifndef USER_H_
#define USER_H_

#include <string>

class User
{
public:
	User(const std::string &username, const std::string &password);

	const std::string &getUserName() const;
	bool authentication(const std::string &password) const;
private:
	std::string username_;
	std::string password_;
};


#endif /* USER_H_ */