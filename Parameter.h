#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"

class Parameter
{
private:
  string value;
  string type;
public:
  Parameter();//string value, string type);
  ~Parameter();
  string getValue();
  string getType();
  void setValue(string value);
  void setType(string type);

};
