//
// Created by mohamad on 30/12/2019.
//

#include "Expression.h"
#include "stack"
#include "map"
#include "SymbolTable.h"

#ifndef FLIGHTGEAR_INTERPRETER_H
#define FLIGHTGEAR_INTERPRETER_H


class BinaryOperator : public Expression {
protected:
    Expression *left{};
    Expression *right{};

public:
    BinaryOperator() = default;

    double calculate() override = 0;
    ~BinaryOperator() override{
        delete this->left;
        delete this->right;
    }
};

class Plus : public BinaryOperator{
public:
    Plus(Expression *leftExp, Expression *rightExp);
    double calculate() override;
};

class Minus : public BinaryOperator{
public:
    Minus(Expression *leftExp, Expression *rightExp);
    double calculate() override;
};

class Mul : public BinaryOperator{
public:
    Mul(Expression *leftExp, Expression *rightExp);
    double calculate() override;
};

class Div : public BinaryOperator{
public:
    Div(Expression *leftExp, Expression *rightExp);
    double calculate() override;
};


class Value : public Expression {
private:
    mutable double val;
public:
    explicit Value(double value);
    double calculate() override;
};

class Variable : public Expression {
private:
    string name;
    double value;
public:
    Variable(string s,double v){
        this->name = s;
        this->value = v;
    }
    //create operator functions that class will understand
    Variable& operator ++();
    Variable& operator --();
    Variable& operator +=(double add);
    Variable& operator -=(double sub);
    Variable& operator ++(int);
    Variable& operator --(int);
    double calculate() override;

};

class UnaryOperator : public Expression {
protected:
    Expression *exp{};

public:
    UnaryOperator() = default;

    double calculate() override = 0;

    ~UnaryOperator() override {
        delete this->exp;
    }
};

class UPlus : public UnaryOperator {
public:
    explicit UPlus(Expression *exp1);
    double calculate() override;
};

class UMinus : public UnaryOperator {
    double calculate() override;
public:
    explicit UMinus(Expression *exp1);
};

//----------------------------------------PART 2-----------------------------------------//

class Interpreter {
private:
    //The class's Field.
    stack<double> numericStack;
    stack<char> operatorStack;
    map<string, pair<string,double>> setV = SymbolTable::symTable;
    stack<Expression*> expStack;
public:
    //**indepth explanation is in the .cpp file**//
    //----------------Supporting Functions----------------------------------------------

    //a supporting function for setVariables that checks if text has ';'.
    bool hasSemiColon(const string& has);

    //checks if the expression has an equal number of opening and closing brackets.
    static bool hasLegalBrackets(const string &has);

    //returns a new Expression* created by the given values and an operator
    static Expression * newExp(double x, double y, char op);

    //returns a new Expression* by a new value and another expression and an operator
    //and in the end return the final expression to calculate.
    static Expression *newExp2(double x, Expression *ex, char op);

    //checks if there isn't a "-variable" - a minus before variable in the expression
    static bool legalVariableOperation(const string &has);

    //this function creates a new expression made of 2 expressions and an operator
    static Expression *newExp3(Expression *ex1, Expression *ex2, char op);

    //check if given variable is in the variable map
    bool checkVars(const string &exp);

    //checks if given chat is an operator
    bool isOp(const char &op);

    //checks if we have to operators near each other.
    bool illegalOperations(const string &exp);
    //-------------------------------------Main Functions---------------------------------
    //interprets the given string into an expression, function returns pointer to an expression
    Expression *interpret(const string& exp);

    //set the variables, for example x=5;y=10. will give an x in the map the value "5", and y the value 10.
    //have to take into consideration the validity of the input
    void setVariables(const string& setVars);
};

#endif //FLIGHTGEAR_INTERPRETER_H
