#ifndef SCANNER
#define SCANNER

#include "StateMachine.h"

class ScannerClass {
public:
    ScannerClass(std::string input);
    int GetLineNumber() const {return mLineNumber;};
    TokenClass GetNextToken();
private:
    int mLineNumber;
    std::ifstream mFin;
};

#endif // SCANNER
