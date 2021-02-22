#include "node.h"

Node::~Node() {

}

// StartNode
StartNode::StartNode(ProgramNode *p) {
    mProgramNode = p;
}

StartNode::~StartNode() {
    delete mProgramNode;
}

// ProgramNode
ProgramNode::ProgramNode(BlockNode *b) {
    mBlockNode = b;
}

ProgramNode::~ProgramNode() {
    delete mBlockNode;
}

// BlockNode
BlockNode::BlockNode(StatementGroupNode *s) {
    mStatementGroupNode = s;
}

BlockNode::~BlockNode() {
    delete mStatementGroupNode;
}

// StatementGroupNode
void StatementGroupNode::addStatement(StatementNode *p) {
    mStatementNodes.push_back(p);
}

StatementGroupNode::~StatementGroupNode() {
    std::vector<StatementNode*>::iterator it;
    int i = 0;
    for (it = mStatementNodes.begin(); it != mStatementNodes.end(); it++,i++ ) {
        delete mStatementNodes[i];
        }
}

// DeclarationStatementNode
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *p) {
    mIdentifierNode = p;
}

DeclarationStatementNode::~DeclarationStatementNode() {
    delete mIdentifierNode;
}

// AssignmentStatementNode
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en) {
    mIdentifierNode = in;
    mExpressionNode = en;
}

AssignmentStatementNode::~AssignmentStatementNode() {
    delete mIdentifierNode;
    delete mExpressionNode;
}

// CoutStatementClass
CoutStatementClass::CoutStatementClass(ExpressionNode *en) {
    mExpressionNode = en;
}

// ExpressionNode
ExpressionNode::~ExpressionNode() {
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
    delete mLeftExpressionNode;
    delete mRightExpressionNode;
}

// PlusNode
int PlusNode::Evaluate() {
    return mLeftExpressionNode->Evaluate() + mRightExpressionNode->Evaluate();
}

PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right) {}
