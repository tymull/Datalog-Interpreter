#include "ColonDash.h"


ColonDash::ColonDash()
{
}


ColonDash::~ColonDash()
{
}


int ColonDash::getReadings()
{
	return readings;
}


bool ColonDash::dashCheck(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '-')
	{
		readings++;
		return true;
	}
	else
	{
		return false;
	}
}


bool ColonDash::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == ':')
	{
		readings++; //indicates that it successfully read
		it++; //to go to next point in vector in recursion. IF SEGFAULTS CHECK HERE--may be iterating to impossible amount
		return dashCheck(it, input_file);
	}
	else
	{
		return false;
	}
}


void ColonDash::resetReadings()
{
	readings = 0;
}


Token ColonDash::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "COLON_DASH";
	string content(":-");
	Token token(name, content, current_line);
	return token;
}
