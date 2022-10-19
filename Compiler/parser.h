#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
//for future assignments leave it as it is
class parser
{
    lexer _lexer;
	ofstream fout_symbol_table;
public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
	void parserMain();
	void function();
	void functionprime();
	void ID();
	void FPARAM();
	void FPARAMPRIME();
	void VAR();
	void CODE();
	void DISPLAY();
	void DISPLAYLINE();
	void IF();
	void ASSIGN();
	void DOUNTIL();
	void RETURN();
	void READ();
	void EXECUTE();
	void INIT();
	void X();
	void EXP();
	void PST();
	void CONDITION();
	void NEXT();
	void RO();
	void T();
	void R();
	void F();
	void RPRIME();
	void ELSEIF();
	void ELSE();
	void CPARAMS();
	void CPARAMSPRIME();
	void CPARAMSDOUBLEPRIME();
	void addToSymbolTable(string type,string symbol);


    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
	//all your parser function goes here
};
#endif
