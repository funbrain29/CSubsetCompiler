#ifndef PARSER
#define PARSER

#include "Node.h"

class ParserClass {
private:
    ScannerClass *mScanner;
    SymbolTableClass *mSymbolTable;
    TokenClass Match(TokenType expectedType);
    void Program();
    void Block();
    void StatementGroup();
    bool Statement();
    void Declaration();
    void Assignment();
    void Cout();
    void Identifier();
    void Integer();
    void Expression();
    void Relational();
    void PlusMinus();
    void TimesDivide();
    void Factor();

public:
    ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable);
    void Start();
};

#endif // PARSER
