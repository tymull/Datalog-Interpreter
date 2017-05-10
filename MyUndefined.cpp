#include "MyUndefined.h"


MyUndefined::MyUndefined()
{
}


MyUndefined::~MyUndefined()
{
}


int MyUndefined::getReadings()
{
	return readings;
}

/*
bool MyUndefined::badID(int it, const vector <char>& input_file)
{
	if (isalnum(getChar(it, input_file)))
	{
		readings++;
		it++;
		return badID(it, input_file);
	}
	//HAVE TO FIX THIS '\xff' is eof right click and make text file
	else if (isblank(getChar(it, input_file)) || getChar(it, input_file) == '\n' || it == input_file.size())
	{
		return true; //will only accept if the next character is blank or new line or EOF.
	}
	else
	{
		return true; //reached some symbol
	}
}
*/

bool MyUndefined::endBlock(int it, const vector <char>& input_file)
{
	if (it == input_file.size()) //if it has reached the EOF
	{
		return true; //can't have eof before '#' makes undefined
	}
	else if (getChar(it, input_file) == '#')
	{
    readings = 0; //indicates it is closed block comment
    extra_lines = 0; //reset extra_lines for next time
		return false;
	}
	//with two '|' in a row, the first would be part of the comment and the second would repeat this method
	else if (getChar(it, input_file) == '|')
	{
		readings++;
		it++;
		return endBlock(it, input_file);
	}
	else if (getChar(it, input_file) == '\n') //catches new lines within read()
	{
		extra_lines++;
		readings++;
		it++;
		return isBlock(it, input_file);
	}
	else
	{
		return isBlock(it, input_file); //if it '#' doesn't follow '|', will continue reading
	}
}


bool MyUndefined::isBlock(int it, const vector <char>& input_file)
{
	if (it == input_file.size()) //if it has reached the EOF
	{
		return true; //can't have eof before '|' makes undefined
	}
	else if (getChar(it, input_file) == '\n') //catches new lines within read()
	{
		extra_lines++;
		readings++;
		it++;
		return isBlock(it, input_file);
	}
	else if (getChar(it, input_file) == '|')
	{
		readings++; //indicates that it successfully read
		it++;
		return endBlock(it, input_file); //if it has another ', will continue reading
	}
	else
	{
		readings++;
		it++;
		return isBlock(it, input_file); //keeps reading until reaches a '|'
	}
}


bool MyUndefined::lineOrBlock(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '|')
	{
		readings++;
		it++;
		return isBlock(it, input_file);
	}
	else
	{
		readings = 0;
		return false;//anything else would be a line comment
	}
}


bool MyUndefined::endString(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\'')
	{
		readings++; //indicates that it successfully read
		it++;
		return isStuff(it, input_file); //if it has another ', will continue reading
	}
	else
	{
    readings = 0; //this would be a valid string
    extra_lines = 0; //reset extra_lines for next time
		return false;
	}
}


bool MyUndefined::isStuff(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\'')
	{
		readings++;
		it++;
		return endString(it, input_file);
	}
	else if (it == input_file.size()) //if it has reached EOF
	{
		return true; //this makes it undefined
	}
	else if (getChar(it, input_file) == '\n') //catches new lines within read()
	{
		extra_lines++;
		readings++;
		it++;
		return isStuff(it, input_file);
	}
	else
	{
		readings++;
		it++;
		return isStuff(it, input_file);
	}
}


bool MyUndefined::read(int it, const vector <char>& input_file)
{
  if (isdigit(getChar(it, input_file))) //checks to see if first character is a number and therefore not ID
	{
		readings++; //indicates that it successfully read
		return true; //only reads one digit at a time as undefined
		//it++;
		//return badID(it, input_file);
	}
  else if (getChar(it, input_file) == '#')
	{
		readings++; //indicates that it successfully read
		it++;
		return lineOrBlock(it, input_file);
	}
	else if (getChar(it, input_file) == '\'')
	{
		readings++; //indicates that it successfully read
		it++;
		return isStuff(it, input_file);
	}
  else if (isblank(getChar(it, input_file)))
	{
		return false; //this will give max_readings to WhiteSpace
	}
	else
	{
    readings++;
		return true; //this will catch any extraneous invalid symbols. Valid symbols will have higher precedence
	}
}


void MyUndefined::resetReadings()
{
	readings = 0;
}


Token MyUndefined::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "UNDEFINED";
	string content(input_file.begin() + it, input_file.begin() + it + readings); // for some crazy reason, can't put input_file[it]
	int line = current_line; //this returns line that it started on
	current_line += extra_lines; //this adds new lines from method to Lexical Analyzer that would have been skipped
  extra_lines = 0; //reset extra_lines for next time
	Token token(name, content, line);
	return token;
}
