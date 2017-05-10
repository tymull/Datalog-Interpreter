#include "LeftParen.h"


LeftParen::LeftParen()
{
}


LeftParen::~LeftParen()
{
}


int LeftParen::getReadings()
{
	return readings;
}


bool LeftParen::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '(')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void LeftParen::resetReadings()
{
	readings = 0;
}


Token LeftParen::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "LEFT_PAREN";
	string content("(");
	Token token(name, content, current_line);
	return token;
}
