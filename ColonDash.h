#pragma once
#include "Automaton.h"
class ColonDash :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	ColonDash();
	~ColonDash();
	int getReadings();
	bool dashCheck(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

