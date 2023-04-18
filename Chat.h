/* Chat.h Console_chat */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Message.h"
#include "User.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных

class Chat
{
private:
	std::string _name;
	std::string _login;
	std::string _password;
	std::string _from;
	std::string _to;
	std::string _text;
	std::vector<std::unique_ptr<Message>> _msg;	//vector for messages
	std::vector<std::unique_ptr<User>> _usr;	//vector for users
public:
	Chat() = default;

	~Chat() = default;

	void chatting(const std::string&);

	void logIn();

	void checkIn();

	char* socketRead();

	void socketWrite(const char*);

	char message[MESSAGE_LENGTH];

	int connection;
};