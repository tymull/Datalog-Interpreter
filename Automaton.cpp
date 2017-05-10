#include "Automaton.h"


Automaton::Automaton()
{
}


Automaton::~Automaton()
{
}

char Automaton::getChar(int it, const vector <char>& input_file)
{
	return input_file[it]; //returns character at given iteration.
}

//will probably make this virtual or used for undefined
Token Automaton::tokenize(unsigned int& current_line, int it, const vector <char>& input_file)
{
	string name = "ERROR";
	string content = "--came from Automaton--";
	int line = 0;
	Token error(name, content, line);
	return error;
}