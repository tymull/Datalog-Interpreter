#include "Parser.h"


Parser::Parser(vector <Token> tokens)
{
	this->tokens = tokens;
}


Parser::~Parser()
{
}


int Parser::getIt()
{
	return it;
}


vector <Token> Parser::getTokens()
{
	return tokens;
}


DatalogProgram Parser::getDatalogProgram()
{
	return dp;
}


void Parser::ignoreComments() //this should be called every time it is incremented
{
	while (tokens[it].getName() == "COMMENT")
	//will ensure that "COMMENT" is effectively ignored and not compared to other token
	{
		it++;
	}
}


void Parser::match(string item)
{
	if (tokens[it].getName() != item)
	{
		throw tokens[it]; //bad input throw to output the token
	}
	else
	{
		it++; //input is good so far, move to next token
		ignoreComments();
	}
}


void Parser::datalogProgram()
{
	ignoreComments();
	match("SCHEMES"); //input must start with token name SCHEMES
	match("COLON");//COLON should follow SCHEMES

	scheme(); //recurse to a different part of grammar
	schemeList(); //since it is passed by reference, it will continue to increment through the vector through recursions

	match("FACTS");
	match("COLON");

	factList();

	match("RULES");
	match("COLON");

	ruleList();

	match("QUERIES");
	match("COLON");

	query();
	queryList();
}


void Parser::scheme()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		pred.setName(tokens[it].getContent()); //sets scheme name
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		param.setType(tokens[it].getName());//sets param type
		param.setValue(tokens[it].getContent());//sets param value
		pred.addParameter(param); //pushes param onto vector
		it++;
		ignoreComments();
	}

	idList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		dp.addScheme(pred); //pushes pred onto scheme vector
		pred.clearParams(); //get ready for next predicate
		it++;
		ignoreComments();
	}
}


void Parser::schemeList()
{
	if (tokens[it].getName() == "ID")
	{
		scheme();
		schemeList();
	}
	else if (tokens[it].getName() != "FACTS") //if next token is FACTS, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::idList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();

		if (tokens[it].getName() != "ID")
		{
			throw tokens[it];
		}
		else
		{
			param.setType(tokens[it].getName());//sets param type
			param.setValue(tokens[it].getContent());//sets param value
			pred.addParameter(param); //pushes param onto vector
			it++;
			ignoreComments();
			idList();
		}
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::fact()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		pred.setName(tokens[it].getContent());//sets fact name
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "STRING")
	{
		throw tokens[it];
	}
	else
	{
		param.setType(tokens[it].getName());//sets param type
		param.setValue(tokens[it].getContent());//sets param value
		pred.addParameter(param); //pushes param onto vector
		it++;
		ignoreComments();
	}
	stringList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "PERIOD")
	{
		throw tokens[it];
	}
	else
	{
		dp.addFact(pred);//pushes pred onto facts vector
		pred.clearParams();//get ready for next predicate
		it++;
		ignoreComments();
	}
}


void Parser::factList()
{
	if (tokens[it].getName() == "ID")
	{
		fact();
		factList();
	}
	else if (tokens[it].getName() != "RULES") //if next token is RULES, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::rule()
{
	headPredicate();

	if (tokens[it].getName() != "COLON_DASH")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}

	predicate();
	my_rule.addPredicate(pred);//adds predicate to vector in my_rule
	pred.clearParams();//get ready for next predicate
	predicateList();

	if (tokens[it].getName() != "PERIOD")
	{
		throw tokens[it];
	}
	else
	{
		dp.addRule(my_rule);//adds my_rule to vector
		my_rule.clearPredicates();//get ready for next my_rule
		it++;
		ignoreComments();
	}
}


void Parser::ruleList()
{
	if (tokens[it].getName() == "ID")
	{
		rule();
		ruleList();
	}
	else if (tokens[it].getName() != "QUERIES") //if next token is QUERIES, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::headPredicate()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		pred.setName(tokens[it].getContent());//sets headPred name
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		param.setType(tokens[it].getName());//sets param type
		param.setValue(tokens[it].getContent());//sets param value
		pred.addParameter(param); //pushes param onto vector
		it++;
		ignoreComments();
	}
	idList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		my_rule.setHeadPred(pred);//sets pred as headPred for my_rule
		pred.clearParams();//get ready for next predicate
		it++;
		ignoreComments();
	}
}


void Parser::predicate()
{
	if (tokens[it].getName() != "ID")
	{
		throw tokens[it];
	}
	else
	{
		pred.setName(tokens[it].getContent());//sets predicate name
		it++;
		ignoreComments();
	}
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}

	parameter();
	//need to use sstream because may have nested expressions
	param.setValue(param_stream.str());//sets param value to stream
	param_stream.str("");//clears sstream to be usable again
	pred.addParameter(param); //pushes param onto vector
	parameterList();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}
}


void Parser::predicateList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();
		predicate();
		my_rule.addPredicate(pred);//adds predicate to vector in my_rule
		pred.clearParams();//get ready for next predicate
		predicateList();
	}
	else if (tokens[it].getName() != "PERIOD") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::parameter()
{
	if (tokens[it].getName() == "ID")
	{
		param.setType(tokens[it].getName());//sets param type
		param_stream << tokens[it].getContent();//puts value onto stream
		it++;
		ignoreComments();
	}
	else if (tokens[it].getName() == "LEFT_PAREN")//NEED TO FIGURE THIS OUT!
	{
		//will set param type after Right_Paren in expression() call.
		param_stream << tokens[it].getContent();//puts value onto stream
		expression();
	}
	else if (tokens[it].getName() == "STRING")
	{
		param.setType(tokens[it].getName());//sets param type
		param_stream << tokens[it].getContent();//puts value onto stream
		it++;
		ignoreComments();
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::parameterList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();
		parameter();
		//need to use sstream because may have nested expressions
		param.setValue(param_stream.str());//sets param value to stream
		param_stream.str("");//clears sstream to be usable again
		pred.addParameter(param); //pushes param onto vector
		parameterList();
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::expression()
{
	if (tokens[it].getName() != "LEFT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		it++;
		ignoreComments();
	}

	parameter();
	myOperator();
	parameter();

	if (tokens[it].getName() != "RIGHT_PAREN")
	{
		throw tokens[it];
	}
	else
	{
		param.setType("expression");//sets param type
		param_stream << tokens[it].getContent();//puts value onto stream
		it++;
		ignoreComments();
	}
}


void Parser::myOperator()
{
	if (tokens[it].getName() == "ADD")
	{
		param_stream << tokens[it].getContent();//puts value onto stream
		it++;
		ignoreComments();
	}
	else if (tokens[it].getName() == "MULTIPLY")
	{
		param_stream << tokens[it].getContent();//puts value onto stream
		it++;
		ignoreComments();
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::query()
{
	if (tokens[it].getName() == "ID")
	{
		predicate();
		dp.addQuery(pred);//adds query to vector
		pred.clearParams();//get ready for next predicate
	}
	else
	{
		throw tokens[it];
	}
	if (tokens[it].getName() == "Q_MARK")
	{
		it++;
		ignoreComments();
	}
	else
	{
		throw tokens[it];
	}
}


void Parser::queryList()
{
	if (tokens[it].getName() == "ID")
	{
		query();
		queryList();
	}
	else if (tokens[it].getName() != "EOF") //if next token is EOF, move on and finish. Otherwise throw
	{
		throw tokens[it];
	}
}


void Parser::stringList()
{
	if (tokens[it].getName() == "COMMA")
	{
		it++;
		ignoreComments();

		if (tokens[it].getName() == "STRING")
		{
			param.setType(tokens[it].getName());//sets param type
			param.setValue(tokens[it].getContent());//sets param value
			pred.addParameter(param); //pushes param onto vector
			it++;
			ignoreComments();
			stringList();
		}
		else
		{
			throw tokens[it];
		}
	}
	else if (tokens[it].getName() != "RIGHT_PAREN") //if next token is RIGHT_PAREN, move on. Otherwise throw
	{
		throw tokens[it];
	}
}


DatalogProgram Parser::validate()
{
	try
	{
		datalogProgram(); //this will run through each production in grammar to validate
	}
	catch (Token t)
	{
		//stringstream output;
		//output << "Failure!\n  " << t.getToken(); //two spaces instead of \t
		return dp;//output.str();
	}
	dp.setDomain();//sets domain and gets ready to print output
	return dp;//.toString();//"Success!";
}
