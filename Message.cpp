/* Message.cpp Console_chat */

#include "Message.h"

Message::Message(const std::string& from, const std::string& to, const std::string& text) : _from(from), _to(to), _text(text)
{
}

const std::string Message::getFrom() const
{
	return _from;
}

const std::string Message::getTo() const
{
	return _to;
}

const std::string Message::getText() const
{
	return _text;
}
