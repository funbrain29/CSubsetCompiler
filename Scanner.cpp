#include "Scanner.h"

ScannerClass::ScannerClass(std::string input) {
    mLineNumber = 1;
    mFin.open(input.c_str(), std::ios::binary);
    if (! mFin.is_open()) {
        std::cout << "Failed to open file: " + input;
        exit(EXIT_FAILURE);
    }
}

TokenClass ScannerClass::GetNextToken() {
    StateMachineClass stateMachine;
    MachineState machineState;
    TokenType tokenType;
    std::string lexeme;

    do {
        char c = mFin.get();
        machineState = stateMachine.UpdateState(c, tokenType);
        if (machineState != START_STATE) {
            lexeme += c;
            if (machineState == ENDCOMMENT_STATE
            || machineState == COMMENT_STATE
            || machineState == SCOMMENT_STATE) {
                lexeme = "";
                if (c == '\n') {
                    mLineNumber += 1;
                }
            }
        } else {
            if (c == '\n') {
                mLineNumber += 1;
            }
        }
    } while (machineState != CANTMOVE_STATE
    && machineState != EOF_STATE);
    if (tokenType == BAD_TOKEN) {
        std::cout << "Error: BAD_TOKEN when parsing lexeme: '" + lexeme + "'\n";
        exit(EXIT_FAILURE);
    }
    lexeme.pop_back();
    TokenClass tokenClass(tokenType, lexeme);
    tokenClass.CheckReserved();
    mFin.unget();
    MSG("   Scanner: Scanned token \"" << gTokenTypeNames[tokenType] << "\" from lexeme \"" << lexeme << "\"\n" );
    return tokenClass;
}

TokenClass ScannerClass::PeekNextToken() {
    int currentLineNumber = mLineNumber;
    std::streampos p = mFin.tellg();
    TokenClass t = GetNextToken();
    if(!mFin) {
        mFin.clear();
    }
    mFin.seekg(p);
    mLineNumber = currentLineNumber;
    return t;
}
