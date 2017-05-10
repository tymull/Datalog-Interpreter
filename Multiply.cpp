#include "Multiply.h"


Multiply::Multiply()
{
}


Multiply::~Multiply()
{
}


int Multiply::getReadings()
{
	return readings;
}


bool Multiply::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '*')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void Multiply::resetReadings()
{
	readings = 0;
}


Token Multiply::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "MULTIPLY";
	string content("*");
	Token token(name, content, current_line);
	return token;
}
