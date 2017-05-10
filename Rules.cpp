#include "Rules.h"


Rules::Rules()
{
}


Rules::~Rules()
{
}


int Rules::getReadings()
{
	return readings;
}


bool Rules::s(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 's')
	{
		readings++;
		return true;
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Rules::e(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'e')
	{
		readings++;
		it++;
		return s(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Rules::l(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'l')
	{
		readings++;
		it++;
		return e(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Rules::u(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'u')
	{
		readings++;
		it++;
		return l(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Rules::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'R')
	{
		readings++; //indicates that it successfully read
		it++; //to go to next point in vector in recursion. IF SEGFAULTS CHECK HERE--may be iterating to impossible amount
		return u(it, input_file);
	}
	else
	{
		return false;
	}
}


void Rules::resetReadings()
{
	readings = 0;
}


Token Rules::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "RULES";
	string content("Rules");
	Token token(name, content, current_line);
	return token;
}
