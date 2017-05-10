#include "Parameter.h"

Parameter::Parameter()//string value, string type)
{
  //this->value = value;
  //this->type = type;
}


Parameter::~Parameter()
{
}


string Parameter::getValue()
{
  return value;
}


string Parameter::getType()
{
  return type;
}


void Parameter::setValue(string value)
{
  this->value = value;
}


void Parameter::setType(string type)
{
  this->type = type;
}
