/* User.h Console_chat */

#pragma once
#include <iostream>

class User
{
private:
	const std::string _name;
	const std::string _login;
	const std::string _password;
public:
	User() = default;

	User(const std::string& name, const std::string& login, const std::string& password);

	~User() = default;

	const std::string getName() const;

	const std::string getLogin() const;

	bool access(const std::string& login, const std::string& password);
};