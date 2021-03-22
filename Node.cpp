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

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("DeclarationStatementNode Deleting IdentifierNode\n");
    delete mIdentifierNode;
}

// AssignmentStatementNode
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

void AssignmentStatementNode::Interpret() {
    mIdentifierNode->SetValue(mExpressionNode->Evaluate());
}

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("AssignmentStatementNode Deleting IdentifierNode and ExpressionNode\n");
    delete mIdentifierNode;
    delete mExpressionNode;
}

// CoutStatementNode
CoutStatementNode::CoutStatementNode(ExpressionNode *en) {
    mExpressionNode = en;
}

void CoutStatementNode::Interpret() {
    std::cout << mExpressionNode->Evaluate() << "\n";
}

CoutStatementNode::~CoutStatementNode() {
    MSG("CoutStatementNode Deleting ExpressionNode\n");
    delete mExpressionNode;
}

// ExpressionNode
ExpressionNode::~ExpressionNode() {
    MSG("Deleting ExpressionNode\n");
}

// IntegerNode
IntegerNode::IntegerNode(int i ) {
    mInt = i;
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
int PlusNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() + mRightExpressionNode->Evaluate();
}

PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// MinusNode
int MinusNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() - mRightExpressionNode->Evaluate();
}

MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// TimesNode
int TimesNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() * mRightExpressionNode->Evaluate();
}

TimesNode::TimesNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// DivideNode
int DivideNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() / mRightExpressionNode->Evaluate();
}

DivideNode::DivideNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// LessNode
int LessNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() < mRightExpressionNode->Evaluate();
}

LessNode::LessNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// LessEqualNode
int LessEqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() <= mRightExpressionNode->Evaluate();
}

LessEqualNode::LessEqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// GreaterNode
int GreaterNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() > mRightExpressionNode->Evaluate();
}

GreaterNode::GreaterNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// GreaterEqualNode
int GreaterEqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() >= mRightExpressionNode->Evaluate();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// EqualNode
int EqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() == mRightExpressionNode->Evaluate();
}

EqualNode::EqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}

// NotEqualNode
int NotEqualNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() != mRightExpressionNode->Evaluate();
}

NotEqualNode::NotEqualNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}


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

WhileStatementNode::~WhileStatementNode() {
    delete mExpressionNode;
    delete mStatementNode;
}
