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
    return 0;
}
