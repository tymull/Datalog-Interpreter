#include "MyString.h"


MyString::MyString()
{
}


MyString::~MyString()
{
}


int MyString::getReadings()
{
	return readings;
}


bool MyString::endString(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\'')
	{
		readings++; //indicates that it successfully read
		it++;
		return isStuff(it, input_file); //if it has another ', will continue reading
	}
	else
	{
		return true;
	}
}


bool MyString::isStuff(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\'')
	{
		readings++;
		it++;
		return endString(it, input_file);
	}
	else if (it == input_file.size()-1) //if it has reached the EOF
	{
		readings = 0;
		extra_lines = 0; //reset extra_lines for next time
		return false; //this makes it undefined
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


bool MyString::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\'')
	{
		readings++; //indicates that it successfully read
		it++;
		return isStuff(it, input_file);
	}
	else
	{
		return false;
	}
}


void MyString::resetReadings()
{
	readings = 0;
}


Token MyString::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "STRING";
	string content(input_file.begin() + it, input_file.begin() + it + readings); // for some crazy reason, can't put input_file[it]
	int line = current_line; //this returns line that it started on
	current_line += extra_lines; //this adds new lines from method to Lexical Analyzer that would have been skipped
	extra_lines = 0; //reset extra_lines for next time
	Token token(name, content, line);
	return token;
}
