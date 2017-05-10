#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Parameter.h"

class Predicate
{
private:
  string name;
  vector <Parameter> params;
public:
  Predicate();//string name, Parameter param);
  ~Predicate();
  string getName();
  vector <Parameter> getParams();
  void setName(string name);
  void addParameter(Parameter param);
  void clearParams();
  string toString();
};
