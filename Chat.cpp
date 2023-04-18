/* Chat.cpp Console_chat */

#include "Chat.h"

void Chat::chatting(const std::string& from)
{
	std::string str = "\033[2J\033[1;1H";	//clearing the console
	str += "Hello, " + from + '\n';
	for (size_t i = 0; i < size(_msg); ++i)
	{
		if (((*_msg[i]).getFrom() == from) || ((*_msg[i]).getTo() == from) || ((*_msg[i]).getTo() == "all")) {
			str += "From: " + (*_msg[i]).getFrom() + "     To: " + (*_msg[i]).getTo() + "\nMessage: " + (*_msg[i]).getText() + '\n';
		}
	}
	str += "Enter the recipient (all for everyone): ";
	socketWrite(str.c_str());
	_to = socketRead();
	socketWrite("Enter your message: ");
	_text = socketRead();
	_msg.push_back(std::make_unique<Message>(from, _to, _text));
}

void Chat::logIn()
{
	if (_usr.empty()) {
		throw "No user, registration required!";
	}
	socketWrite("Enter login: ");
	_login = socketRead();
	socketWrite("Enter password: ");
	_password = socketRead();
	for (size_t i = 0; i < size(_usr); ++i)
	{
		if ((*_usr[i]).access(_login, _password)) {	//login and password verification
			chatting((*_usr[i]).getName());	//enter the chat
			return;
		}
	}
	throw "Invalid login or password!";
}

void Chat::checkIn()
{
	socketWrite("Enter a new username: ");
	_name = socketRead();
	if (_name == "all") {
		throw "This name is busy! Please enter another name.";
	}
	for (size_t i = 0; i < size(_usr); ++i)
	{
		if (_name == (*_usr[i]).getName()) {
			throw "This name is busy! Please enter another name.";
		}
	}
	socketWrite("Enter new user login: ");
	_login = socketRead();
	for (size_t i = 0; i < size(_usr); ++i)
	{
		if (_login == (*_usr[i]).getLogin()) {
			throw "This login is busy! Please enter another login.";
		}
	}
	socketWrite("Enter the new user's password: ");
	_password = socketRead();
	_usr.push_back(std::make_unique<User>(_name, _login, _password));
}

char* Chat::socketRead()
{
	bzero(message, MESSAGE_LENGTH);
	read(connection, message, sizeof(message));
	return message;
}

void Chat::socketWrite(const char* msg)
{
	bzero(message, MESSAGE_LENGTH);
	strcpy(message, msg);
	write(connection, message, sizeof(message));
}