#include "node.h"

Node::~Node() {
    std::cout << "Deleting Node\n";
}

// StartNode
StartNode::StartNode(ProgramNode *p) {
    mProgramNode = p;
}

StartNode::~StartNode() {
    std::cout << "StartNode Deleting ProgramNode\n";
    delete mProgramNode;
}

// ProgramNode
ProgramNode::ProgramNode(BlockNode *b) {
    mBlockNode = b;
}

ProgramNode::~ProgramNode() {
    std::cout << "ProgramNode Deleting BlockNode\n";
    delete mBlockNode;
}

// BlockNode
BlockNode::BlockNode(StatementGroupNode *s) {
    mStatementGroupNode = s;
}

BlockNode::~BlockNode() {
    std::cout << "BlockNode Deleting StatementGroupNode\n";
    delete mStatementGroupNode;
}

// StatementGroupNode
void StatementGroupNode::addStatement(StatementNode *p) {
    mStatementNodes.push_back(p);
}

StatementGroupNode::~StatementGroupNode() {
    std::vector<StatementNode*>::iterator it;
    int i = 0;
    std::cout << "StatementGroupNode Deleting StatementNodes\n";
    for (it = mStatementNodes.begin(); it != mStatementNodes.end(); it++,i++ ) {
    std::cout << "StatementGroupNode Deleted StatementNode\n";
        delete mStatementNodes[i];
        }
}

// DeclarationStatementNode
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *p) {
    mIdentifierNode = p;
}

DeclarationStatementNode::~DeclarationStatementNode() {
    std::cout << "DeclarationStatementNode Deleting IdentifierNode\n";
    delete mIdentifierNode;
}

// AssignmentStatementNode
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

AssignmentStatementNode::~AssignmentStatementNode() {
    std::cout << "AssignmentStatementNode Deleting IdentifierNode and ExpressionNode\n";
    delete mIdentifierNode;
    delete mExpressionNode;
}

// CoutStatementNode
CoutStatementNode::CoutStatementNode(ExpressionNode *en) {
    mExpressionNode = en;
}

CoutStatementNode::~CoutStatementNode() {
    std::cout << "CoutStatementNode Deleting ExpressionNode\n";
    delete mExpressionNode;
}

// ExpressionNode
ExpressionNode::~ExpressionNode() {
    std::cout << "Deleting ExpressionNode\n";
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
    std::cout << "BinaryOperatorNode Deleting ExpressionNodes\n";
    delete mLeftExpressionNode;
    delete mRightExpressionNode;
}

// PlusNode
int PlusNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() + mRightExpressionNode->Evaluate();
}

PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}
