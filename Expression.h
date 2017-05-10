#pragma once

#include "Parameter.h"
//Expression class may be completely useless...
class Expression :
  public Parameter
{
private:
  Parameter left_param;
  char oper;
  Parameter right_param;
public:
  Expression();
  ~Expression();
  Parameter getLeftParam();
  char getOper();
  Parameter getRightParam();
  void addLeftParam(Parameter param);
  void addOper(char oper);
  void addRightParam(Parameter param);

};
