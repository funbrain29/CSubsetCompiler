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
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;

class Node {
    private:
    public:
    virtual ~Node();
    virtual void Interpret() = 0;
};

class StartNode: public Node {
    private:
    ProgramNode *mProgramNode;

    public:
    StartNode(ProgramNode *p);
    virtual void Interpret();
    virtual ~StartNode();
};

class ProgramNode: public Node {
    private:
    BlockNode *mBlockNode;

    public:
    ProgramNode(BlockNode *b);
    virtual void Interpret();
    virtual ~ProgramNode();
};

class StatementNode: public Node {
    private:
    public:
};

class BlockNode: public StatementNode {
    private:
    StatementGroupNode *mStatementGroupNode;

    public:
    BlockNode(StatementGroupNode *s);
    virtual void Interpret();
    virtual ~BlockNode();
};

class StatementGroupNode: public Node {
    private:
    std::vector<StatementNode*> mStatementNodes;

    public:
    void addStatement(StatementNode *p);
    virtual void Interpret();
    ~StatementGroupNode();
};


class DeclarationStatementNode: public StatementNode {
    private:
    IdentifierNode *mIdentifierNode;
    public:
    DeclarationStatementNode(IdentifierNode *p);
    virtual void Interpret();
    ~DeclarationStatementNode();
};

class AssignmentStatementNode: public StatementNode {
    private:
    IdentifierNode *mIdentifierNode;
    ExpressionNode *mExpressionNode;

    public:
    AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en);
    virtual void Interpret();
    virtual ~AssignmentStatementNode();
};

class CoutStatementNode: public StatementNode {
    private:
    ExpressionNode *mExpressionNode;

    public:
    CoutStatementNode(ExpressionNode *en);
    virtual void Interpret();
    ~CoutStatementNode();
};

class IfStatementNode: public StatementNode {
    private:
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;

    public:
    IfStatementNode(ExpressionNode *en, StatementNode *sn);
    virtual void Interpret();
    ~IfStatementNode();
};

class WhileStatementNode: public StatementNode {
    private:
    ExpressionNode *mExpressionNode;
    StatementNode *mStatementNode;


    public:
    WhileStatementNode(ExpressionNode *en, StatementNode *sn);
    virtual void Interpret();
    ~WhileStatementNode();
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

class MinusNode: public BinaryOperatorNode {
    public:
    MinusNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class TimesNode: public BinaryOperatorNode {
    public:
    TimesNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class DivideNode: public BinaryOperatorNode {
    public:
    DivideNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class LessNode: public BinaryOperatorNode {
    public:
    LessNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class LessEqualNode: public BinaryOperatorNode {
    public:
    LessEqualNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class GreaterNode: public BinaryOperatorNode {
    public:
    GreaterNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class GreaterEqualNode: public BinaryOperatorNode {
    public:
    GreaterEqualNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class EqualNode: public BinaryOperatorNode {
    public:
    EqualNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

class NotEqualNode: public BinaryOperatorNode {
    public:
    NotEqualNode(ExpressionNode * left, ExpressionNode * right);
    int Evaluate();
};

#endif
