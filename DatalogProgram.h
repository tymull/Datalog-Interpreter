#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "Token.h"
#include "RuleDP.h"
#include "Predicate.h"
#include "Parameter.h"

class DatalogProgram
{
protected:
  vector <Predicate> schemes;
  vector <Predicate> facts;
  vector <RuleDP> rules;
  vector <Predicate> queries;
  set <string> domain;
public:
  DatalogProgram();
  ~DatalogProgram();
  vector <Predicate> getSchemes();
  vector <Predicate> getFacts();
  vector <RuleDP> getRules();
  vector <Predicate> getQueries();
  set <string> getDomain();
  void addScheme(Predicate pred);
  void addFact(Predicate pred);
  void addRule(RuleDP rule);
  void addQuery(Predicate pred);
  void setDomain();
  string domainToString(); //for keeping down complexity
  string toString();

};
