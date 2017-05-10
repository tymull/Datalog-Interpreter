#include "Queries.h"


Queries::Queries()
{
}


Queries::~Queries()
{
}


int Queries::getReadings()
{
	return readings;
}


bool Queries::s(int it, const vector <char>& input_file)
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


bool Queries::e2(int it, const vector <char>& input_file)
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


bool Queries::i(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'i')
	{
		readings++;
		it++;
		return e2(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Queries::r(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'r')
	{
		readings++;
		it++;
		return i(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Queries::e1(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'e')
	{
		readings++;
		it++;
		return r(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Queries::u(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'u')
	{
		readings++;
		it++;
		return e1(it, input_file);
	}
	else
	{
		readings = 0; //because this could be an ID
		return false;
	}
}


bool Queries::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == 'Q')
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


void Queries::resetReadings()
{
	readings = 0;
}


Token Queries::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "QUERIES";
	string content("Queries");
	Token token(name, content, current_line);
	return token;
}
