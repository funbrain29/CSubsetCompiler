#include "Functions.h"

void CodeAndExecute(std::string filename, int flag) {
    // Create scanner, symbol table, and parser objects.
    ScannerClass scanner(filename);
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    // Do the parsing, which results in a parse tree.
    StartNode * sn = parser.Start();

    // Create the machine code instructions from the parse tree
    InstructionsClass machineCode;
    sn->Code(machineCode);
    machineCode.Finish();
    if (flag) {
        machineCode.PrintAllMachineCodes();
    }

    // Execute the machine code instructions previously created
    machineCode.Execute();

    // cleanup recursively
    delete sn;
}

// run tests
void runTests(std::string filename) {
    /*
    std::cout << "--Running Token Test--\n";
    if (testToken() == 0) {
        std::cout << "--Token Test Finished--\n";
    };
    std::cout << "\n--Running Scanner Test--\n";
    if (testScanner(filename) == 0) {
        std::cout << "--Scanner Test Finished--\n";
    };
    std::cout << "\n--Running SymbolClass Test--\n";
    if (testSymbolClass() == 0) {
        std::cout << "--SymbolClass Test Finished--\n";
    };
    std::cout << "\n--Running Nodes Test--\n";
    if (testNodes() == 0) {
        std::cout << "--Nodes Test Finished--\n";
    };
    */
    std::cout << "\n--Running Parser Test--\n";
    if (testParser(filename) == 0) {
        std::cout << "\n--Parser Test Finished--\n";
    };
    std::cout << "\n--Running MachineCode Test--\n";
    if (testMachineCode(filename) == 0) {
        std::cout << "--MachineCode Test Finished--\n";
    };
}

// test MachineCode
int testMachineCode(std::string filename) {
    // Create scanner, symbol table, and parser objects.
    ScannerClass scanner(filename);
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);

    // Do the parsing, which results in a parse tree.
    StartNode * sn = parser.Start();

    // Create the machine code instructions from the parse tree
    InstructionsClass machineCode;
    sn->Code(machineCode);
    machineCode.Finish();

    // Execute the machine code instructions previously created
    machineCode.Execute();

    // cleanup recursively
    delete sn;

    return 0;
}

// test Parser
int testParser(std::string filename) {
    ScannerClass scanner(filename);
    SymbolTableClass symboltable;
    ParserClass pc = ParserClass(&scanner,&symboltable);
    StartNode* sn = pc.Start();
    MSG("Parser Started, Interpreting...\n");
    sn->Interpret();


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
int testScanner(std::string filename) {
    ScannerClass scanner(filename);
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
