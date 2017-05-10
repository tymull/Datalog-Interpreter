#pragma once
#include "Automaton.h"
#include <cctype>
class WhiteSpace :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	WhiteSpace();
	~WhiteSpace();
	int getReadings();
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

