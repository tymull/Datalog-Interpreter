#pragma once
#include "Automaton.h"
class MyString :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
	unsigned int extra_lines = 0; //keeps track of lines read within read() that would be skipped in LexicalAnalyzer
public:
	MyString();
	~MyString();
	int getReadings();
	bool endString(int it, const vector <char>& input_file);
	bool isStuff(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};

