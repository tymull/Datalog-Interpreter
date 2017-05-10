#include "Expression.h"
//this class is probably useless...
Expression::Expression()
{
}


Expression::~Expression()
{
}


Parameter Expression::getLeftParam()
{
  return left_param;
}


char Expression::getOper()
{
  return oper;
}


Parameter Expression::getRightParam()
{
  return right_param;
}


void Expression::addLeftParam(Parameter param)
{
  left_param = param;
}


void Expression::addOper(char oper)
{
  this->oper = oper;
}


void Expression::addRightParam(Parameter param)
{
  right_param = param;
}
