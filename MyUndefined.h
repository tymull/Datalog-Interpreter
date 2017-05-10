#pragma once
#include "Automaton.h"
#include <cctype>
class MyUndefined :
	public Automaton
{
private:
	int readings = 0; //number of characters read by this machine
	unsigned int extra_lines = 0; //keeps track of lines read within read() that would be skipped in LexicalAnalyzer
public:
	MyUndefined();
	~MyUndefined();
	int getReadings();
  //bool badID(int it, const vector <char>& input_file);//for detecting invalid IDs
  bool endBlock(int it, const vector <char>& input_file);//for detecting unclosed block comments
	bool isBlock(int it, const vector <char>& input_file);//for detecting unclosed block comments
	bool lineOrBlock(int it, const vector <char>& input_file);//for detecting unclosed block comments
	bool endString(int it, const vector <char>& input_file); //for detecting unclosed strings
	bool isStuff(int it, const vector <char>& input_file);//for detecting unclosed strings
	bool read(int it, const vector <char>& input_file);
	void resetReadings();
	Token tokenize(unsigned int& current_line, int it, const vector <char>& input_file);
};
