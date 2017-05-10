#include "Database.h"

Database::Database(DatalogProgram data_p)
{
  dp = data_p;
  schemes = dp.getSchemes();
  facts = dp.getFacts();
  rules = dp.getRules();
  queries = dp.getQueries();

  if (!facts.empty()) //if there are facts to make relation tuples
  {
    schemesAndFacts();
  }
  else //just put in schemes
  {
    schemesOnly();
  }
  //cout << "1\n";
}


Database::~Database()
{
}


DatalogProgram Database::getDatalogProgram()
{
  return dp;
}


vector <Predicate> Database::getSchemes()
{
  return schemes;
}


vector <Predicate> Database::getFacts()
{
  return facts;
}


vector <RuleDP> Database::getRules()
{
  return rules;
}


vector <Predicate> Database::getQueries()
{
  return queries;
}


map <string,Relation> Database::getRelations()
{
  return relations;
}


void Database::setDatalogProgram(DatalogProgram data_p)
{
  dp = data_p;
}


void Database::addRelation(Relation relat)
{
  relations.insert(pair<string,Relation>(relat.getName(),relat));
}


Relation Database::evalPred(Predicate pred)//can maybe put this function in eval Rules
{
  vector <Parameter> params = pred.getParams();
  Relation relation_out = factCheck(relations[pred.getName()], params);
  return relation_out;
}


void Database::evalRules()
{
  //stringstream output;
  bool parse_flag = false; //flag if any new tuple inserted, will reparse rules
  Relation r1;
  //if(parse_flag)
  //cout << "No, No, No...." <<endl;
  //Relation r2;
  //int n = 0; //number of times parse through rules.
  //cout << "1\n";
  for (unsigned int i = 0; i < rules.size(); i++)
  {
    Predicate headPred = rules[i].getHeadPred();
    vector <Predicate> predicates = rules[i].getPredicates();//OPTIMIZE
    vector <int> project_indices;
    r1 = evalPred(predicates[0]);
    //cout << "2\n";
    for (unsigned int j = 1; j < predicates.size(); j++)//if more than one predicate
    {
    //  string relName1 = predicates[j].getName();
    //  if (j + 1 <= predicates.size())
    //  {
        //string relName2 = predicates[j+1].getName();
        //cout << "3\n";
      r1 = r1.naturalJoin(evalPred(predicates[j]));//relations[r1.getName()].naturalJoin(evalPred(predicates[j]));//faster to not use gets and to change in join.
    //  }
      r1.setName(predicates[j].getName());
    //  vector <int> project_indices;
    /*
      vector <Parameter> params = headPred.getParams();//list of schema to project --OPTIMIZE--also could just add a getParamsSize() maybe for some?
      Schema schema_list = r1.getSchema();
      for (unsigned int k = 0; k < params.size(); k++)
      {
        for (unsigned int l = 0; l < schema_list.size(); l++)//schemes will still be here even if no tuples
        {
          if (params[k].getValue() == schema_list[l])
          {
            project_indices.push_back(l);//first scheme to be projected, then next,....
          }
        }
      }

      //cout << "hey\n" << r1.toString();
      r1 = r1.project(project_indices);
      */
      //cout << r1.toString();
      /*
      if (relations[r1.getName()].unionize(r1));//already know right position, so no need to rename schema
      {
        parse_flag = true; //make sure to parse rules again
        //cout << relations[r1.getName()].toString() << "okay?\n";
      }
      */
    }
    vector <Parameter> params = headPred.getParams();//list of schema to project --OPTIMIZE--also could just add a getParamsSize() maybe for some?
    Schema schema_list = r1.getSchema();
    for (unsigned int k = 0; k < params.size(); k++)
    {
      for (unsigned int l = 0; l < schema_list.size(); l++)//schemes will still be here even if no tuples
      {
        if (params[k].getValue() == schema_list[l])
        {
          project_indices.push_back(l);//first scheme to be projected, then next,....
        }
      }
    }
    r1 = r1.project(project_indices);
    //cout << "before\n" << relations[headPred.getName()].toString() << "okay?\n";
    if (relations[headPred.getName()].unionize(r1))//already know right position, so no need to rename schema
    {
      parse_flag = true; //make sure to parse rules again
      //cout << "after\n" << relations[headPred.getName()].toString() << "okay?\n";
      //cout << "after\n" << relations[r1.getName()].toString() << "okay?\n";
    }
  }

  rp_cnt++;
  if (parse_flag)
  {
    evalRules();//parse rules again to add to relations
  }
  return;
  //return output.str();
}


string Database::evalQueries()
{
  stringstream output;
  output << "Schemes populated after " << rp_cnt << " passes through the Rules.\n";
  for (unsigned int i = 0; i < queries.size(); i++)//this will process each query
  {
    output << queries[i].toString() << "? ";
    //DO NOT NEED TO CHECK FOR QUERIES THAT DO NOT CORRELATE TO A SCHEME!
    //vector <Relation> relations2 = relations;
    //cout << relations2[0].toString();
    //for (unsigned int j = 0; j < relations.size(); j++)//find corresponding relation
    //{
      //if (relations[j].getName() == queries[i].getName())//if part of same scheme
      //{//query ID at this position with map can assume queries will always exist
        //cout << "2\n";
    vector <Parameter> params = queries[i].getParams();
    Relation relation_out = factCheck(relations[queries[i].getName()], params);//MAYBE need to not alter relation passed into fact check?
    output << relation_out.toString();
        //cout << output.str() << endl;
        //cout << "3\n";
      //}//otherwise try again until find matching relation
    //}
  }

  return output.str();
}


Relation Database::factCheck(Relation relat, vector <Parameter> params)//use & here?
{
  vector <int> project_indices;
  set <string> seen_ID; //ASSUMING QUERY 1ST VARIABLES ARE IN ALPHABETICAL ORDER but might work regardless
  map <string,int> select_ref;//this will tie ID to index needed to compare
  Schema rename_schema; //keeps track of schema used to rename relation
  //vector <Parameter> params = query.getParams();
  //cout << "here\n";
  //cout << relat.toString() << endl;

  for (unsigned int i = 0; i < params.size(); i++)//parse each param in QUERY
  {
    if (params[i].getType() == "ID")//if current param is ID
    {
      if (seen_ID.count(params[i].getValue()))//if ID has been seen,
      {
        //this will select equal value from first schema referenced and give relation only if also includes
        //at this schema
        relat = relat.selectEqual(select_ref[params[i].getValue()], i);
      }
      else //if current ID is new
      {
        //adds index to list of schema to project, then to list to rename, then stores index of first of
        //this same ID to use to compare with duplicates in different indices, then adds to rename schema
        project_indices.push_back(i);
        seen_ID.insert(params[i].getValue());
        select_ref[params[i].getValue()] = i;
        rename_schema.push_back(params[i].getValue());
      }
    }
    else //if current param is STRING
    {
      //cout << "4\n";
      //only keep tuples that have this value at this index in relat
      relat = relat.selectValue(i, params[i].getValue());
      //cout << "5\n";
    }
  }
  if (!project_indices.empty())//if there is something to project
  {
    relat = relat.project(project_indices);
    //relat = relat.renameR(rename_schema);
  }//otherwise don't worry about it
  relat = relat.renameR(rename_schema);//will rename all schema to be projected at once
  //if nothing to project, this will make schema empty and thus not print any tuples in toString
  //cout << "1";

  return relat;
}


void Database::schemesOnly()
{
  for (unsigned int i = 0; i < schemes.size(); i++) //parses through schemes
  {
    Schema schema; //list of schema
    set <Tuple> tuples;//this will be empty
    string name = schemes[i].getName();//scheme names are all unique
    vector <Parameter> params = schemes[i].getParams();
    for (unsigned int j = 0; j < params.size(); j++)//parse each param in scheme
    {
      schema.push_back(params[j].getValue());//already know params in scheme are valid IDs
    }
    Relation relat(name, schema, tuples);//makes into a relation with no tuples
    relations.insert(pair<string,Relation>(name,relat));//places new relation onto list of relations
  }//now will move to next scheme for a new relation
}


void Database::schemesAndFacts()
{
  for (unsigned int i = 0; i < schemes.size(); i++) //parses through schemes
  {
    Schema schema; //list of schema
    set <Tuple> tuples;//will order vectors and not alter index of tuple
    string name = schemes[i].getName();//scheme names are all unique
    vector <Parameter> params = schemes[i].getParams();
    for (unsigned int j = 0; j < params.size(); j++)//parse each param in scheme
    {
      schema.push_back(params[j].getValue());//already know params in scheme are valid IDs
    }

    for (unsigned int j = 0; j < facts.size(); j++)//parses through facts
    {
      if (name == facts[j].getName())
      {
        Tuple tup; //vector of strings
        params = facts[j].getParams();
        for (unsigned int k = 0; k < params.size(); k++)//parse each param in fact
        {
          tup.push_back(params[k].getValue());//already know params in fact are valid strings--push onto tuple
        }
        tuples.insert(tup);//will insert tup into set before moving on to next fact
      }
    }
    Relation relat(name, schema, tuples);//makes into a relation
    relations.insert(pair<string,Relation>(name,relat));//places new relation onto list of relations
  }//now will move to next scheme for a new relation
}


string Database::toString()
{
}
