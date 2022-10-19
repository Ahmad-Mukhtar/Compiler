#include "lexer.h"
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
	"FUNCTION",
	"INT",
	"IF",
	"ELSE",
	"DO",
	"UNTIL",
	"THEN",
	"READ",
	"DISPLAY",
	"DISPLAYLINE",
	"RETURN",
	"RELATION_OP",
	"COMMA",
	"COLON",
	"SEMI_COLON",
	"DOLLAR",
	"OPEN_PARANTHESIS",
	"CLOSE_PARANTHESIS",
	"ADD_OP",
	"SUBTRACT_OP",
	"MULTIPLY_OP",
	"DIVIDE_OP",
	"MOD_OP",
	"ID",
	"NUMBER",
	"STRING",
	"COMMENT_START",
	"COMMENT_END",
	"ASSIGN",
	"BLOCK_START",
	"BLOCK_END",
	"CHARACTER",
	"VARIABLE"
	};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}
void lexer::Tokenize()//function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();

	for (it = stream.begin(); it != stream.end(); it++)
	{
		// Comma
		if (*it == ',')
		{
			tokens.push_back(token(string(""), TokenType::COMMA));
		}
		// Colon
		else if (*it == ':')
		{
			tokens.push_back(token(string(""), TokenType::COLON));
		}
		// Semi Colon
		else if (*it == ';')
		{
			tokens.push_back(token(string(""), TokenType::SEMI_COLON));
		}

		//Dollar Or Variable
		else if (*it == '$')
		{
			tokens.push_back(token(string(""), TokenType::DOLLAR));
			string temp = "";
			it++;
			if (*(it)==95) {
				it++;
				while (it != stream.end() && ((*(it) >= 65 && *(it) <= 90) || (*(it) >= 97 && *(it) <= 122)))
				{
					temp.push_back(*it);
					it++;
				}
				if (*it == 95)
				{
					cout << "Invalid Token";
					exit(0);
				}
			}
			else {
				while (it != stream.end() && ((*(it) >= 65 && *(it) <= 90) || (*(it) >= 97 && *(it) <= 122)))
				{
					temp.push_back(*it);
					it++;
				}
			}

			tokens.push_back(token(string(temp), TokenType::VARIABLE));
			it--;
			
		}
		else if (*it == '<')
		{
			if (*(it + 1) == '-')
			{
				tokens.push_back(token(string(""), TokenType::FUNCTION_POINTER));
			}
			else
			{
				cout << "error";
				tokens.push_back(token(string(""), TokenType::ERROR));
				exit(0);
			}
		}
		//Open parnthesis
		else if (*it == '(')
		{
			tokens.push_back(token(string(""), TokenType::OPEN_PARANTHESIS));
		}

		//close paranthesis
		else if (*it == ')')
		{
			tokens.push_back(token(string(""), TokenType::CLOSE_PARANTHESIS));
		}

		// Add Op
		else if (*it == '+')
		{
			tokens.push_back(token(string(""), TokenType::ADD_OP));
		}
		// Subtract Op Or Relational Operators
		else if (*it == '-')
		{
			// Equal to
			if (*(it + 1) == 'e' && *(it + 2) == 'q')
			{
				tokens.push_back(token(string("-eq"), TokenType::RELATION_OP));
				it++;
				it++;
			}

			//not equal to
			else if (*(it + 1) == 'n' && *(it + 2) == 'e')
			{
				tokens.push_back(token(string("-ne"), TokenType::RELATION_OP));
				it++;
				it++;
			}

			//Less Than
			else if (*(it + 1) == 'l' && *(it + 2) == 't')
			{
				tokens.push_back(token(string("-lt"), TokenType::RELATION_OP));
				it++;
				it++;
			}

			//less tha equal to
			else if (*(it + 1) == 'l' && *(it + 2) == 'e')
			{
				tokens.push_back(token(string("-le"), TokenType::RELATION_OP));
				it++;
				it++;
			}
			//greater than
			else if (*(it + 1) == 'g' && *(it + 2) == 't')
			{
				tokens.push_back(token(string("-gt"), TokenType::RELATION_OP));
				it++;
				it++;
			}

			//greater than equal to
			else if (*(it + 1) == 'g' && *(it + 2) == 'e')
			{
				tokens.push_back(token(string("-ge"), TokenType::RELATION_OP));
				it++;
				it++;
			}
			else if (*(it-1)!='<')
			{

				tokens.push_back(token(string(""), TokenType::SUBTRACT_OP));
			}
		}

		 //assignment op
		else if(*it=='=')
		{
			tokens.push_back(token(string(""), TokenType::ASSIGN));
		}
		// Multiply Op
		else if (*it == '*')
		{
			tokens.push_back(token(string(""), TokenType::MULTIPLY_OP));
		}
		// Divide Op
		else if (*it == '/')
		{
			tokens.push_back(token(string(""), TokenType::DIVIDE_OP));
		}
		// Mod Op
		else if (*it == '%')
		{
			tokens.push_back(token(string(""), TokenType::MOD_OP));
		}
		
		//Open and close Block

		else if (*it == '{')
		{
		tokens.push_back(token(string(""), TokenType::BLOCK_START));
		}
		else if (*it == '}')
		{
		tokens.push_back(token(string(""), TokenType::BLOCK_END));
		}
		// String
		else if (*it == '"')
		{
		string temp = "";
		temp.push_back(*it);
		it++;
		while (it != stream.end() && *it != '"')
		{
			temp.push_back(*it);
			it++;
		}
		temp.push_back('"');
		tokens.push_back(token(string(temp), TokenType::STRING));
		}
		// string Literal
		else if (*it == '\'')
		{
		string temp = "";
		temp.push_back(*it);
		it++;
		while (it != stream.end() && *it != '\'')
		{
			temp.push_back(*it);
			it++;
		}
		temp.push_back(*it);
		tokens.push_back(token(string(temp), TokenType::STRING));
		}
		// Comments
		else if (*it == '#')
		{
			it++;
			if (*it == '~')
			{
				
				//tokens.push_back(token(string(""), TokenType::COMMENT_START));
				while (it != stream.end())
				{
					if (*it == '~' && *(it + 1) == '#')
					{
						//tokens.push_back(token(string(""), TokenType::COMMENT_END));
						it++;
						break;
					}
					it++;
				}
			}
			else
			{
				it--;
				tokens.push_back(token(string(""), TokenType::ERROR));
			}
		}

		// keywords and identifiers
		else if ((*(it) >= 65 && *(it) <= 90) || (*(it) >= 97 && *(it) <= 122)|| (*(it) == 95))
		{
			string temp = "";
			temp.push_back(*it);
			it++;
			while (it != stream.end() && ((*(it) >= 65 && *(it) <= 90) || (*(it) >= 97 && *(it) <= 122) || (*(it) >= 48 && *(it) <= 57)))
			{
				temp.push_back(*it);
				it++;
			}

			if (*(it) == '_')
			{
				cout << "error";
				exit(0);
			}
			it--;

			if (temp == "if")
			{
				tokens.push_back(token("", TokenType::IF));
			}
			else if (temp == "else")
			{
				tokens.push_back(token("", TokenType::ELSE));
			}
			else if (temp == "function")
			{
				tokens.push_back(token("", TokenType::FUNCTION));
			}
			else if (temp == "do")
			{
				tokens.push_back(token("", TokenType::DO));
			}
			else if (temp == "until")
			{
				tokens.push_back(token("", TokenType::UNTIL));
			}
			else if (temp == "int")
			{
				tokens.push_back(token("", TokenType::INT));
			}
			else if (temp == "then")
			{
				tokens.push_back(token("", TokenType::THEN));
			}
			else if (temp == "read")
			{
				tokens.push_back(token("", TokenType::READ));
			}
			else if (temp == "return")
			{
				tokens.push_back(token("", TokenType::RETURN));
			}
			else if (temp == "display")
			{
				tokens.push_back(token("", TokenType::DISPLAY));
			}
			else if (temp == "displayline")
			{
				tokens.push_back(token("", TokenType::DISPLAYLINE));
			}
			else if(temp=="execute")
			{
				tokens.push_back(token(string(temp), TokenType::EXECUTE));
			}
			else if (temp == "_" && *(it + 1) == '_')
			{
				cout << "error";
				exit(0);
			}
			else
			{
				tokens.push_back(token(string(temp), TokenType::ID));
			}
		}
		// Number
		else if ((*(it) >= 48 && *(it) <= 57))
		{
		string temp = "";
		temp.push_back(*it);
		it++;
		while (it != stream.end() && (*(it) >= 48 && *(it) <= 57))
		{
			temp.push_back(*it);
			it++;
		}
		it--;
		tokens.push_back(token(string(temp), TokenType::NUMBER));
		}

		else if(!isspace(*(it)))
		{
		cout << "error";
		exit(0);
		}

	}

	//push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' ');//dummy spaces appended at the end
        stream.push_back(' ');
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}