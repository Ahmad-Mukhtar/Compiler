#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
	fout_symbol_table.open("symbol_table.txt");
}
void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}


void parser::parserMain() 
{
	function();
	functionprime();
}

void parser::function()
{
	ID();
	expect(TokenType::COLON);
	expect(TokenType::INT);
	expect(TokenType::FUNCTION_POINTER);
	expect(TokenType::FUNCTION);
	expect(TokenType::OPEN_PARANTHESIS);
	FPARAM();
	expect(TokenType::CLOSE_PARANTHESIS);
	expect(TokenType::BLOCK_START);
	CODE();
	expect(TokenType::BLOCK_END);



}

void parser::functionprime()
{
	if (_lexer.peek(1).tokenType == TokenType::ID)
	{
		function();
		functionprime();
	}
	else
	{
		//do nothing
	}

}

void parser::ID()
{
	token t=expect(TokenType::ID);
	//addToSymbolTable(t.lexeme, "IDENTIFIER");
}

void parser::FPARAM()
{
	if (_lexer.peek(2).tokenType == TokenType::VARIABLE)
	{
		FPARAMPRIME();

		if (_lexer.peek(1).tokenType == TokenType::COMMA)
		{
			expect(TokenType::COMMA);
			FPARAMPRIME();
			FPARAM();
		}
		
		else
		{
			//FPARAMPRIME();
		}
	}

	else if (_lexer.peek(1).tokenType == TokenType::COMMA)
	{
		expect(TokenType::COMMA);
		FPARAMPRIME();
		FPARAM();
	}

	else
	{
		//Do nothing
	}
}

void parser::FPARAMPRIME()
{
	expect(TokenType::DOLLAR);
	token t = expect(TokenType::VARIABLE);
	expect(TokenType::COLON);
	expect(TokenType::INT);
	addToSymbolTable(t.lexeme, "VARIABLE");
}

void parser::VAR()
{
	expect(TokenType::DOLLAR);
	expect(TokenType::VARIABLE);
	
	//ID();
}

void parser::CODE()
{

	if (_lexer.peek(1).tokenType == TokenType::DOLLAR && _lexer.peek(2).tokenType == TokenType::VARIABLE && _lexer.peek(3).tokenType == TokenType::COLON)
	{
		INIT();
		CODE();
	}


	else if (_lexer.peek(1).tokenType == TokenType::DISPLAY)
	{
		DISPLAY();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::DISPLAYLINE)
	{
		DISPLAYLINE();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::IF)
	{
		IF();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::DOLLAR && _lexer.peek(2).tokenType == TokenType::VARIABLE&&_lexer.peek(3).tokenType == TokenType::ASSIGN)
	{
		ASSIGN();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::DO)
	{
		DOUNTIL();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::RETURN)
	{
		RETURN();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::STRING&& _lexer.peek(2).tokenType == TokenType::COLON&&_lexer.peek(3).tokenType == TokenType::READ)
	{
		READ();
		CODE();
	}

	else if (_lexer.peek(1).tokenType == TokenType::EXECUTE)
	{
		EXECUTE();
		expect(TokenType::SEMI_COLON);
		CODE();
	}

	else
	{

	}
	

}

void parser::INIT()
{
	expect(TokenType::DOLLAR);
	token t=expect(TokenType::VARIABLE);
	expect(TokenType::COLON);
	expect(TokenType::INT);
	X();
	expect(TokenType::SEMI_COLON);
	addToSymbolTable(t.lexeme, "VARIABLE");
}

void parser::X()
{
	if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
	{
		expect(TokenType::ASSIGN);
		if (_lexer.peek(2).tokenType == TokenType::VARIABLE || _lexer.peek(1).tokenType == TokenType::NUMBER || _lexer.peek(1).tokenType == TokenType::OPEN_PARANTHESIS)
		{
			EXP();
		}

		else if(_lexer.peek(1).tokenType==TokenType::EXECUTE)
		{
			EXECUTE();
		}
	}

	else
	{
		//do nothing
	}


}

void parser::DISPLAY()
{
	expect(TokenType::DISPLAY);
	expect(TokenType::COLON);
	PST();
	expect(TokenType::SEMI_COLON);
}

void parser::DISPLAYLINE()
{
	expect(TokenType::DISPLAYLINE);
	expect(TokenType::COLON);
	PST();
	expect(TokenType::SEMI_COLON);
}

void parser::PST()
{
	if (_lexer.peek(1).tokenType == TokenType::STRING)
	{
		expect(TokenType::STRING);
		if(_lexer.peek(1).tokenType == TokenType::COMMA)
		{
			expect(TokenType::COMMA);
			PST();
		}
	}

	else if (_lexer.peek(2).tokenType == TokenType::VARIABLE|| _lexer.peek(1).tokenType == TokenType::NUMBER|| _lexer.peek(1).tokenType == TokenType::OPEN_PARANTHESIS)
	{
		EXP();
		if (_lexer.peek(1).tokenType == TokenType::COMMA)
		{
			expect(TokenType::COMMA);
			PST();
		}
	}
	
}

void parser::IF()
{
	expect(TokenType::IF);
	expect(TokenType::OPEN_PARANTHESIS);
	CONDITION();
	expect(TokenType::CLOSE_PARANTHESIS);
	expect(TokenType::THEN);
	expect(TokenType::BLOCK_START);
	CODE();
	expect(TokenType::BLOCK_END);
	NEXT();

}

void parser::CONDITION()
{
	EXP();
	RO();
	EXP();
}

void parser::NEXT()
{
	if (_lexer.peek(1).tokenType == TokenType::ELSE&&_lexer.peek(2).tokenType == TokenType::IF)
	{
		ELSEIF();
	}

	else if(_lexer.peek(1).tokenType == TokenType::ELSE)
	{
		ELSE();
	}
	
	else
	{

	}
}

void parser::ELSEIF()
{
	expect(TokenType::ELSE);
	expect(TokenType::IF);
	expect(TokenType::OPEN_PARANTHESIS);
	CONDITION();
	expect(TokenType::CLOSE_PARANTHESIS);
	expect(TokenType::THEN);
	expect(TokenType::BLOCK_START);
	CODE();
	expect(TokenType::BLOCK_END);
	NEXT();

}

void parser::ELSE()
{
	if (_lexer.peek(1).tokenType == TokenType::ELSE)
	{
		expect(TokenType::ELSE);
		expect(TokenType::BLOCK_START);
		CODE();
		expect(TokenType::BLOCK_END);
	}
	else
	{
		//do nothing
	}

}

void parser::EXP()
{
	T();
	R();
}

void parser::T()
{
	F();
	RPRIME();
}

void parser::R()
{
	if (_lexer.peek(1).tokenType == TokenType::ADD_OP)
	{
		expect(TokenType::ADD_OP);
		T();
		R();
	}
	else if (_lexer.peek(1).tokenType == TokenType::SUBTRACT_OP)
	{
		expect(TokenType::SUBTRACT_OP);
		T();
		R();
	}
	else
	{
	}
}

void parser::F()
{
	if (_lexer.peek(2).tokenType == TokenType::VARIABLE)
	{
		VAR();
	}
	else if (_lexer.peek(1).tokenType == TokenType::NUMBER)
	{
		expect(TokenType::NUMBER);
	}
	else if(_lexer.peek(1).tokenType == TokenType::OPEN_PARANTHESIS)
	{
		expect(TokenType::OPEN_PARANTHESIS);
		EXP();
		expect(TokenType::CLOSE_PARANTHESIS);

	}
}

void parser::RPRIME()
{
	if (_lexer.peek(1).tokenType == TokenType::MULTIPLY_OP)
	{
		expect(TokenType::MULTIPLY_OP);
		F();
	}
	else if (_lexer.peek(1).tokenType == TokenType::DIVIDE_OP)
	{
		expect(TokenType::DIVIDE_OP);
		F();
	}
	else if (_lexer.peek(1).tokenType == TokenType::MOD_OP)
	{
		expect(TokenType::DIVIDE_OP);
		F();
	}
	else
	{
	}
}

void parser::RO()
{
	if (_lexer.peek(1).lexeme == "-eq" || _lexer.peek(1).lexeme == "-ne" || _lexer.peek(1).lexeme == "-le" || _lexer.peek(1).lexeme == "-lt" || _lexer.peek(1).lexeme == "-gt" || _lexer.peek(1).lexeme == "-ge")
	{
		expect(TokenType::RELATION_OP);
	}

	else
	{
		cout << "Bad Token..." << endl;
		exit(0);
	}
}

void parser::EXECUTE()
{
	expect(TokenType::EXECUTE);
	expect(TokenType::COLON);
	ID();
	expect(TokenType::OPEN_PARANTHESIS);
	CPARAMS();
	expect(TokenType::CLOSE_PARANTHESIS);
}

void parser::CPARAMS()
{
	if (_lexer.peek(2).tokenType == TokenType::VARIABLE)
	{
		CPARAMSPRIME();
	}

	else
	{

	}
}

void parser::CPARAMSPRIME()
{
	if (_lexer.peek(2).tokenType == TokenType::VARIABLE)
	{
		CPARAMSDOUBLEPRIME();
		if (_lexer.peek(1).tokenType == TokenType::COMMA)
		{
			expect(TokenType::COMMA);
			CPARAMSDOUBLEPRIME();
			CPARAMSPRIME();
		}

		else
		{

		}
	}

	else if(_lexer.peek(1).tokenType == TokenType::COMMA)
	{
		expect(TokenType::COMMA);
		CPARAMSDOUBLEPRIME();
		CPARAMSPRIME();
	}

	else
	{
		//do nothing
	}

}

void parser::CPARAMSDOUBLEPRIME()
{
	VAR();
}

void parser::DOUNTIL()
{
	expect(TokenType::DO);
	expect(TokenType::UNTIL);
	expect(TokenType::OPEN_PARANTHESIS);
	CONDITION();
	expect(TokenType::CLOSE_PARANTHESIS);
	expect(TokenType::BLOCK_START);
	CODE();
	expect(TokenType::BLOCK_END);
}

void parser::RETURN()
{
	expect(TokenType::RETURN);
	expect(TokenType::COLON);
	EXP();
	expect(TokenType::SEMI_COLON);
}

void parser::READ()
{
	expect(TokenType::STRING);
	expect(TokenType::COLON);
	expect(TokenType::READ);
	expect(TokenType::COLON);
	VAR();
	expect(TokenType::SEMI_COLON);
}

void parser::ASSIGN()
{
	VAR();
	expect(TokenType::ASSIGN);
	if (_lexer.peek(1).tokenType == TokenType::EXECUTE)
	{
		EXECUTE();
	}
	else
	{
		EXP();
	}
	expect(TokenType::SEMI_COLON);
}

void parser::addToSymbolTable(string type, string symbol) 
{
	fout_symbol_table << "{'" << type << "', '" << symbol << "'}" << endl;
}

//this function is for sample purposes only
/*
bool parser::statements()
{
    //statements-- > COLON LPAREN start RPAREN
    if (_lexer.peek(1).tokenType == TokenType::COLON)
    {
        expect(TokenType::COLON);
        if (_lexer.peek(1).tokenType == TokenType::LPAREN)
        {
            expect(TokenType::LPAREN);
            start();
            if (_lexer.peek(1).tokenType == TokenType::RPAREN)
            {
                expect(TokenType::RPAREN);
                return true;
            }
        }
    }
    return false;
}*/ 