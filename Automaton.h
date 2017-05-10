#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Token.h"

using namespace std;

class Automaton
{
protected:
	
public:
	Automaton(); //by not making input_file in constructor, do not need to add an input_file for each subclass
	~Automaton();
	char getChar(int it, const vector <char>& input_file); //just do it++ when need to read in more recursively
	bool virtual read(int it, const vector <char>& input_file) = 0;
	int virtual getReadings() = 0;
	void virtual resetReadings() = 0;
	Token virtual tokenize(unsigned int& current_line, int it, const vector <char>& input_file);

};

