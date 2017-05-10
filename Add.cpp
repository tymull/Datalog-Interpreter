#include "Add.h"


Add::Add()
{
}


Add::~Add()
{
}


int Add::getReadings()
{
	return readings;
}


bool Add::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '+')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void Add::resetReadings()
{
	readings = 0;
}


Token Add::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "ADD";
	string content("+");
	Token token(name, content, current_line);
	return token;
}