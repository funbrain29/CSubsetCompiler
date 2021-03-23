#include "Token.h"

TokenClass::TokenClass() {
}

TokenClass::TokenClass(TokenType type, const std::string & lexeme) {
    mType = type;
    mLexeme = lexeme;
}

TokenType TokenClass::getTokenType() {
    return mType;
}

void TokenClass::CheckReserved() {
    if (GetLexeme() == "void") {
        mType = VOID_TOKEN;
    } else if (GetLexeme() == "main") {
        mType = MAIN_TOKEN;
    } else if (GetLexeme() == "int") {
        mType = INT_TOKEN;
    } else if (GetLexeme() == "cout") {
        mType = COUT_TOKEN;
    } else if (GetLexeme() == "for") {
        mType = FOR_TOKEN;
    } else if (GetLexeme() == "if") {
        mType = IF_TOKEN;
    } else if (GetLexeme() == "while") {
        mType = WHILE_TOKEN;
    }
}

std::ostream & operator<<(std::ostream & out, const TokenClass & tc) {
    out.setf(std::ios::left);
    out << "Type: " << std::setw(15) << tc.GetTokenTypeName()<< "Lexeme: " << std::setw(15) << tc.GetLexeme();
    return out;
}
