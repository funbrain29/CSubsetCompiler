/*
// test Machine Code function
#include <iostream>
using namespace std;
int main() {
    unsigned char mCode[] = {0x55, 0x8B, 0xEC, 0X5d, 0XC3};
    cout << "About to Execute the machine code...\n";
    void * ptr = mCode;
    void (*f)(void);
    f = (void (*)(void)) ptr ;
    f(); // call the array as if it were a function
    cout << "There and back again!\n\n";
    return 0;
}
*/

#include "test.h"

int main() {
    std::cout << "--Running Token Test--\n";
    if (testToken() == 0) {
        std::cout << "--Token Test Finished--\n";
    };
    std::cout << "\n--Running Scanner Test--\n";
    if (testScanner() == 0) {
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
    std::cout << "\n--Running Parser Test--\n";
    if (testParser() == 0) {
        std::cout << "\n--Parser Test Finished--\n";
    };
    std::cout << "\n--Running MachineCode Test--\n";
    if (testMachineCode() == 0) {
        std::cout << "--MachineCode Test Finished--\n";
    };
    return 0;
}
