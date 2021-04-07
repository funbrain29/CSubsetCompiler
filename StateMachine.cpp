#include "StateMachine.h"

// The constructor should initialize mCurrentState to START_STATE.  UpdateState should change mCurrentState, based on its current value and the input character.  Eventually, UpdateState will return CANTMOVE_STATE, which signifies to the calling code that the current token is completed.  The reference parameter correspondingTokenType should be set by UpdateState, so that the calling code knows what kind of TokenType it should make.  If the current state of the machine is not a valid end state, then correspondingTokenType should be set to BAD_TOKEN, so the calling code knows to print an error message and quit

StateMachineClass::StateMachineClass() {
    mCurrentState = START_STATE;
    // First, initialize all the mLegalMoves to CANTMOVE_STATE
    // Then, reset the mLegalMoves that are legitimate
    for(int i = 0; i < LAST_STATE; i++)
    {
        for(int j = 0; j < LAST_CHAR; j++)
        {
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }

    // All EOF_CHAR will return EOF_STATE no matter the last state
    for(int i = 0; i < LAST_STATE; i++) {
        mLegalMoves[EOF_CHAR][i] = EOF_STATE;
        mLegalMoves[COMMENT_STATE][i] = COMMENT_STATE;
        mLegalMoves[ENDCOMMENT_STATE][i] = COMMENT_STATE;
    }

    for(int i = 0; i < LAST_STATE; i++) {
        mLegalMoves[SCOMMENT_STATE][i] = SCOMMENT_STATE;
    }

    // start states
    mLegalMoves[START_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR]= INTEGER_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR]= PLUS_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR]= MINUS_STATE;
    mLegalMoves[START_STATE][TIMES_CHAR]= TIMES_STATE;
    mLegalMoves[START_STATE][DIVIDE_CHAR]= DIVIDE_STATE;
    mLegalMoves[START_STATE][SEMICOLON_CHAR]= SEMICOLON_STATE;
    mLegalMoves[START_STATE][LESS_CHAR]= LESS_STATE;
    mLegalMoves[START_STATE][GREAT_CHAR]= GREAT_STATE;
    mLegalMoves[START_STATE][EQUAL_CHAR]= ASSIGNMENT_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR]= LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR]= RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR]= LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR]= RCURLY_STATE;
    mLegalMoves[START_STATE][EXCL_CHAR]= NOT_STATE;
    mLegalMoves[START_STATE][EOF_CHAR]= EOF_STATE;
    mLegalMoves[START_STATE][AND_CHAR]= AMP_STATE;
    mLegalMoves[START_STATE][OR_CHAR]= BAR_STATE;
    //Whitespace
    mLegalMoves[START_STATE][WHITESPACE_CHAR]= START_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR]= START_STATE;
    //double symbols
    mLegalMoves[LESS_STATE][LESS_CHAR]= INSERTION_STATE;
    mLegalMoves[LESS_STATE][EQUAL_CHAR]= LESSEQ_STATE;
    mLegalMoves[GREAT_STATE][EQUAL_CHAR]= GREATEQ_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR]= INTEGER_STATE;
    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR]= EQUAL_STATE;
    mLegalMoves[NOT_STATE][EQUAL_CHAR]= NOTEQ_STATE;
    mLegalMoves[AMP_STATE][AND_CHAR]= AND_STATE;
    mLegalMoves[BAR_STATE][OR_CHAR]= OR_STATE;
    //Identifier continues
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]= IDENTIFIER_STATE;
    //comments
    mLegalMoves[DIVIDE_STATE][TIMES_CHAR]= COMMENT_STATE;
    mLegalMoves[COMMENT_STATE][TIMES_CHAR]= ENDCOMMENT_STATE;
    mLegalMoves[ENDCOMMENT_STATE][DIVIDE_CHAR]= START_STATE;
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR]= SCOMMENT_STATE;
    mLegalMoves[SCOMMENT_STATE][NEWLINE_CHAR]= START_STATE;

    //Corresponding TokenTypes
    for(int i=0; i<LAST_STATE; i++) {
        mCorrespondingTokenTypes[i]=BAD_TOKEN;
    }

    // Relational Operators:
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[LESSEQ_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[GREAT_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[GREATEQ_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[NOTEQ_STATE] = NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
    mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
    // Other Operators:
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[AMP_STATE] = BITWISE_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    //Other Characters:
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    // Other Token Types:
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[EOF_STATE] = ENDFILE_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter,
TokenType & correspondingTokenType) {
    CharacterType charType = BAD_CHAR;

    if(currentCharacter == '(') {
        charType = LPAREN_CHAR;
    } else if(currentCharacter == ')') {
        charType = RPAREN_CHAR;
    } else if(currentCharacter == '\n') {
        charType = NEWLINE_CHAR;
    } else if(isdigit(currentCharacter)) {
        charType = DIGIT_CHAR;
    } else if(isalpha(currentCharacter)) {
        charType = LETTER_CHAR;
    } else if(isspace(currentCharacter)) {
        charType = WHITESPACE_CHAR;
    } else if(currentCharacter == EOF) {
        charType = EOF_CHAR;
    } else if(currentCharacter == '+') {
        charType = PLUS_CHAR;
    } else if(currentCharacter == ';') {
        charType = SEMICOLON_CHAR;
    } else if(currentCharacter == '<') {
        charType = LESS_CHAR;
    } else if(currentCharacter == '>') {
        charType = GREAT_CHAR;
    } else if(currentCharacter == '=') {
        charType = EQUAL_CHAR;
    } else if(currentCharacter == '{') {
        charType = LCURLY_CHAR;
    } else if(currentCharacter == '}') {
        charType = RCURLY_CHAR;
    } else if(currentCharacter == '!') {
        charType = EXCL_CHAR;
    } else if(currentCharacter == '-') {
        charType = MINUS_CHAR;
    } else if(currentCharacter == '*') {
        charType = TIMES_CHAR;
    } else if(currentCharacter == '/') {
        charType = DIVIDE_CHAR;
    } else if(currentCharacter == '&') {
        charType = AND_CHAR;
    } else if(currentCharacter == '|') {
        charType = OR_CHAR;
    }
    mCurrentState = mLegalMoves[mCurrentState][charType];
    if (mCurrentState != CANTMOVE_STATE) {
        correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    }
    TokenClass testtoken(correspondingTokenType,std::string(1,currentCharacter));
    /*MSG("Character: '" + std::string(1,currentCharacter) + "'"
    + " gives CharType: '" + gCharacterTypeNames[charType] + "'"
    + " gives MachineState: '" + gMachineStateNames[mCurrentState] + "'"
    + " gives Token: '" + testtoken.GetTokenTypeName() + "'\n");*/
    return mCurrentState;
}
