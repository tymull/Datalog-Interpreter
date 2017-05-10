#pragma once

#include "DatalogProgram.h"
#include "Relation.h"
#include <map>

class Database
{
private:
  DatalogProgram dp; //contains valid Datalog Program
  vector <Predicate> schemes;
  vector <Predicate> facts;
  vector <RuleDP> rules;
  vector <Predicate> queries;
  map <string,Relation> relations;
  int rp_cnt = 0;//counts how many times parses through rules
  //vector <Relation> relations; //list of relations from dp
public:
  Database(DatalogProgram data_p);
  ~Database();
  DatalogProgram getDatalogProgram();
  vector <Predicate> getSchemes();
  vector <Predicate> getFacts();
  vector <RuleDP> getRules();
  vector <Predicate> getQueries();
  map <string,Relation> getRelations();
  void setDatalogProgram(DatalogProgram data_p);
  void addRelation(Relation relat);
  Relation evalPred(Predicate pred);
  void evalRules();
  string evalQueries();
  Relation factCheck(Relation relat, vector <Parameter> params);
  void schemesOnly();
  void schemesAndFacts();
  string toString();
};
