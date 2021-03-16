#include "test.h"

// test Parser
int testParser() {
    ScannerClass scanner("source.txt");
    SymbolTableClass symboltable;
    ParserClass pc = ParserClass(&scanner,&symboltable);
    StartNode* sn = pc.Start();
    delete sn;
    return 0;
}

// test Nodes
int testNodes() {
    SymbolTableClass st;

    // in1 -> ds
    IdentifierNode *in1 = new IdentifierNode(&st, "base");
    DeclarationStatementNode *ds = new DeclarationStatementNode(in1);

    //in2, int1 + int2 = plus -> as1
    IdentifierNode *in2 = new IdentifierNode(&st, "sum");
    IntegerNode *int1 = new IntegerNode(300);
    IntegerNode *int2 = new IntegerNode(5);
    PlusNode *plus = new PlusNode(int1,int2);
    AssignmentStatementNode *as1 = new AssignmentStatementNode(in2,plus);

    //in3, int3 - int4 = minus -> as2
    IdentifierNode *in3 = new IdentifierNode(&st, "minus");
    IntegerNode *int3 = new IntegerNode(300);
    IntegerNode *int4 = new IntegerNode(5);
    MinusNode *minus = new MinusNode(int3,int4);
    AssignmentStatementNode *as2 = new AssignmentStatementNode(in3,minus);

    //in4, int5 > int6 = greater -> as3
    IdentifierNode *in4 = new IdentifierNode(&st, "less");
    IntegerNode *int5 = new IntegerNode(300);
    IntegerNode *int6 = new IntegerNode(5);
    GreaterNode *greater = new GreaterNode(int5,int6);
    AssignmentStatementNode *as3 = new AssignmentStatementNode(in4,greater);

    StatementGroupNode *sg = new StatementGroupNode();
    sg->addStatement(ds);
    sg->addStatement(as1);
    sg->addStatement(as2);
    sg->addStatement(as3);

    BlockNode *bn = new BlockNode(sg);
    ProgramNode *pn = new ProgramNode(bn);
    StartNode *sn = new StartNode(pn);
    delete sn;
    return 0;
}

// test SymbolClass
int testSymbolClass() {
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

    std::cout << "(Not actually an Error:) ";
    S.AddEntry("s");
    return 0;
}

// test scanner
int testScanner() {
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

// initial test
int testToken() {
    TokenType tt = VOID_TOKEN;
    std::string lexeme = "void";
    TokenClass tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
    return 0;
}
