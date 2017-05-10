
#include <iostream>
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "Relation.h"
#include "Database.h"

using namespace std;

int main(int argc, char* argv[])
{

	LexicalAnalyzer lexi(argv[1]);
	Parser datalog_parser(lexi.scan());

	Database db(datalog_parser.validate());//initialize Database
	db.evalRules();
	cout << db.evalQueries();

	return 0;
}
