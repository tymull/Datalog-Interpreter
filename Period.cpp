#include "Period.h"


Period::Period()
{
}


Period::~Period()
{
}


int Period::getReadings()
{
	return readings;
}


bool Period::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '.')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void Period::resetReadings()
{
	readings = 0;
}


Token Period::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "PERIOD";
	string content(".");
	Token token(name, content, current_line);
	return token;
}
