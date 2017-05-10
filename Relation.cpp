#include "Relation.h"

Relation::Relation(string name, Schema schema, set<Tuple> tuples)
{
  this->name = name;
  this->schema = schema;
  this->tuples = tuples;
}


Relation::Relation(Schema schema)
{
  this->schema = schema;
}


Relation::Relation()
{
}


Relation::~Relation()
{
}


string Relation::getName()
{
  return name;
}


Schema Relation::getSchema()
{
  return schema;
}


set <Tuple> Relation::getTuples()
{
  return tuples;
}


void Relation::setName(string name)
{
  this->name = name;
}


void Relation::addSchema(string scheme)
{
  schema.push_back(scheme);
}


void Relation::addTuple(Tuple tup)
{
  tuples.insert(tup);
}


bool Relation::isjoinable (Schema scheme1, Tuple tup1, Schema scheme2, Tuple tup2)
{
  for (unsigned int i = 0; i < scheme1.size(); i++)
  {
    for (unsigned int j = 0; j < scheme2.size(); j++)
    {
      if (scheme1[i] == scheme2[j] && tup1[i] != tup2[j])
      {
        return false;
      }
    }
  }
  return true;
}


Relation Relation::selectEqual(int index1, int index2)
{
  set <Tuple> equal_tuples;
  for (set <Tuple>::iterator i = tuples.begin(); i != tuples.end(); i++)//check all tuples in Relation
  {
    if ((*i)[index1] == (*i)[index2])//if these two attributes are equal in current tuple
    {
      equal_tuples.insert(*i);//then add tuple to output
    }
  }
  Relation output(name, schema, equal_tuples);//output relation with updated properties
  return output;
}


Relation Relation::selectValue(int index, string value)
{
  set <Tuple> equal_tuples;
  for (set <Tuple>::iterator i = tuples.begin(); i != tuples.end(); i++)//check all tuples in Relation
  {
    if ((*i)[index] == value)//if this attribute has same value in current tuple
    {
      equal_tuples.insert(*i);//then add tuple to output
    }
  }
  Relation output(name, schema, equal_tuples);//output relation with updated properties
  return output;
}


Relation Relation::project(vector <int> attributes)//list of indexes to project
{
  Schema new_schema;
  set <Tuple> new_tuples;
  for (unsigned int i = 0; i < attributes.size(); i++)
  {
    new_schema.push_back(schema[attributes[i]]);//add each schema index to new schema
  }
  for (set <Tuple>::iterator it = tuples.begin(); it != tuples.end(); it++)
  {//add new values at index of current tuples
    Tuple temp;
    for (unsigned int i = 0; i < attributes.size(); i++)
    {
      temp.push_back((*it)[attributes[i]]);//retrieve index of each tuple list
    }
    new_tuples.insert(temp);//insert new tuple lists
  }

  Relation output(name, new_schema, new_tuples);
  return output;
}


Relation Relation::renameR(Schema scheme)
{
  Schema new_schema = scheme;//change names of schema
  Relation output(name, new_schema, tuples);
  return output;
}


Relation Relation::naturalJoin(Relation relat)//probably want to pass by reference
{
  Schema joinedSchema;
  Schema relatSchema = relat.getSchema();
  set <string> schemaSet;
  vector <int> tup_its;//this will store iterators to unique tuple values from r2 based on unique schema
  for (unsigned int i = 0; i < schema.size(); i++) //this will put all r1 schema into set to search uniqueness
  {
    schemaSet.insert(schema[i]);
    joinedSchema.push_back(schema[i]);//ccreate final schema for joined relation first with r1 schema
  }
  for (unsigned int i = 0; i < relatSchema.size(); i++)//this will add unique elements of r2
  {
    if (!schemaSet.count(relatSchema[i]))//if unique scheme that's not already in joinedSchema
    {
      joinedSchema.push_back(relatSchema[i]);//then add to joinedSchema
      tup_its.push_back(i);//and store iterator to unique tuple value for joining later
    }
  }
  /*
  for (set <string>::iterator it = schemaSet.begin(); it != schemaSet.end(); it++)
  {
    joinedSchema.push_back(schemaSet[it]);//create final schema for joined relation with all unique schema fom both relations
  }
  */
  Relation result(joinedSchema);//creates output with new schema

  set <Tuple> relatTuples = relat.getTuples();
  for (set <Tuple>::iterator i = tuples.begin(); i != tuples.end(); i++) //first relation tuples
  {
    for (set <Tuple>::iterator j = relatTuples.begin(); j != relatTuples.end(); j++)//second relation tuples
    {
      if (isjoinable(schema, *i, relatSchema, *j)) //if tuples form r1 can be joined with r2
      {
        Tuple joined_tup = *i;//first part of new tuple
        Tuple tup_temp = *j;
        for (unsigned int k = 0; k < tup_its.size(); k++)//move through each unique tuple value in relatTuples
        {
          joined_tup.push_back(tup_temp[tup_its[k]]);//add unique tup values from r2 to new tuple
        }
        result.addTuple(joined_tup);//add joined tuple to joined relation
      }
    }
  }

  return result;//REMEMBER this must be given a name after the joining is done.
}


bool Relation::unionize(Relation relat) //if pass by reference, relat will change
{
  //if (schema == relat.getSchema()) //FOR OPTIMIZATION probably can do without this
  //{
    bool output = false;
    set <Tuple> relatTuples = relat.getTuples();//ALSO could make things like this public?
    for (set <Tuple>::iterator it = relatTuples.begin(); it != relatTuples.end(); it++)
    {
      if (tuples.insert(*it).second)//puts all tuples from both relations into the one calling union
      {//HOPEFULLY still inserts
        output = true;
        //cout << "FOR ISENGUARD!!!" << endl;
      }
    }
    //if(output)
    //  cout << "the hobbits died :(" << endl;
    return output;
  //}//if not same schema, does nothing
}


string Relation::toString()
{
  stringstream output;
  if (!tuples.empty())//if tuples empty, then it was invalid operation
  {
    output << "Yes(" << tuples.size() << ")\n";
    if (!schema.empty())//only print if there are schema to be projected
    {
      for (set <Tuple>::iterator it = tuples.begin(); it != tuples.end(); it++)
      {
        output << "  " << schema[0] << "=" << (*it)[0];//first pair indented
        for (unsigned int i = 1; i < schema.size(); i++) //i=1 because all pairs except first need comma in front
        {
          output << ", " << schema[i] << "=" << (*it)[i];
        }
        output << endl;
      }
    }
  }
  else
  {
    output << "No\n";
  }
  return output.str();
}
