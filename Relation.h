#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include "Parser.h"
#include "Schema.h"
#include "Tuple.h"


class Relation
{
private:
  string name;
  Schema schema; //list of schema
  set <Tuple> tuples; //will order vectors and not alter index of Tuple
public:
  Relation(string name, Schema schema, set<Tuple> tuples);
  Relation(Schema schema); //a way to initialize relation only with schema
  Relation();
  ~Relation();
  string getName();
  Schema getSchema();
  set <Tuple> getTuples();
  void setName(string name);
  void addSchema(string scheme);
  void addTuple(Tuple tup);
  bool isjoinable(Schema scheme1, Tuple tup1, Schema scheme2, Tuple tup2);//tests if tuples are joinable
  Relation selectEqual(int index1, int index2);
  Relation selectValue(int index, string value);
  Relation project(vector <int> attributes);
  Relation renameR(Schema scheme);
  Relation naturalJoin(Relation relat);
  bool unionize(Relation relat);
  string toString();
};
