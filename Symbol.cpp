#include "Symbol.h"

// returns true if <s> is already in the symbol table.
bool SymbolTableClass::Exists(const std::string & s) {
    auto it = std::find_if(mSymbolTable.begin(), mSymbolTable.end(),
                        [s] (const Variable& sv) {
                            return sv.mLabel == s;
                        });
    return it != mSymbolTable.end();
}

// adds <s> to the symbol table,
// or quits if it was already there
void SymbolTableClass::AddEntry(const std::string & s) {
    if (not Exists(s)) {
        Variable sv = {s};
        mSymbolTable.push_back(sv);
    } else {
        std::cout << "Error: SymbolTableClass::AddEntry, Element '" + s + "' already exists."  << std::endl;
    }
}

// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
int SymbolTableClass::GetValue(const std::string & s) {

    // Check if element s exists in vector
    auto it = std::find_if(mSymbolTable.begin(), mSymbolTable.end(),
                        [s] (const Variable& sv) {
                            return sv.mLabel == s;
                        });
    //std::vector<Variable>::iterator it = std::find(mSymbolTable.begin(), mSymbolTable.end(), sv);

    if (it != mSymbolTable.end()) {
        // Element Found
        // Get index of element from iterator
        int index = std::distance(mSymbolTable.begin(), it);
        return mSymbolTable.at(index).mValue;
    } else {
        std::cout << "Error: SymbolTableClass::GetValue, Element '" + s + "' does not exist."  << std::endl;
        exit(EXIT_FAILURE);
        // Element Not Found
    }
}

// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTableClass::SetValue(const std::string & s, int v) {
    // Check if element s exists in vector
    auto it = std::find_if(mSymbolTable.begin(), mSymbolTable.end(),
                        [s] (const Variable& sv) {
                            return sv.mLabel == s;
                        });
    //std::vector<Variable>::iterator it = std::find(mSymbolTable.begin(), mSymbolTable.end(), sv);

    if (it != mSymbolTable.end()) {
        // Element Found
        // Get index of element from iterator
        int index = std::distance(mSymbolTable.begin(), it);
        mSymbolTable.at(index).mValue = v;
    } else {
        std::cout << "Error: SymbolTableClass::SetValue, Element '" + s + "' does not exist."  << std::endl;
        exit(EXIT_FAILURE);
        // Element Not Found
    }
}

// returns the index of where variable <s> is.
// returns -1 if variable <s> is not there.
int SymbolTableClass::GetIndex(const std::string & s) {
    // get iterator
    auto it = std::find_if(mSymbolTable.begin(), mSymbolTable.end(),
                        [s] (const Variable& sv) {
                            return sv.mLabel == s;
                        });
    // transform to index
    int index = std::distance(mSymbolTable.begin(), it);
    return index;
}

// returns the current number of variables in the symbol
// table.
int SymbolTableClass::GetCount() {
    return mSymbolTable.size();
}
