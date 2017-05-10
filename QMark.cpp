#include "QMark.h"


QMark::QMark()
{
}


QMark::~QMark()
{
}


int QMark::getReadings()
{
	return readings;
}


bool QMark::read(int it, const vector <char>& input_file)
{
	if (getChar(it, input_file) == '?')
	{
		readings++; //indicates that it successfully read
		return true;
	}
	else
	{
		return false;
	}
}


void QMark::resetReadings()
{
	readings = 0;
}


Token QMark::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "Q_MARK";
	string content("?");
	Token token(name, content, current_line);
	return token;
}