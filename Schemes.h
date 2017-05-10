#pragma once
#include "Automaton.h"
class Schemes :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	Schemes();
	~Schemes();
	int getReadings();
	bool c(int it, const vector <char>& input_file);
	bool h(int it, const vector <char>& input_file);
	bool e1(int it, const vector <char>& input_file);
	bool m(int it, const vector <char>& input_file);
	bool e2(int it, const vector <char>& input_file);
	bool s(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

