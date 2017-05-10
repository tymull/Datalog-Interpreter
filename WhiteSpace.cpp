#include "WhiteSpace.h"


WhiteSpace::WhiteSpace()
{
}


WhiteSpace::~WhiteSpace()
{
}


int WhiteSpace::getReadings()
{
	return readings;
}


bool WhiteSpace::read(int it, const vector<char>& input_file)
{
	if (isblank(getChar(it, input_file)))
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void WhiteSpace::resetReadings()
{
	readings = 0;
}


Token WhiteSpace::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "ERROR";
	string content = "--came from WhiteSpace--";
	int line = 0;
	Token error(name, content, line);
	return error;
}
