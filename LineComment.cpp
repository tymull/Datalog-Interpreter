#include "LineComment.h"


LineComment::LineComment()
{
}


LineComment::~LineComment()
{
}


int LineComment::getReadings()
{
	return readings;
}


bool LineComment::isLine(int it, const vector <char>& input_file)
{
	if (it == input_file.size()-1 || getChar(it, input_file) == '\n')
	{
		return true; //this ends the line comment
	}
	else
	{
		readings++;
		it++;
		return isLine(it, input_file);
	}
}


bool LineComment::lineOrBlock(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '|')
	{
		return false; //false because should be block comment
	}
	else if (it == input_file.size()-1 || getChar(it, input_file) == '\n')
	{
		return true; //this ends the line comment
	}
	else
	{
		readings++;
		it++;
		return isLine(it, input_file);
	}
}


bool LineComment::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '#')
	{
		readings++; //indicates that it successfully read
		it++;
		return lineOrBlock(it, input_file);
	}
	else
	{
		return false;
	}
}


void LineComment::resetReadings()
{
	readings = 0;
}


Token LineComment::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "COMMENT";
	string content(input_file.begin() + it, input_file.begin() + it + readings); // for some crazy reason, can't put input_file[it]
	Token token(name, content, current_line);
	return token;
}
