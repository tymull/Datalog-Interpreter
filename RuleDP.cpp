#include "RuleDP.h"

RuleDP::RuleDP()//Predicate headPred, Predicate pred)
{
//  this->headPred = headPred;
//  predicates.push_back(pred);
}


RuleDP::~RuleDP()
{
}


Predicate RuleDP::getHeadPred()
{
  return headPred;
}


vector <Predicate> RuleDP::getPredicates()
{
  return predicates;
}


void RuleDP::setHeadPred(Predicate headPred)
{
  this->headPred = headPred;
}


void RuleDP::addPredicate(Predicate pred)
{
  predicates.push_back(pred);
}


void RuleDP::clearPredicates()
{
  predicates.clear();
}


string RuleDP::toString()
{
  stringstream output;
  output << headPred.toString() << " :- ";
  for (unsigned int i = 0; i < predicates.size(); i++)
  {
    if (i + 1 != predicates.size()) //if not last predicate
    {
      output << predicates[i].toString() << ",";
    }
    else
    {
      output << predicates[i].toString() << ".";
    }
  }
  return output.str();
}
