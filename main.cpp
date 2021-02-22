#include "Node.h"

int main() {
    SymbolTableClass st;
    std::string mystring;
    IdentifierNode *in1 = new IdentifierNode(&st, "sum");
    DeclarationStatementNode *ds = new DeclarationStatementNode(in1);
    IdentifierNode *in2 = new IdentifierNode(&st, "sum");
    IntegerNode *int1 = new IntegerNode(300);
    IntegerNode *int2 = new IntegerNode(5);
    PlusNode *plus = new PlusNode(int1,int2);
    AssignmentStatementNode *as = new AssignmentStatementNode(in2,plus);
    StatementGroupNode *sg = new StatementGroupNode();
    sg->addStatement(ds);
    sg->addStatement(as);
    std::cout << "Success!\n";
    return 0;
}

// test SymbolClass
/*
int main() {
    SymbolTableClass SymbolClass;
    SymbolClass.AddEntry("variable zero");
    SymbolClass.SetValue("variable zero", 0);
    SymbolClass.AddEntry("variable one");
    SymbolClass.SetValue("variable one", 1);
    std::cout << "index:" << SymbolClass.GetIndex("variable zero") << std::endl;
    std::cout << "value:" << SymbolClass.GetValue("variable zero") << std::endl;
    std::cout << "index:" << SymbolClass.GetIndex("variable one") << std::endl;
    std::cout << "value:" << SymbolClass.GetValue("variable one") << std::endl;
    std::cout << "count:" << SymbolClass.GetCount() << std::endl;

    SymbolTableClass S;
    std::cout << S.Exists("s") << std::endl;
    S.AddEntry("s");
    std::cout << S.Exists("s") << std::endl;
    S.SetValue("s",200);
    std::cout << S.GetValue("s") << std::endl;

    S.AddEntry("s");
    return 0;
}
*/

// test scanner
/*
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

// initial test
/*
int main() {
    TokenType tt = VOID_TOKEN;
    std::string lexeme = "void";
    TokenClass tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
    return 0;
}
*/
