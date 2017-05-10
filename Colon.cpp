#include "Colon.h"


Colon::Colon()
{
}


Colon::~Colon()
{
}


int Colon::getReadings()
{
	return readings;
}


bool Colon::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == ':')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void Colon::resetReadings()
{
	readings = 0;
}


Token Colon::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "COLON";
	string content(":");
	Token token(name, content, current_line);
	return token;
}