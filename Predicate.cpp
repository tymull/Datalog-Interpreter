#include "Predicate.h"

Predicate::Predicate()//string name, Parameter param)
{
//  this->name = name;
//  params.push_back(param);
}


Predicate::~Predicate()
{
}


string Predicate::getName()
{
  return name;
}


vector <Parameter> Predicate::getParams()
{
  return params;
}


void Predicate::setName(string name)
{
  this->name = name;
}


void Predicate::addParameter(Parameter param)
{
  params.push_back(param);
}


void Predicate::clearParams()
{
  params.clear();
}


string Predicate::toString()
{
  stringstream output;
  output << name << "(";
  for (unsigned int i = 0; i < params.size(); i++)
  {
    if (i + 1 != params.size()) //if not last param
    {
      output << params[i].getValue() << ",";
    }
    else
    {
      output << params[i].getValue() << ")";
    }
  }
  return output.str();
}
