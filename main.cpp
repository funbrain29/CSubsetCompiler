#include "Scanner.h"

int main() {
    ScannerClass scanner("source.txt");
    TokenClass currentToken;
    TokenClass endToken(ENDFILE_TOKEN,"");

    while (currentToken.GetTokenType() != ENDFILE_TOKEN) {
        currentToken = scanner.GetNextToken();
        std::cout << currentToken << "Line: "
        << std::setw(15) << scanner.GetLineNumber() << std::endl;
    }

    return 0;
}

/*
int main() {
    TokenType tt = VOID_TOKEN;
    std::string lexeme = "void";
    TokenClass tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
    return 0;
}
*/
