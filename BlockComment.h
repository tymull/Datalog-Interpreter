#pragma once
#include "Automaton.h"
class BlockComment :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
	unsigned int extra_lines = 0; //keeps track of lines read within read() that would be skipped in LexicalAnalyzer
public:
	BlockComment();
	~BlockComment();
	int getReadings();
	bool endBlock(int it, const vector <char>& input_file);
	bool isBlock(int it, const vector <char>& input_file);
	bool lineOrBlock(int it, const vector <char>& input_file);
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};
