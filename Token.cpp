#include "Token.h"


Token::Token(string name, string content, int line)
{
	this->name = name;
	this->content = content;
	this->line = line;
}


Token::~Token()
{
}


string Token::getName()
{
	return name;
}


string Token::getContent()
{
	return content;
}


int Token::getMyLine()
{
	return line;
}


string Token::getToken()
{
	stringstream token;
	token << "(" << name << ",\"" << content << "\"," << line << ")";
	return token.str();
}