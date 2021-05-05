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
	MSG("Successfully matched Token Type: " <<
		currentToken. GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"\n");
	return currentToken; // the one we just processed
}

StartNode* ParserClass::Start() {
	ProgramNode *pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode* sn = new StartNode(pn);
	return sn;
}

ProgramNode* ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode* bn = Block();
	ProgramNode* pb = new ProgramNode(bn);
	return pb;
}

BlockNode* ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroupNode* sgn = StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode* bn = new BlockNode(sgn);
	return bn;
}

StatementGroupNode* ParserClass::StatementGroup() {
	StatementGroupNode* sgn = new StatementGroupNode;
    while (true) {
        StatementNode* sn = Statement();
        if (sn == NULL) { break; }
		sgn->addStatement(sn);
    }
	return sgn;
}

StatementNode* ParserClass::Statement() {
    TokenClass tc;
	MSG("\n---Statement peeking\n");
	tc = mScanner->PeekNextToken();
	TokenType tokentype = tc.getTokenType();
	MSG("---Statement token peeked: " << gTokenTypeNames[tokentype] << "\n\n");
	if (tokentype == INT_TOKEN) {
		Match(INT_TOKEN);
		IdentifierNode* in = Identifier();

		TokenClass tc2;
		MSG("\n---StatementDeclaration peeking\n");
		tc2 = mScanner->PeekNextToken();
		TokenType tokentype2 = tc2.getTokenType();
		MSG("---StatementDeclaration token peeked: " << gTokenTypeNames[tokentype] << "\n\n");

		if (tokentype2 == SEMICOLON_TOKEN) {
			DeclarationStatementNode* xsn = Declaration(in);
			return xsn;
		} else {
			DeclarationAssignmentStatementNode* xsn = DeclarationAssignment(in);
			return xsn;
		}
	} else if (tokentype == IDENTIFIER_TOKEN) {
		AssignmentStatementNode* xsn = Assignment();
		return xsn;
	} else if (tokentype == COUT_TOKEN) {
		CoutStatementNode* xsn = Cout();
		return xsn;
	} else if (tokentype == IF_TOKEN) {
		IfStatementNode* xsn = If();
		return xsn;
	} else if (tokentype == WHILE_TOKEN) {
		WhileStatementNode* xsn = While();
		return xsn;
	} else if (tokentype == DOWHILE_TOKEN) {
		WhileStatementNode* xsn = DoWhile();
		return xsn;
	} else if (tokentype == LCURLY_TOKEN) {
		BlockNode* xsn = Block();
		return xsn;
	}
	return NULL;
}

DeclarationStatementNode* ParserClass::Declaration(IdentifierNode *in) {
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode* dsn = new DeclarationStatementNode(in);
	return dsn;
}

DeclarationAssignmentStatementNode* ParserClass::DeclarationAssignment(IdentifierNode *in) {
	Match(ASSIGNMENT_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	DeclarationAssignmentStatementNode* dsn = new DeclarationAssignmentStatementNode(in,en);
	return dsn;
}

AssignmentStatementNode* ParserClass::Assignment() {
	IdentifierNode* in = Identifier();

	// check for =, +=, or -=

	TokenClass tc;
	MSG("\n---CoutStatement peeking\n");
	tc = mScanner->PeekNextToken();
	TokenType tokentype = tc.getTokenType();
	MSG("---CoutStatement token peeked: " << gTokenTypeNames[tokentype] << "\n\n");

	if (tokentype == PLUSEQUALS_TOKEN) {
		Match(PLUSEQUALS_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		PlusEqualsStatementNode* asn = new PlusEqualsStatementNode(in,en);
		return asn;

	} else if (tokentype == MINUSEQUALS_TOKEN) {
		Match(MINUSEQUALS_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		MinusEqualsStatementNode* asn = new MinusEqualsStatementNode(in,en);
		return asn;

	} else if (tokentype == TIMESEQUALS_TOKEN) {
		Match(TIMESEQUALS_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		TimesEqualsStatementNode* asn = new TimesEqualsStatementNode(in,en);
		return asn;

	} else {
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode* asn = new AssignmentStatementNode(in,en);
		return asn;
	}
	return NULL;
}

CoutStatementNode* ParserClass::Cout() {
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	CoutStatementNode* cn = new CoutStatementNode();

	for (;;) {
		// peek first time to check if expression or endl
		TokenClass tc;
		MSG("\n---CoutStatement peeking\n");
		tc = mScanner->PeekNextToken();
		TokenType tokentype = tc.getTokenType();
		MSG("---CoutStatement token peeked: " << gTokenTypeNames[tokentype] << "\n\n");

		if (tokentype == ENDL_TOKEN) {
			Match(ENDL_TOKEN);
			ExpressionNode *p = NULL;
			cn->addExpression(p);
		} else {
			ExpressionNode* en = Expression();
			cn->addExpression(en);
		}

		// peek second time to check if semicolon or if there is more to print
		MSG("\n---CoutStatement peeking\n");
		tc = mScanner->PeekNextToken();
		tokentype = tc.getTokenType();
		MSG("---CoutStatement token peeked: " << gTokenTypeNames[tokentype] << "\n\n");

		if (tokentype == SEMICOLON_TOKEN) {
			break;
		} else if (tokentype == INSERTION_TOKEN) {
			Match(INSERTION_TOKEN);
			// loop again
		}
	}

	Match(SEMICOLON_TOKEN);
	return cn;
}

IfStatementNode* ParserClass::If() {
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	BlockNode* bn = Block();
	IfStatementNode* in = new IfStatementNode(en,bn);
	return in;
}

WhileStatementNode* ParserClass::While() {
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	BlockNode* bn = Block();
	WhileStatementNode* in = new WhileStatementNode(en,bn);
	return in;
}

WhileStatementNode* ParserClass::DoWhile() {
	Match(DOWHILE_TOKEN);
	StatementNode* sn = Statement();
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	Match(SEMICOLON_TOKEN);
	WhileStatementNode* in = new WhileStatementNode(en,sn);
	return in;
}

IdentifierNode* ParserClass::Identifier() {
	TokenClass tc = Match(IDENTIFIER_TOKEN);
	IdentifierNode* in = new IdentifierNode(mSymbolTable,tc.GetLexeme());
	return in;
}

IntegerNode* ParserClass::Integer() {
	TokenClass tc = Match(INTEGER_TOKEN);
	IntegerNode* in = new IntegerNode(stoi(tc.GetLexeme()));
	return in;
}

ExpressionNode* ParserClass::Expression() {
	return Or();
}

ExpressionNode* ParserClass::Or() {
	ExpressionNode* current = And();

	MSG("\n---Or peeking\n");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	MSG("---Or token peeked: " << gTokenTypeNames[tt] << "\n\n");

	if(tt == OR_TOKEN) {
		Match(tt);
		current = new OrNode(current,And());
	}
	return current;
}

ExpressionNode* ParserClass::And() {
	ExpressionNode* current = BitwiseAnd();

	MSG("\n---Or peeking\n");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	MSG("---Or token peeked: " << gTokenTypeNames[tt] << "\n\n");

	if(tt == AND_TOKEN) {
		Match(tt);
		current = new AndNode(current,BitwiseAnd());
	}
	return current;
}

// Bitwise and currently nonfunctional, no machine code equal
ExpressionNode* ParserClass::BitwiseAnd() {
	return Relational();
	/*
	ExpressionNode* current = Relational();

	MSG("\n---Or peeking\n");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	MSG("---Or token peeked: " << gTokenTypeNames[tt] << "\n\n");

	if(tt == BITWISE_TOKEN) {
		Match(tt);
		current = new BitwiseAndNode(current,Relational());
	}
	return current;
	*/
}

ExpressionNode* ParserClass::Relational() {
	ExpressionNode* current = PlusMinus();

	MSG("\n---Relational peeking\n");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	MSG("---Relational token peeked: " << gTokenTypeNames[tt] << "\n\n");

	if(tt == LESS_TOKEN) {
		Match(tt);
		current = new LessNode(current,PlusMinus());
	}
	else if(tt == LESSEQUAL_TOKEN) {
		Match(tt);
		current = new LessEqualNode(current,PlusMinus());
	}
	else if(tt == GREATER_TOKEN) {
		Match(tt);
		current = new GreaterNode(current,PlusMinus());
	}
	else if(tt == GREATEREQUAL_TOKEN) {
		Match(tt);
		current = new GreaterEqualNode(current,PlusMinus());
	}
	else if(tt == EQUAL_TOKEN) {
		Match(tt);
		current = new EqualNode(current,PlusMinus());
	}
	else if(tt == NOTEQUAL_TOKEN) {
		Match(tt);
		current = new NotEqualNode(current,PlusMinus());
	}
	return current;
}

ExpressionNode* ParserClass::PlusMinus() {
	ExpressionNode* current = TimesDivide();
	while(true) {

		MSG("\n---PlusMinus peeking\n");
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		MSG("---PlusMinus token peeked: " << gTokenTypeNames[tt] << "\n\n");

		if(tt == PLUS_TOKEN) {
			Match(tt);
			current = new PlusNode(current,TimesDivide());
		} else if(tt == MINUS_TOKEN) {
			Match(tt);
			current = new MinusNode(current,TimesDivide());
		} else { return current; }
	}
}

ExpressionNode* ParserClass::TimesDivide() {
	ExpressionNode* current = Factor();
	while(true) {

		MSG("\n---TimesDivide peeking\n");
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		MSG("---TimesDivide token peeked: " << gTokenTypeNames[tt] << "\n\n");

		if(tt == TIMES_TOKEN) {
			Match(tt);
			current = new TimesNode(current,Factor());
		} else if(tt == DIVIDE_TOKEN) {
			Match(tt);
			current = new DivideNode(current,Factor());
		} else { return current; }
	}
}

ExpressionNode* ParserClass::Factor() {

	MSG("\n---Factor peeking\n");
	TokenClass tc = mScanner->PeekNextToken();
	TokenType tokentype = tc.getTokenType();
	MSG("---Factor token peeked: " << gTokenTypeNames[tokentype] << "\n\n");

	if (tokentype == IDENTIFIER_TOKEN) {
		return Identifier();
	} else if (tokentype == INTEGER_TOKEN) {
		return Integer();
	} else if (tokentype == LPAREN_TOKEN) {
		Match(LPAREN_TOKEN);
		return Expression();
		Match(RPAREN_TOKEN);
	} else {
		std::cout << "ERR: Invalid Factor Token :" ;
		exit(1);
	}
	return NULL;
}
