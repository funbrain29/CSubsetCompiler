#include "Parser.h"

ParserClass::ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable) {
    mScanner = Scanner;
    mSymbolTable = SymbolTable;
}
