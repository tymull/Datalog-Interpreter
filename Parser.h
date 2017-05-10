#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Token.h"
#include "DatalogProgram.h"

class Parser
{
private:
	int it = 0; //initialize first iteration of Token vector
	vector <Token> tokens;
	DatalogProgram dp; //will hold vectors of schemes, facts, etc.
 //below used to store info to be pushed into dp vectors
	Predicate pred; //this will be cleared and reused for each part
	RuleDP my_rule;
	Parameter param; //used to push info into predicate
	stringstream param_stream;
	vector <Predicate> pred_list;//used to push preds onto rule or query
public:
	Parser(vector <Token> tokens);
	~Parser();
	int getIt();
	vector <Token> getTokens();
	DatalogProgram getDatalogProgram();
	void ignoreComments();
	void match(string item);
	//below are the functions that represent the grammar of the datalog Program
	void datalogProgram();
	void scheme();
	void schemeList();
	void idList();
	void fact();
	void factList();
	void rule();
	void ruleList();
	void headPredicate();
	void predicate();
	void predicateList();
	void parameter();
	void parameterList();
	void expression();
	void myOperator();
	void query();
	void queryList();
	void stringList();
	//this next method will determine if the input is valid
	DatalogProgram validate();

};
