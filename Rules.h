#pragma once
#include "Automaton.h"
class Rules :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	Rules();
	~Rules();
	int getReadings();
	bool u(int it, const vector <char>& input_file);
	bool l(int it, const vector <char>& input_file);
	bool e(int it, const vector <char>& input_file);
	bool s(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

