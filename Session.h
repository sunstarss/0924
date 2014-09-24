#ifndef SESSION_H
#define SESSION_H

#include <string>

class Session
{
public:

	Session() :username_(""), valid_(false) { }

	void setUsername(const std::string &username)
	{ username_ = username; }
	const std::string &getUsername() const
	{ return username_; }

	void makeValid()
	{ valid_ = true; }
	bool isValid() const
	{ return valid_; }

private:

	std::string username_;
	bool valid_;

};


#endif
