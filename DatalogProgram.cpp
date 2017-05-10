#include "DatalogProgram.h"

DatalogProgram::DatalogProgram()
{
}


DatalogProgram::~DatalogProgram()
{
}


vector <Predicate> DatalogProgram::getSchemes()
{
  return schemes;
}


vector <Predicate> DatalogProgram::getFacts()
{
  return facts;
}


vector <RuleDP> DatalogProgram::getRules()
{
  return rules;
}


vector <Predicate> DatalogProgram::getQueries()
{
  return queries;
}


set <string> DatalogProgram::getDomain()
{
  return domain;
}


void DatalogProgram::addScheme(Predicate pred)
{
  schemes.push_back(pred);
}


void DatalogProgram::addFact(Predicate pred)
{
  facts.push_back(pred);
}


void DatalogProgram::addRule(RuleDP rule)
{
  rules.push_back(rule);
}


void DatalogProgram::addQuery(Predicate pred)
{
  queries.push_back(pred);
}


void DatalogProgram::setDomain()
{
  if (!facts.empty())//if there are facts
  {
    for (unsigned int i = 0; i < facts.size(); i++)
    {
      vector <Parameter> params = facts[i].getParams();
      for (unsigned int j = 0; j < params.size(); j++)
      { //this will input all facts and order them
        domain.insert(params[j].getValue());
      }
    }
  }
}


string DatalogProgram::domainToString()
{
  stringstream output;
  output << "Domain(" << domain.size() <<"):\n";
  if (!domain.empty())//if domain is not empty
  {
    for (set <string>::iterator i = domain.begin(); i != domain.end(); i++)//stop before end
    {
      output << "  " << *i << endl;
    }
  //  output << "  " << *domain.end();
  }
  return output.str();
}


string DatalogProgram::toString()
{
  stringstream output;
  output << "Success!\nSchemes(" << schemes.size() << "):\n";
  for (unsigned int i = 0; i < schemes.size(); i++)
  {
    output << "  " << schemes[i].toString() << endl;
  }
  output << "Facts(" << facts.size() << "):\n";
  if (!facts.empty())//if facts is not empty
  {
    for (unsigned int i = 0; i < facts.size(); i++)
    {
      output << "  " << facts[i].toString() << ".\n";
    }
  }
  output << "Rules(" << rules.size() << "):\n";
  if (!rules.empty())//if rules is not empty
  {
    for (unsigned int i = 0; i < rules.size(); i++)
    {
      output << "  " << rules[i].toString() << endl;
    }
  }
  output << "Queries(" << queries.size() << "):\n";
  for (unsigned int i = 0; i < queries.size(); i++)
  {
    output << "  " << queries[i].toString() << "?\n";
  }
  output << domainToString();
  return output.str();
}
