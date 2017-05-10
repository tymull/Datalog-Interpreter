#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class Token
{
private:
	string name = "null";
	string content;
	int line;
public:
	Token(string name, string content, int line);
	~Token();
	string getName();
	string getContent();
	int getMyLine();
	string getToken();
};

