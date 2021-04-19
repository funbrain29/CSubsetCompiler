#ifndef TEST
#define TEST

#include <string>
#include "Parser.h"

void CodeAndExecute(std::string filename,int flag=0);
void runTests();
int testNodes();
int testSymbolClass();
int testScanner();
int testToken();
int testParser();
int testMachineCode();

#endif
