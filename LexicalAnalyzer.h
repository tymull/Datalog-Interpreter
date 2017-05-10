#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Token.h"
#include "Automaton.h"
#include "Comma.h"
#include "Period.h"
#include "QMark.h"
#include "LeftParen.h"
#include "RightParen.h"
#include "Colon.h"
#include "ColonDash.h"
#include "Multiply.h"
#include "Add.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"
#include "ID.h"
#include "MyString.h"
#include "LineComment.h"
#include "BlockComment.h"
#include "WhiteSpace.h"
#include "MyUndefined.h"

using namespace std;

class LexicalAnalyzer
{
	friend class Comma;
protected:
	vector <char> input_file;
	vector <char> temp_file;
public:
	LexicalAnalyzer(char* input_file_in);
	~LexicalAnalyzer(); //&input file as a paramater
	vector <char> getInputFile();
	void analyze(char* input_file); //can change value of input_file
	char getChar(int it);
	vector <Token> scan(); //will scan file using all automata subclasses and output tokens

};
