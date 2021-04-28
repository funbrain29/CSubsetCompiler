#ifndef TEST
#define TEST

#include <string>
#include "Parser.h"

void CodeAndExecute(std::string filename,int flag=0);
void ParseAndInterpret(std::string filename);
void runTests(std::string filename);
int testMachineCode(std::string filename);
int testParser(std::string filename);
int testNodes();
int testSymbolClass();
int testScanner(std::string filename);
int testToken();

#endif
