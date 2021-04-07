#ifndef PARSER
#define PARSER

#include "Node.h"

class ParserClass {
private:
    ScannerClass *mScanner;
    SymbolTableClass *mSymbolTable;
    TokenClass Match(TokenType expectedType);
    ProgramNode* Program();
    BlockNode* Block();
    StatementGroupNode* StatementGroup();
    StatementNode* Statement();
    DeclarationStatementNode* Declaration(IdentifierNode *in);
    DeclarationAssignmentStatementNode* DeclarationAssignment(IdentifierNode *in);
    AssignmentStatementNode* Assignment();
    CoutStatementNode* Cout();
    IfStatementNode* If();
    WhileStatementNode* While();
    IdentifierNode* Identifier();
    IntegerNode* Integer();
    ExpressionNode* Expression();
    ExpressionNode* Or();
    ExpressionNode* And();
    ExpressionNode* BitwiseAnd();
    ExpressionNode* Relational();
    ExpressionNode* PlusMinus();
    ExpressionNode* TimesDivide();
    ExpressionNode* Factor();

public:
    ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable);
    StartNode* Start();
};

#endif // PARSER
