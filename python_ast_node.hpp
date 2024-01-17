#include <iostream>
#include <vector>
using namespace std;


class AstNode {
public:
    string name = "undefined";  
    string label = "undefined";

    virtual void add(AstNode* node) = 0; 
    virtual void print() const = 0;
    
    virtual ~AstNode() {}
};


// seems like a lot of repeated code.. but we need a class for every token/expression

class Prog : public AstNode {
private:
    vector<AstNode*> next;

public:
    Prog(const string& name) {
        this->name = name;
        this->label = "DeclareProg";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
        vector<AstNode*>::iterator it;
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~Prog() {
        for (const auto& i : next) {
            delete i;
        }
    }
};


class StatementsNode: public AstNode {
private:
    vector<AstNode*> next;
public:
    StatementsNode(const string& name) {
        this->name = name;
        this->label = "StatementsProgram";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~StatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class StatementNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    StatementNode(const string& name) {
        this->name = name;
        this->label = "Statement";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~StatementNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


// if
class IfStmtNode: public AstNode {
private:
    vector<AstNode*> next;
public:
    IfStmtNode(const string& name) {
        this->name = name;
        this->label = "IF-Statement";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~IfStmtNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class ElifElseNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    ElifElseNode(const string& name) {
        this->name = name;
        this->label = "Elif-Else";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ElifElseNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class ElseNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    ElseNode(const string& name) {
        this->name = name;
        this->label = "Else statement";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ElseNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class ExceptNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    ExceptNode(const string& name) {
        this->name = name;
        this->label = "ExceptNodes";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ExceptNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class FunctionStatementsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FunctionStatementsNode(const string& name) {
        this->name = name;
        this->label = "Function-Statements";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~FunctionStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class FunctionIneerStmtsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FunctionIneerStmtsNode(const string& name) {
        this->name = name;
        this->label = "Function-Ineer-Stmts";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~FunctionIneerStmtsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class FunctionCallNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FunctionCallNode(const string& name) {
        this->name = name;
        this->label = "Function Call";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
 void print() const override {
        cout << "\t" << name << " [label=\"" << label <<"\"]" << endl;
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~FunctionCallNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class FunctionOfWhileNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FunctionOfWhileNode(const string& name) {
        this->name = name;
        this->label = "Function Of While";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~FunctionOfWhileNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class FunctionOfForNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FunctionOfForNode(const string& name) {
        this->name = name;
        this->label = "Function Of For";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~FunctionOfForNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class FuncForStmtsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FuncForStmtsNode(const string& name) {
        this->name = name;
        this->label = "Func For Stmts";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~FuncForStmtsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class rangeArgsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    rangeArgsNode(const string& name) {
        this->name = name;
        this->label = "range Args";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~rangeArgsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ElifStmtNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    ElifStmtNode(const string& name) {
        this->name = name;
        this->label = "Elif-Stmt";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ElifStmtNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ElifStmtsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    ElifStmtsNode(const string& name) {
        this->name = name;
        this->label = "Elif-Stmt";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ElifStmtsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class RelationStmtNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    RelationStmtNode(const string& name) {
        this->name = name;
        this->label = "RelationStmtNode";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~RelationStmtNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class Arg : public AstNode {
private:
    vector<AstNode*> next;

public:
    Arg(const string& name) {
        this->name = name;
        this->label = "Argument";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& arg : next) {
            arg->print();
        }
    }
};


class WhileStatementsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    WhileStatementsNode(const string& name) {
        this->name = name;
        this->label = "While";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~WhileStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ForStatementsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    ForStatementsNode(const string& name) {
        this->name = name;
        this->label = "For";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ForStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ForIFStatements : public AstNode {
private:
    vector<AstNode*> next;
public:
    ForIFStatements(const string& name) {
        this->name = name;
        this->label = "For IF Statements";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ForIFStatements() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class ForElifStmt : public AstNode {
private:
    vector<AstNode*> next;
public:
    ForElifStmt(const string& name) {
        this->name = name;
        this->label = "For Elif Stmt";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ForElifStmt() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ForElifElse  : public AstNode {
private:
    vector<AstNode*> next;
public:
    ForElifElse (const string& name) {
        this->name = name;
        this->label = "For Elif Else ";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ForElifElse () {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ForElif : public AstNode {
private:
    vector<AstNode*> next;
public:
    ForElif(const string& name) {
        this->name = name;
        this->label = "For Elif Else ";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~ForElif () {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class Args : public AstNode {
private:
    vector<AstNode*> next;

public:
    Args(const string& name,const string& label) {
        this->name = name;
        this->label = label;
    }
 
    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;

        for (const auto& arg : next) {
            cout << "\t" << name << " -> " << arg->name << ";" << endl;
            arg->print();
        }
    }
};


class ArgsPrint : public AstNode {
private:
    vector<AstNode*> next;

public:
    ArgsPrint(const string& name,const string& label) {
        this->name = name;
        this->label = label;
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;

        for (const auto& arg : next) {
            cout << "\t" << name << " -> " << arg->name << ";" << endl;
            arg->print();
        }
    }
};





// Composite node for representing  BlockNode
class BlockNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    BlockNode(const string& name) {
        this->name = name;
        this->label = "Block";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~BlockNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class StmtsNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    StmtsNode(const string& name) {
        this->name = name;
        this->label = "Block-Stmts";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }

    ~StmtsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class StmtNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    StmtNode(const string& name) {
        this->name = name;
        this->label = "Block Statements";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }

    ~StmtNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class assignmentStatement : public AstNode {
private:
    vector<AstNode*> next;

public:
    assignmentStatement(const string& name) {
        this->name = name;
        this->label = "assignment";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
        // for (const auto& stmt : next) {
        //     stmt->print();
        // }
    }

    ~assignmentStatement() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};



class ForBlockStatements : public AstNode {
private:
    vector<AstNode*> next;

public:
    ForBlockStatements(const string& name) {
        this->name = name;
        this->label = "For Block Statements";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }

    ~ForBlockStatements() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};



class FunctionNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    FunctionNode(const string& name) {
        this->name = name;
        this->label = "Declare Fun";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
        vector<AstNode*>::iterator it;
        // for (it = next.begin(); it != next.end(); ++it) {
        //     // example
        //     // Func -> args
        //     // Func -> body
        //     cout << "\t" << name << " -> " << (*it)->name << ";" << endl;
        //     (*it)->print();
        // }
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~FunctionNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class IdentifierNode : public AstNode {

public:
    string value = "undefined";
    IdentifierNode(string name, string label, string value) {
        this->name = name;
        this->label = label;
        this->value = value; 
    }
    void add(AstNode* /*node*/) override {
        cerr << "Cannot add a child to a leaf node." << endl;
    }

    void print() const override {
        cout << "\t" << name << " [shape=box,label=\"" << label << ": " << value << "\"]" << endl;

    }
};


class ExpressionDivisionNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ExpressionDivisionNode(const string& name) {
        this->name = name;
        this->label = "Division ";
    } 

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
        // for (const auto& stmt : next) {
        //     stmt->print();
        // }
    }

    ~ExpressionDivisionNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ExpressionPlusNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ExpressionPlusNode(const string& name) {
        this->name = name;
        this->label = "Plus ";
    } 

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
        // for (const auto& stmt : next) {
        //     stmt->print();
        // }
    }

    ~ExpressionPlusNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ExpressionMinusNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ExpressionMinusNode(const string& name) {
        this->name = name;
        this->label = "Minus ";
    } 

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }

    ~ExpressionMinusNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ExpressionMultNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ExpressionMultNode(const string& name) {
        this->name = name;
        this->label = "Mult";
    } 

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
        
    }

    ~ExpressionMultNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class ExpressionRemainderNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ExpressionRemainderNode(const string& name) {
        this->name = name;
        this->label = "Remainder";
    } 

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
        // for (const auto& stmt : next) {
        //     stmt->print();
        // }
    }

    ~ExpressionRemainderNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class NumberNode : public AstNode {
private:
    int value;
public:
    NumberNode(string name, string label, int value) {
        this->name = name;
        this->label = label;
        this->value = value; 
    }

    void add(AstNode* /*node*/) override {
        cerr << "Cannot add a child to a leaf node." << endl;
    }

    void print() const override {
        cout << "\t" << name << " [shape=box,label=\"" << label << ": " << value << "\"]" << endl;

    }
};



class ArrayNode : public AstNode {
private:
    int value;
public:
    ArrayNode(string name, string label, int value) {
        this->name = name;
        this->label = label;
        this->value = value; 
    }

    void add(AstNode* /*node*/) override {
        cerr << "Cannot add a child to a leaf node." << endl;
    }

    void print() const override {
        cout << "\t" << name << " [shape=box,label=\"" << label << ": " << value << "\"]" << endl;

    }
};


class IntNumberNode : public AstNode {
private:
    int value;
public:
    IntNumberNode(string name, string label, int value) {
        this->name = name;
        this->label = label;
        this->value = value; 
    }

    void add(AstNode* /*node*/) override {
        cerr << "Cannot add a child to a leaf node." << endl;
    }

    void print() const override {
        cout << "\t" << name << " [shape=box,label=\"" << label << ": " << value << "\"]" << endl;

    }
};


class FloatNumberNode : public AstNode {
private:
    int value;
public:
    FloatNumberNode(string name, string label, int value) {
        this->name = name;
        this->label = label;
        this->value = value; 
    }

    void add(AstNode* /*node*/) override {
        cerr << "Cannot add a child to a leaf node." << endl;
    }

    void print() const override {
        cout << "\t" << name << " [shape=box,label=\"" << label << ": " << value << "\"]" << endl;

    }
};


class StringNode : public AstNode {
private:
    string value;
public:
    StringNode(string name, string value) {
        this->name = name;
        this->value = value; 
    }

    void add(AstNode* /*node*/) override {
        cerr << "Cannot add a child to a leaf node." << endl;
    }

    void print() const override {
        cout << "\t" << name << " [shape=box,label=\"" << "String:" << value << "\"]" << endl;

    }
};


class PassNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    PassNode(const string& name) {
        this->name = name;
        this->label = "Pass";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~PassNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class MatchStatementsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    MatchStatementsNode(const string& name) {
        this->name = name;
        this->label = " MatchStatements";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~MatchStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};



class CaseStatementsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    CaseStatementsNode(const string& name) {
        this->name = name;
        this->label = "caseStatement";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~CaseStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class CaseNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    CaseNode(const string& name) {
        this->name = name;
        this->label = "Case";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~CaseNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class FinalCaseNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    FinalCaseNode(const string& name) {
        this->name = name;
        this->label = "final case";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~FinalCaseNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};



class MatchBlockNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    MatchBlockNode(const string& name) {
        this->name = name;
        this->label = "MatchBlock";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~MatchBlockNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};



class WithBodyNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    WithBodyNode(const string& name) {
        this->name = name;
        this->label = "WithBody";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~WithBodyNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class WithStatementsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    WithStatementsNode(const string& name) {
        this->name = name;
        this->label = "WithStatements";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~WithStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class WithItemNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    WithItemNode(const string& name) {
        this->name = name;
        this->label = "WithItem";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~WithItemNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class bracketsNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    bracketsNode(const string& name) {
        this->name = name;
        this->label = "brackets";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~bracketsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class TargetNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    TargetNode(const string& name) {
        this->name = name;
        this->label = "Target";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~TargetNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class TargetInsideNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    TargetInsideNode(const string& name) {
        this->name = name;
        this->label = "TargetInsid";
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~TargetInsideNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class exprNode : public AstNode {
private:
    vector<AstNode*> next;
public:
    exprNode(const string& name) {
        this->name = name;
        this->label = "exprNode";
    }
    exprNode() {
    
    }
    void add(AstNode* node) override {
        next.push_back(node);
    }
    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
 
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }
    ~exprNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};

class ClassNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ClassNode(const string& name) {
        this->name = name;
        this->label = "Declare Class";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~ClassNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};

class ClassStatementsNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ClassStatementsNode(const string& name) {
        this->name = name;
        this->label = "Class Statements";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }

    ~ClassStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


class INTNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    INTNode(const string& name) {
        this->name = name;
        this->label = "int";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~INTNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class FloatNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    FloatNode(const string& name) {
        this->name = name;
        this->label = "float-data-type";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~FloatNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class STRNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    STRNode(const string& name) {
        this->name = name;
        this->label = "STR-data-type";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~STRNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class BoolNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    BoolNode(const string& name) {
        this->name = name;
        this->label = "bool-data-type";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~BoolNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class ListNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ListNode(const string& name) {
        this->name = name;
        this->label = "List-data-type";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~ListNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class BreakeNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    BreakeNode(const string& name) {
        this->name = name;
        this->label = "Breake";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~BreakeNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class ContinueNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ContinueNode(const string& name) {
        this->name = name;
        this->label = "Continue";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~ContinueNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class ReturnNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ReturnNode(const string& name) {
        this->name = name;
        this->label = "Return";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~ReturnNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class YieldNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    YieldNode(const string& name) {
        this->name = name;
        this->label = "Yield";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~YieldNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class GlobalNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    GlobalNode(const string& name) {
        this->name = name;
        this->label = "Global";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~GlobalNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class NonlocalNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    NonlocalNode(const string& name) {
        this->name = name;
        this->label = "Nonlocal";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~NonlocalNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class NullNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    NullNode(const string& name) {
        this->name = name;
        this->label = "Nonlocal";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<" : "<<name<<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~NullNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class TryStatementsNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    TryStatementsNode(const string& name) {
        this->name = name;
        this->label = "Try";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label <<"\"]" << endl;
       
        for (const auto& item : next) {
            cout << "\t" << name << " -> " << item->name << ";" << endl;
            item->print();
        }
    }

    ~TryStatementsNode() {
        for (const auto& arg : next) {
            delete arg;
        }
    }
};


class ExceptStatementsNode : public AstNode {
private:
    vector<AstNode*> next;

public:
    ExceptStatementsNode(const string& name) {
        this->name = name;
        this->label = "Try-Statements";
    }

    void add(AstNode* node) override {
        next.push_back(node);
    }

    void print() const override {
        cout << "\t" << name << " [label=\"" << label << "\"]" << endl;
        for (const auto& stmt : next) {
            cout << "\t" << name << " -> " << stmt->name << ";" << endl;
            stmt->print();
        }
    }

    ~ExceptStatementsNode() {
        for (const auto& stmt : next) {
            delete stmt;
        }
    }
};


// driver code (kind of...)
class AST {
private:
    AstNode* root = nullptr;
public:
    AST(AstNode* r) : root(r) {}

    ~AST() {
        if (root != nullptr) {
            delete root;
            root = nullptr;
        }
        
    }
    void Print() {
        cout << "digraph G {" << endl;
        root->print();
        cout << "}" << endl;
        
    }
};