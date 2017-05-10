#pragma once
#include "Automaton.h"
class Facts :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	Facts();
	~Facts();
	int getReadings();
	bool a(int it, const vector <char>& input_file);
	bool c(int it, const vector <char>& input_file);
	bool t(int it, const vector <char>& input_file);
	bool s(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

