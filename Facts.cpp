#include "Facts.h"


Facts::Facts()
{
}


Facts::~Facts()
{
}


int Facts::getReadings()
{
	return readings;
}


bool Facts::s(int it, const vector <char>& input_file)
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


bool Facts::t(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 't')
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


bool Facts::c(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'c')
	{
		readings++;
		it++;
		return t(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Facts::a(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'a')
	{
		readings++;
		it++;
		return c(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Facts::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'F')
	{
		readings++; //indicates that it successfully read
		it++; //to go to next point in vector in recursion. IF SEGFAULTS CHECK HERE--may be iterating to impossible amount
		return a(it, input_file);
	}
	else
	{
		return false;
	}
}


void Facts::resetReadings()
{
	readings = 0;
}


Token Facts::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "FACTS";
	string content("Facts");
	Token token(name, content, current_line);
	return token;
}
