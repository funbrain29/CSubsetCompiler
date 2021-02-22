#ifndef NODE
#define NODE

#include "Symbol.h"

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class DeclarationNode;
class IdentifierNode;
class AssignmentStatementNode;
class AssignmentNode;
class ExpressionNode;
class CoutStatementNode;
class IntegerNode;
class BinaryOperatorNode;
class PlusNode;

class Node {
    private:
    public:
    virtual ~Node();
};

class StartNode: public Node {
    private:
    ProgramNode *mProgramNode;

    public:
    StartNode(ProgramNode *p);
    virtual ~StartNode();
};

class ProgramNode: public Node {
    private:
    BlockNode *mBlockNode;

    public:
    ProgramNode(BlockNode *b);
    virtual ~ProgramNode();
};

class BlockNode: public Node {
    private:
    StatementGroupNode *mStatementGroupNode;

    public:
    BlockNode(StatementGroupNode *s);
    virtual ~BlockNode();
};

class StatementGroupNode: public Node {
    private:
    std::vector<StatementNode*> mStatementNodes;

    public:
    void addStatement(StatementNode *p);
    ~StatementGroupNode();
};

class StatementNode: public Node {
    private:
    public:
};

class DeclarationStatementNode: public StatementNode {
    private:
    IdentifierNode *mIdentifierNode;
    public:
    DeclarationStatementNode(IdentifierNode *p);
    ~DeclarationStatementNode();
};

class AssignmentStatementNode: public StatementNode {
    private:
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

    public:
    AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en);
    virtual ~AssignmentStatementNode();
};

class CoutStatementClass: public StatementNode {
    private:
    ExpressionNode *mExpressionNode;

    public:
    CoutStatementClass(ExpressionNode *en);
};

class ExpressionNode {
    private:
    public:
    virtual int Evaluate() = 0;
    virtual ~ExpressionNode();
};

class IntegerNode: public ExpressionNode {
    private:
    int mInt;

    public:
    IntegerNode(int i);
    int Evaluate() {return mInt;};
};

class IdentifierNode: public ExpressionNode {
    private:
    SymbolTableClass *mSymbolTable;
    std::string mLabel;

    public:
    IdentifierNode(SymbolTableClass *ms, std::string l);
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();
};

class BinaryOperatorNode: public ExpressionNode {
    protected:
    ExpressionNode *mLeftExpressionNode;
    ExpressionNode *mRightExpressionNode;
    public:
    BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
    ~BinaryOperatorNode();
};

class PlusNode: public BinaryOperatorNode {
    public:
    PlusNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

#endif
