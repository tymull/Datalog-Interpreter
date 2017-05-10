#include "ID.h"


ID::ID()
{
}


ID::~ID()
{
}


int ID::getReadings()
{
	return readings;
}


bool ID::stillID(int it, const vector <char>& input_file)
{
	if (isalnum(getChar(it, input_file)))
	{
		readings++;
		it++;
		return stillID(it, input_file);
	}
	//HAVE TO FIX THIS '\xff' is eof right click and make text file
	else if (isblank(getChar(it, input_file)) || getChar(it, input_file) == '\n' || it == input_file.size()-1)
	{
		return true; //will only accept if the next character is blank or new line or EOF.
	}
	else
	{
		return true;//reached some symbol
	}
}


bool ID::read(int it, const vector <char>& input_file)
{
	if (isalpha(getChar(it, input_file))) //checks to see if first character is a letter
	{
		readings++; //indicates that it successfully read
		it++;
		return stillID(it, input_file);
	}
	else
	{
		return false;
	}
}


void ID::resetReadings()
{
	readings = 0;
}


Token ID::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "ID";
	string content(input_file.begin() + it, input_file.begin() + it + readings); // for some crazy reason, can't put input_file[it]
	Token token(name, content, current_line);
	return token;
}
