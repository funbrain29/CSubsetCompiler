#include "Node.h"

Node::~Node() {
    MSG("Deleting Node\n");
}

// StartNode
StartNode::StartNode(ProgramNode *p) {
    mProgramNode = p;
}

void StartNode::Interpret() {
    mProgramNode->Interpret();
}

void StartNode::Code(InstructionsClass &machineCode) {
    mProgramNode->Code(machineCode);
}

StartNode::~StartNode() {
    MSG("StartNode Deleting ProgramNode\n");
    delete mProgramNode;
}

// ProgramNode
ProgramNode::ProgramNode(BlockNode *b) {
    mBlockNode = b;
}

void ProgramNode::Interpret() {
    mBlockNode->Interpret();
}

void ProgramNode::Code(InstructionsClass &machineCode) {
    mBlockNode->Code(machineCode);
}

ProgramNode::~ProgramNode() {
    MSG("ProgramNode Deleting BlockNode\n");
    delete mBlockNode;
}

// BlockNode
BlockNode::BlockNode(StatementGroupNode *s) {
    mStatementGroupNode = s;
}

void BlockNode::Interpret() {
    mStatementGroupNode->Interpret();
}

void BlockNode::Code(InstructionsClass &machineCode) {
    mStatementGroupNode->Code(machineCode);
}

BlockNode::~BlockNode() {
    MSG("BlockNode Deleting StatementGroupNode\n");
    delete mStatementGroupNode;
}

// StatementGroupNode
void StatementGroupNode::addStatement(StatementNode *p) {
    mStatementNodes.push_back(p);
}

void StatementGroupNode::Interpret() {
    std::vector<StatementNode*>::iterator it;
    int i = 0;
    for (it = mStatementNodes.begin(); it != mStatementNodes.end(); it++,i++ ) {
        mStatementNodes[i]->Interpret();
    }
}

void StatementGroupNode::Code(InstructionsClass &machineCode) {
    std::vector<StatementNode*>::iterator it;
    int i = 0;
    for (it = mStatementNodes.begin(); it != mStatementNodes.end(); it++,i++ ) {
        mStatementNodes[i]->Code(machineCode);
    }
}

StatementGroupNode::~StatementGroupNode() {
    std::vector<StatementNode*>::iterator it;
    int i = 0;
    MSG("StatementGroupNode Deleting StatementNodes\n");
    for (it = mStatementNodes.begin(); it != mStatementNodes.end(); it++,i++ ) {
    MSG("StatementGroupNode Deleted StatementNode\n");
        delete mStatementNodes[i];
    }
}

// DeclarationStatementNode
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *p) {
    mIdentifierNode = p;
}

void DeclarationStatementNode::Interpret() {
    mIdentifierNode->DeclareVariable();
}

void DeclarationStatementNode::Code(InstructionsClass &machineCode) {
    mIdentifierNode->DeclareVariable();
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("DeclarationStatementNode Deleting IdentifierNode\n");
    delete mIdentifierNode;
}

// DelcarationAssignmentNode
DeclarationAssignmentStatementNode::DeclarationAssignmentStatementNode(IdentifierNode *p, ExpressionNode *e = NULL) {
    mIdentifierNode = p;
    mExpressionNode = e;
}

void DeclarationAssignmentStatementNode::Interpret() {
    mIdentifierNode->DeclareVariable();
    mIdentifierNode->SetValue(mExpressionNode->Evaluate());
}

void DeclarationAssignmentStatementNode::Code(InstructionsClass &machineCode) {
    mIdentifierNode->DeclareVariable();
    mExpressionNode->CodeEvaluate(machineCode);
    int index = mIdentifierNode->GetIndex();
    machineCode.PopAndStore(index);
}

DeclarationAssignmentStatementNode::~DeclarationAssignmentStatementNode() {
    MSG("DeclarationStatementAssignmentNode Deleting IdentifierNode and ExpressionNode\n");
    delete mIdentifierNode;
    delete mExpressionNode;
}

// AssignmentStatementNode
AssignmentStatementNode::AssignmentStatementNode() {
    // empty, needs to exist for PlusEqual/MinusEqual-StatementNode's
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

void AssignmentStatementNode::Interpret() {
    mIdentifierNode->SetValue(mExpressionNode->Evaluate());
}

void AssignmentStatementNode::Code(InstructionsClass &machineCode) {
    mExpressionNode->CodeEvaluate(machineCode);
    int index = mIdentifierNode->GetIndex();
    machineCode.PopAndStore(index);
}

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("AssignmentStatementNode Deleting IdentifierNode and ExpressionNode\n");
    delete mIdentifierNode;
    delete mExpressionNode;
}

// PlusEqualsStatementNode
PlusEqualsStatementNode::PlusEqualsStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

void PlusEqualsStatementNode::Interpret() {
    mIdentifierNode->SetValue(mIdentifierNode->Evaluate() + mExpressionNode->Evaluate());
}

void PlusEqualsStatementNode::Code(InstructionsClass &machineCode) {
    mIdentifierNode->CodeEvaluate(machineCode);
    mExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
    int index = mIdentifierNode->GetIndex();
    machineCode.PopAndStore(index);
}

PlusEqualsStatementNode::~PlusEqualsStatementNode() {
    MSG("PlusEqualsStatementNode Deleting IdentifierNode and ExpressionNode\n");
    delete mIdentifierNode;
    delete mExpressionNode;
}

// MinusEqualsStatementNode
MinusEqualsStatementNode::MinusEqualsStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

void MinusEqualsStatementNode::Interpret() {
    mIdentifierNode->SetValue(mIdentifierNode->Evaluate() - mExpressionNode->Evaluate());
}

void MinusEqualsStatementNode::Code(InstructionsClass &machineCode) {
    mIdentifierNode->CodeEvaluate(machineCode);
    mExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
    int index = mIdentifierNode->GetIndex();
    machineCode.PopAndStore(index);
}

MinusEqualsStatementNode::~MinusEqualsStatementNode() {
    MSG("PlusEqualsStatementNode Deleting IdentifierNode and ExpressionNode\n");
    delete mIdentifierNode;
    delete mExpressionNode;
}

// TimesEqualsStatementNode
TimesEqualsStatementNode::TimesEqualsStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

void TimesEqualsStatementNode::Interpret() {
    mIdentifierNode->SetValue(mIdentifierNode->Evaluate() * mExpressionNode->Evaluate());
}

void TimesEqualsStatementNode::Code(InstructionsClass &machineCode) {
    mIdentifierNode->CodeEvaluate(machineCode);
    mExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
    int index = mIdentifierNode->GetIndex();
    machineCode.PopAndStore(index);
}

TimesEqualsStatementNode::~TimesEqualsStatementNode() {
    MSG("PlusEqualsStatementNode Deleting IdentifierNode and ExpressionNode\n");
    delete mIdentifierNode;
    delete mExpressionNode;
}

// CoutStatementNode
void CoutStatementNode::addExpression(ExpressionNode *en) {
    mExpressionNodes.push_back(en);
}

void CoutStatementNode::Interpret() {
    std::vector<ExpressionNode*>::iterator it;
    int i = 0;
    for (it = mExpressionNodes.begin(); it != mExpressionNodes.end(); it++,i++ ) {
        if (mExpressionNodes[i]) {
            std::cout << mExpressionNodes[i]->Evaluate() << " ";
        } else {
            std::cout << "\n";
        }
    }
}

void CoutStatementNode::Code(InstructionsClass &machineCode) {
    std::vector<ExpressionNode*>::iterator it;
    int i = 0;
    for (it = mExpressionNodes.begin(); it != mExpressionNodes.end(); it++,i++ ) {
        if (mExpressionNodes[i]) {
            mExpressionNodes[i]->CodeEvaluate(machineCode);
            machineCode.PopAndWrite();
        } else {
            machineCode.WriteEndl();
        }
    }
}

CoutStatementNode::~CoutStatementNode() {
    MSG("CoutStatementNode Deleting ExpressionNodes\n");
    std::vector<ExpressionNode*>::iterator it;
    int i = 0;
    for (it = mExpressionNodes.begin(); it != mExpressionNodes.end(); it++,i++ ) {
        MSG("CoutStatementNode Deleted ExpressionNode\n");
        delete mExpressionNodes[i];
    }
}

// IfStatementNode
IfStatementNode::IfStatementNode(ExpressionNode *en, StatementNode *sn) {
    mExpressionNode = en;
    mStatementNode = sn;
}

void IfStatementNode::Interpret() {
    if (mExpressionNode->Evaluate() != 0) {
        mStatementNode->Interpret();
    }
}

void IfStatementNode::Code(InstructionsClass &machineCode) {
    mExpressionNode->CodeEvaluate(machineCode);
    unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char * address1 = machineCode.GetAddress();
    mStatementNode->Code(machineCode);
    unsigned char * address2 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress, (int)(address2-address1));
}

IfStatementNode::~IfStatementNode() {
    delete mExpressionNode;
    delete mStatementNode;
}

// WhileStatementNode
WhileStatementNode::WhileStatementNode(ExpressionNode *en, StatementNode *sn) {
    mExpressionNode = en;
    mStatementNode = sn;
}

void WhileStatementNode::Interpret() {
    while (mExpressionNode->Evaluate() != 0) {
        mStatementNode->Interpret();
    }
}
void WhileStatementNode::Code(InstructionsClass &machineCode) {
    unsigned char * address1 = machineCode.GetAddress();
    mExpressionNode->CodeEvaluate(machineCode);
    unsigned char * InsertAddressToSkip = machineCode.SkipIfZeroStack();
    unsigned char * address2 = machineCode.GetAddress();
    mStatementNode->Code(machineCode);
    unsigned char * InsertAddressToJump = machineCode.Jump();
    unsigned char * address3 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddressToSkip, (int)(address3-address2));
    machineCode.SetOffset(InsertAddressToJump, (int)(address1-address3));
}

WhileStatementNode::~WhileStatementNode() {
    delete mExpressionNode;
    delete mStatementNode;
}

// ExpressionNode
ExpressionNode::~ExpressionNode() {
    MSG("Deleting ExpressionNode\n");
}

// IntegerNode
IntegerNode::IntegerNode(int i ) {
    mInt = i;
}

void IntegerNode::CodeEvaluate(InstructionsClass &machineCode) {
    machineCode.PushValue(mInt);
}

// IdentifierNode
IdentifierNode::IdentifierNode(SymbolTableClass *ms, std::string l) {
    mSymbolTable = ms;
    mLabel = l;
}

void IdentifierNode::DeclareVariable() {
    mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) {
    mSymbolTable->SetValue(mLabel,v);
}

int IdentifierNode::GetIndex() {
    return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
    return mSymbolTable->GetValue(mLabel);
}

void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode) {
    machineCode.PushVariable(this->GetIndex());
}

// BinaryOperatorNode
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right) {
    mLeftExpressionNode = left;
    mRightExpressionNode = right;
}


BinaryOperatorNode::~BinaryOperatorNode() {
    MSG("BinaryOperatorNode Deleting ExpressionNodes\n");
    delete mLeftExpressionNode;
    delete mRightExpressionNode;
}

// PlusNode
PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int PlusNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() + mRightExpressionNode->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}

// MinusNode
MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int MinusNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() - mRightExpressionNode->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

// TimesNode
TimesNode::TimesNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int TimesNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() * mRightExpressionNode->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
}

// DivideNode
DivideNode::DivideNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int DivideNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() / mRightExpressionNode->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

// LessNode
LessNode::LessNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int LessNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() < mRightExpressionNode->Evaluate();
}

void LessNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

// LessEqualNode
LessEqualNode::LessEqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int LessEqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() <= mRightExpressionNode->Evaluate();
}

void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

// GreaterNode
GreaterNode::GreaterNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int GreaterNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() > mRightExpressionNode->Evaluate();
}

void GreaterNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

// GreaterEqualNode
GreaterEqualNode::GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int GreaterEqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() >= mRightExpressionNode->Evaluate();
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}

// EqualNode
EqualNode::EqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int EqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() == mRightExpressionNode->Evaluate();
}

void EqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

// NotEqualNode
NotEqualNode::NotEqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int NotEqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() != mRightExpressionNode->Evaluate();
}

void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
}

// AndNode
AndNode::AndNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int AndNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() && mRightExpressionNode->Evaluate();
}

void AndNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

// OrNode
OrNode::OrNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int OrNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() || mRightExpressionNode->Evaluate();
}

void OrNode::CodeEvaluate(InstructionsClass &machineCode) {
    mLeftExpressionNode->CodeEvaluate(machineCode);
    mRightExpressionNode->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}

// BitwiseAndNode
BitwiseAndNode::BitwiseAndNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

int BitwiseAndNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() & mRightExpressionNode->Evaluate();
}
