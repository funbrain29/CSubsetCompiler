#include "Parser.h"

ParserClass::ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable) {
    mScanner = Scanner;
    mSymbolTable = SymbolTable;
}


TokenClass ParserClass::Match(TokenType expectedType) {
	TokenClass currentToken = mScanner->GetNextToken();
	if(currentToken.GetTokenType() != expectedType)
	{
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Expected token type " <<
			TokenClass:: GetTokenTypeName(expectedType) <<
", but got type " << currentToken.GetTokenTypeName() << std::endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " <<
		currentToken. GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}

void ParserClass::Start() {
	Program();
	Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	Block();
}

void ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroup();
	Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
    while (true) {
        bool ok = Statement();
        if (!ok) { return; }
    }
}

bool ParserClass::Statement() {
    TokenClass tc;
	tc = mScanner->PeekNextToken();
	TokenType tokentype = tc.getTokenType();
	if (tokentype == INT_TOKEN) {
		Declaration();
	} else if (tokentype == IDENTIFIER_TOKEN) {
		Assignment();
	} else if (tokentype == COUT_TOKEN) {
		Cout();
	} else if (tokentype == LCURLY_TOKEN) {
		Block();
	} else { return false; }
	return true;
}

void ParserClass::Declaration() {
	Match(INT_TOKEN);
	Identifier();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::Assignment() {
	Identifier();
	Match(ASSIGNMENT_TOKEN);
	Expression();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::Cout() {
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	Expression();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::Identifier() {
	Match(IDENTIFIER_TOKEN);
}

void ParserClass::Integer() {
	Match(INTEGER_TOKEN);
}

void ParserClass::Expression() {
	Relational();
}

void ParserClass::Relational() {
	PlusMinus();
	// Handle the optional tail:
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == LESS_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if(tt == LESSEQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if(tt == GREATER_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if(tt == GREATEREQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if(tt == EQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if(tt == NOTEQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else { return; }
}

void ParserClass::PlusMinus() {
	TimesDivide();
	while(true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == PLUS_TOKEN) {
			Match(tt);
			TimesDivide();
		} else if(tt == MINUS_TOKEN) {
			Match(tt);
			TimesDivide();
		} else { return; }
	}
}

void ParserClass::TimesDivide() {
	Factor();
	while(true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == TIMES_TOKEN) {
			Match(tt);
			Factor();
		} else if(tt == MINUS_TOKEN) {
			Match(tt);
			Factor();
		} else { return; }
	}
}

void ParserClass::Factor() {
    TokenClass tc;
	tc = mScanner->PeekNextToken();
	TokenType tokentype = tc.getTokenType();
	if (tokentype == IDENTIFIER_TOKEN) {
		Identifier();
	} else if (tokentype == INTEGER_TOKEN) {
		Integer();
	} else if (tokentype == LPAREN_TOKEN) {
		Match(LPAREN_TOKEN);
		Expression();
		Match(RPAREN_TOKEN);
	} else {
		std::cout << "ERR: Invalid Factor Token :" ;
		exit(1);
	}
	return;
}
