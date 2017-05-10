#include "Comment.h"


Comment::Comment()
{
}


Comment::~Comment()
{
}

int Comment::getReadings()
{
	return readings;
}

bool Comment::endBlock(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\xff')
	{
		return false; //can't have eof before '#'
	}
	if (getChar(it, input_file) == '#')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return isBlock(it, input_file); //if it '#' doesn't follow '|', will continue reading
	}
}

bool Comment::isBlock(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\xff')
	{
		return false; //can't have eof before '|'
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

bool Comment::isLine(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '\xff' || getChar(it, input_file) == '\n')
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

bool Comment::lineOrBlock(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '|')
	{
		readings++;
		it++;
		return isBlock(it, input_file);
	}
	else if (getChar(it, input_file) == '\xff' || getChar(it, input_file) == '\n')
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

bool Comment::read(int it, const vector <char>& input_file)
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

