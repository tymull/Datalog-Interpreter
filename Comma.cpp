#include "Comma.h"

Comma::Comma()
{
}


Comma::~Comma()
{
}


int Comma::getReadings()
{
	return readings;
}


bool Comma::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == ',') //checks to see if current iteration is a ','
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void Comma::resetReadings()
{
	readings = 0;
}


Token Comma::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "COMMA";
	string content(input_file.begin() + it, input_file.begin() + it + readings); // for some crazy reason, can't put input_file[it]
	Token token(name, content, current_line);
	return token;
}
