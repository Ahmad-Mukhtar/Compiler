#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum class TokenType
{
	END_OF_FILE=0,
	FUNCTION=1,
	INT=2,
	IF=3,
	ELSE=4,
	DO=5,
	UNTIL=6,
	THEN=7,
	READ=8,
	DISPLAY=9,
	DISPLAYLINE=10,
	RETURN=11,
	RELATION_OP=12,
	COMMA=13,
	COLON=14,
	SEMI_COLON=15,
	DOLLAR=16,
	OPEN_PARANTHESIS=17,
	CLOSE_PARANTHESIS=18,
	ADD_OP=19,
	SUBTRACT_OP=20,
	MULTIPLY_OP=21,
	DIVIDE_OP=22,
	MOD_OP=23,
	ID=24,
	NUMBER=25,
	STRING=26,
	COMMENT_START=27,
	COMMENT_END=28,
	ASSIGN=29,
	BLOCK_START=30,
	BLOCK_END=31,
	EXECUTE = 32,
	VARIABLE=33,
	FUNCTION_POINTER=34,
	ERROR
};
//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  //used for storing file sample_code.ol content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();//populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();//just print everything as it is present in file
	token getNextToken();//get next token
	void resetPointer();//reset pointer to start getting tokens from start
	int getCurrentPointer();//get where current pointer in tokens vector is
	void setCurrentPointer(int pos);//move current pointer to wherever
	token peek(int);//peek the next token
};

#endif // !_LEXER_H
