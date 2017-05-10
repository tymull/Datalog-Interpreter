#pragma once
#include "Automaton.h"
class Comment :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
public:
	Comment();
	~Comment();
	int getReadings();
	bool endBlock(int it, const vector <char>& input_file);
	bool isBlock(int it, const vector <char>& input_file);
	bool isLine(int it, const vector <char>& input_file);
	bool lineOrBlock(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
};

