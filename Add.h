#pragma once
#include "Automaton.h"
class Add :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	Add();
	~Add();
	int getReadings();
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

