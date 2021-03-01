#ifndef PARSER
#define PARSER

#include "Node.h"

class ParserClass {
    private:
    ScannerClass *mScanner;
    SymbolTableClass *mSymbolTable;
    public:
    ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable);
    Start();

};

#endif // PARSER
