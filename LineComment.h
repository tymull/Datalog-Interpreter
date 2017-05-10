#pragma once
#include "Automaton.h"
class LineComment :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	LineComment();
	~LineComment();
	int getReadings();
	bool isLine(int it, const vector <char>& input_file);
	bool lineOrBlock(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};
