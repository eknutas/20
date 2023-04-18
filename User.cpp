/* User.cpp Console_chat */

#include "User.h"

User::User(const std::string& name, const std::string& login, const std::string& password) : _name(name), _login(login), _password(password)
{
}

const std::string User::getName() const
{
    return _name;
}

const std::string User::getLogin() const
{
    return _login;
}

bool User::access(const std::string& login, const std::string& password)
{
    return (_login == login && _password == password);
}
