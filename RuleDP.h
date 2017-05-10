#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"

class RuleDP //DP is Datalog Program to differenciate from Rules in lexer
{
private:
  Predicate headPred;
  vector <Predicate> predicates;
public:
  RuleDP();//Predicate headPred, Predicate pred);
  ~RuleDP();
  Predicate getHeadPred();
  vector <Predicate> getPredicates();
  void setHeadPred(Predicate headPred);
  void addPredicate(Predicate pred);
  void clearPredicates();
  string toString();
};
