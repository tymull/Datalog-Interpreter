#include "RightParen.h"


RightParen::RightParen()
{
}


RightParen::~RightParen()
{
}


int RightParen::getReadings()
{
	return readings;
}


bool RightParen::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == ')')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void RightParen::resetReadings()
{
	readings = 0;
}


Token RightParen::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "RIGHT_PAREN";
	string content(")");
	Token token(name, content, current_line);
	return token;
}
