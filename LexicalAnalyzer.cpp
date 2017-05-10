#include "LexicalAnalyzer.h"


LexicalAnalyzer::LexicalAnalyzer(char* input_file)
{
	ifstream file_to_read(input_file);
	if (file_to_read.is_open())
	{
		if (file_to_read.peek() == EOF)
		{
			this->input_file.push_back(' '); //will just produce EOF token with this WhiteSpace
		}
		else
		{
			while (file_to_read.peek() != EOF)
			{
				this->input_file.push_back(file_to_read.get()); //reads the file into the data member
			}
			file_to_read.close();
		}
	}
	else
	{
		cout << "unable to read file";
	}
}


LexicalAnalyzer::~LexicalAnalyzer()
{
}

vector <char> LexicalAnalyzer::getInputFile()
{
	return input_file;
}

void LexicalAnalyzer::analyze(char* input_file)
{
	ifstream file_to_read(input_file);
	if (file_to_read.is_open())
	{
		if (file_to_read.peek() == EOF)
		{
			this->input_file.push_back(' '); //will just produce EOF token with this WhiteSpace
		}
		else
		{
			while (file_to_read.peek() != EOF)
			{
				this->input_file.push_back(file_to_read.get()); //reads the file into the data member
			}
			file_to_read.close();
		}
	}
	else
	{
		cout << "unable to read file";
	}
}

char LexicalAnalyzer::getChar(int it)
{
	return input_file[it]; //returns character at given iteration.
}

vector <Token> LexicalAnalyzer::scan()
{
	//the following vectors order automata by precidence
	vector <Automaton*> automata;
	vector <Token> tokens;
	unsigned int current_iteration = 0; //this is first iteration for iterating through file. Can increment after tokens made
	unsigned int current_line = 1; //current line in file starts at 1

	automata.push_back(new Comma());
	automata.push_back(new Period());
	automata.push_back(new QMark());
	automata.push_back(new LeftParen());
	automata.push_back(new RightParen());
	automata.push_back(new Colon());
	automata.push_back(new ColonDash());
	automata.push_back(new Multiply());
	automata.push_back(new Add());
	automata.push_back(new Schemes());
	automata.push_back(new Facts());
	automata.push_back(new Rules());
	automata.push_back(new Queries());
	automata.push_back(new ID());
	automata.push_back(new MyString());
	automata.push_back(new LineComment());
	automata.push_back(new BlockComment());
	automata.push_back(new MyUndefined());
	automata.push_back(new WhiteSpace());

	while (current_iteration < input_file.size()) //for some reason need -1 this loop iterates through file
	{
		int max_readings = 0;
		int new_max_readings = 0;
		int it_of_max_readings = -1; //current iteration of max readings. initialized to -1 in case none read.
		if (input_file[current_iteration] == '\n')
		{
			current_line++;
			current_iteration++;
		}
		else
		{
			for (unsigned int i = 0; i < automata.size(); i++)//this loop lets each automata read from current iteration
			{
				automata[i]->read(current_iteration, input_file);
				//finds which automata has most readings and highest precidence.
				new_max_readings = max(max_readings, automata[i]->getReadings());
				/*this will change it_of_max_readings to match the automata with max readings while keeping
				precidence by only changing if it exceeds the previous max.*/
				if (new_max_readings > max_readings)
				{
					it_of_max_readings = i;
					max_readings = new_max_readings;
				}

			}
			if (it_of_max_readings != automata.size()-1) //because this would be a white space
			{
				tokens.push_back(automata[it_of_max_readings]->tokenize(current_line, current_iteration, input_file));
				//this will set readings back to 0 for each automata before it moves forward in file
				for (unsigned int i = 0; i < automata.size(); i++)
				{
					automata[i]->resetReadings(); //just clears all because sometimes more than one reads
				}
				current_iteration += max_readings; //move iteration to point beyond end of last token made
			}
			else
			{
				//this will set readings back to 0 for each automata before it moves forward in file
				automata[it_of_max_readings]->resetReadings(); //only Whitespace reads white space
				current_iteration += max_readings; //this way it just skips over white space and doesn't make a token
			}
		}
	}
	string name_EOF = "EOF";
	string content_EOF = "";
	Token token_EOF(name_EOF, content_EOF, current_line);
	tokens.push_back(token_EOF);
	/*
	stringstream token_list;
	for (unsigned int i = 0; i < tokens.size(); i++) //getting tokens to print out
	{
		token_list << tokens[i].getToken() << endl;
	}
	int total_tokens = tokens.size();
	token_list << "Total Tokens = " << total_tokens << endl;
	*/
	return tokens;
}
