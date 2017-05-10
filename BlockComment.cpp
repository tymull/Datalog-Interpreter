#include "BlockComment.h"


BlockComment::BlockComment()
{
}


BlockComment::~BlockComment()
{
}


int BlockComment::getReadings()
{
	return readings;
}


bool BlockComment::endBlock(int it, const vector <char>& input_file)
{
	if (it == input_file.size()-1) //if it has reached the EOF
	{
		readings = 0;
		extra_lines = 0; //reset extra_lines for next time
		return false; //can't have eof before '#'
	}
	else if (getChar(it, input_file) == '#')
	{
		readings++; //indicates that it successfully read
		return true;
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


bool BlockComment::isBlock(int it, const vector <char>& input_file)
{
	if (it == input_file.size()-1) //if it has reached the EOF
	{
		readings = 0;
		extra_lines = 0; //reset extra_lines for next time
		return false; //can't have eof before '|'
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


bool BlockComment::lineOrBlock(int it, const vector <char>& input_file)
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

bool BlockComment::read(int it, const vector <char>& input_file)
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


void BlockComment::resetReadings()
{
	readings = 0;
}


Token BlockComment::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "COMMENT";
	string content(input_file.begin() + it, input_file.begin() + it + readings); // for some crazy reason, can't put input_file[it]
	int line = current_line; //this returns line that it started on
	current_line += extra_lines; //this adds new lines from method to Lexical Analyzer that would have been skipped
	extra_lines = 0; //reset extra_lines for next time
	Token token(name, content, line);
	return token;
}
