#include "Functions.h"

int main() {
    ParseAndInterpret("source.txt");
    CodeAndExecute("source.txt");

    // include 'true' to print machine code values as well.
    // CodeAndExecute("source.txt", true);
    return 0;
}
