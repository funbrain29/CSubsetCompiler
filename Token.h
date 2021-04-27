#ifndef TOKEN
#define TOKEN

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "debug.h"

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, FOR_TOKEN, IF_TOKEN, WHILE_TOKEN, ENDL_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN,
	// And, Or, Assignment tokens:
	AND_TOKEN, OR_TOKEN, BITWISE_TOKEN, PLUSEQUALS_TOKEN, MINUSEQUALS_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, BAD_TOKEN, ENDFILE_TOKEN
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "FOR", "IF", "WHILE", "ENDL",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"AND", "OR", "BITWISE", "PLUSEQUALS", "MINUSEQUALS",
	"IDENTIFIER", "INTEGER", "BAD", "ENDFILE"
};

class TokenClass {
private:
	TokenType mType;
	std::string mLexeme;
public:
	TokenClass();
	TokenClass(TokenType type, const std::string & lexeme);
	TokenType GetTokenType() const { return mType; }
	const std::string & GetTokenTypeName() const
        { return gTokenTypeNames[mType]; }
	std::string GetLexeme() const { return mLexeme; }
	void CheckReserved();
	static const std::string & GetTokenTypeName(TokenType type)
		{ return gTokenTypeNames[type]; }
	TokenType getTokenType();
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);

#endif // TOKEN
