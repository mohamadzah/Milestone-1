//
// Created by mohamad on 30/12/2019.
//

#include "Interpreter.h"

//
// Created by Mohamad Zahalka on 11/11/2019.
//  ID 207886581
//

#include <iostream>
#include "Interpreter.h"
#include "stdexcept"
#include "sstream"
#define MINUS '-'
#define PLUS '+'
#define MULT '*'
#define SUB '/'

using namespace std;

// UnaryOperator subclasses
UMinus ::UMinus(Expression *exp1) {
    this->exp = exp1;
}
//return -1 * val
double UMinus ::calculate() {
    return  (this->exp->calculate()) * (-1);
}

UPlus ::UPlus(Expression *exp1) {
    this->exp = exp1;
}
//come back to this
double UPlus ::calculate() {
    return  (this->exp->calculate());
}

//BinaryOperator and subclasses
//plus class
Plus ::Plus(Expression *leftExp, Expression *rightExp) {
    this->left = leftExp;
    this->right = rightExp;
}
//return addition operation
double Plus ::calculate() {
    return (this->right->calculate()) + (this->left->calculate());
}
//minus class
Minus ::Minus(Expression *leftExp, Expression *rightExp) {
    this->right = rightExp;
    this->left = leftExp;
}
//return subtracting operation
double Minus ::calculate() {
    return (this->left->calculate()) - (this->right->calculate());
}

//Multiplication class
Mul ::Mul(Expression *leftExp, Expression *rightExp) {
    this->right = rightExp;
    this->left = leftExp;
}
//return multiplication operation
double Mul ::calculate() {
    return this->left->calculate() * this->right->calculate();
}

//Divide class
Div ::Div(Expression *leftExp, Expression *rightExp) {
    this->right = leftExp;
    this->left = rightExp;
}
//divide calulcation, take into consideration we cant divide by 0
double Div ::calculate() {
    if (this->right->calculate() != 0) {
        return this->left->calculate() / this->right->calculate();
    } else {
        cerr << "division by zero" << endl;
        exit(1);
    }
}


// Value class
Value ::Value(double value) {
    this->val = value;
}
//return value
double Value ::calculate() {
    return this->val;
}

//Variable class and all operator overloading functions
//creating operations for class to understand ++, -- etc.
Variable& Variable ::operator++() {
    this->value++;
    return *this;
}

Variable& Variable ::operator--() {
    this->value--;
    return *this;
}

Variable& Variable ::operator+=(double add) {
    this->value = this->value + add;
    return *this;
}

Variable& Variable ::operator-=(double sub) {
    this->value = this->value - sub;
    return *this;
}

Variable& Variable ::operator++(int) {
    this->value++;
    return *this;
}

Variable&  Variable ::operator--(int) {
    this->value--;
    return *this;
}

double Variable ::calculate() {
    return this->value;
}

//----------------------------------------PART 2-------------------------------------

//--------------------**Main functions**----------------------

//return an expression pointer created with the given string.
Expression *Interpreter::interpret(const string& exp) {

    //we check if for every "(" we have a ")"
    if (!hasLegalBrackets(exp)) {
        if (exp[0] == MINUS && !isdigit((exp[1]))) {
            cerr << "Invalid Format" << endl;
        }
    }
    //if it returns false, that means the form is illegal and throw error.
    //else continue
 //   if (!legalVariableOperation(exp)) {
//        cerr <<  "Invalid Format" << endl;
 //   }

    if (!illegalOperations(exp)) {
        cerr <<  "Illegal expression!" << endl;
    }
    //we proceed
    //instead of returning an answer, create an expression depending on the current numbers and operators we have
    //do a bunch of if's and create an expression , then return a pointer to that expression.
    int iter = 0, negativeVal = 0, countNums = 0;
    for (iter = 0; iter < exp.length(); iter++) {
        if(exp[iter] == ' ') {
            continue;
        }
        //check if the current token is a bracket, if yes push it to the operator stack.
        //because brackets are important for the order of the mathematical expression.
        //check if current token is an opening bracket.
        if(exp[iter] == '(') {
            operatorStack.push(exp[iter]);
        } else
            //check if we have a digit || a '-' and check if its an operator or means -1
        if(isdigit(exp[iter]) || exp[iter] == MINUS) {
            double d = 0;
            int temp = iter;
            int c = 0;
            //we check if we can reach the iter++ position
            //we check if current is - and next is digit, so we know that it is a - for a digit and not an operator
            //we multiply number by -1 and continue so we dont go over same number next loop round.
            if (temp+1 <= exp.length()) {
                if((exp[iter] == MINUS && isdigit(exp[temp+1])) || (exp[iter] == MINUS && isalpha(exp[temp+1]))) {
                    if (temp+2 <= exp.length() && (exp[iter] == MINUS && isdigit(exp[temp+1]))) {
                        if (exp[temp+2] != ')') {
                            while (isdigit(exp[temp + 1]) && temp + 1 < exp.length()) {
                                d = (exp[temp + 1] - '0') + (d * 10);
                                temp++;
                            }
                        } else {
                            operatorStack.push(MINUS);
                            continue;
                        }
                    }
                    if ((exp[iter] == MINUS && isalpha(exp[iter+1]))) {
                        if ((!isalpha(exp[iter-1]) && !isdigit(exp[iter-1]))) {
                            string tempx;
                            while (!isOp(exp[iter+1]) && (exp[iter+1] == '_' || isalpha(exp[iter+1]) || isdigit(exp[iter+1]))) {
                                tempx += exp[iter+1];
                                iter++;
                            }
                            iter--;
                            if (!checkVars(tempx)) {
                                cerr << "Variable not set!" << endl;
                                exit(1);
                            }
                            for (auto const &x : setV) {
                                if (tempx == x.second.first) {
                                    d = x.second.second;
                                    d *= -1;
                                    numericStack.push(d);
                                    continue;
                                }
                                //maybe its a variable not derived from simulator
                                if (tempx == x.first) {
                                    d = x.second.second;
                                    d *= -1;
                                    numericStack.push(d);
                                    continue;
                                }
                            }
                        } else {
                            operatorStack.push(MINUS);
                            continue;
                        }
                    }
                    //check if we have a . because if we have a value of type double.
                    if(exp[temp+1] == '.' ) {
                        double ad = 0;
                        temp++;
                        c++;
                        //while we have a digit we continue.
                        while(isdigit(exp[temp+1]) && temp+1 < exp.length()) {
                            ad = ad + (exp[temp+1] - '0')  * 0.10;
                            temp++;
                            c++;
                        }
                        d+=ad;
                        d*=-1;
                        countNums++;
                        iter = temp++;
                        iter++;
                        //push the value to stack.
                        numericStack.push(d);
                        continue;
                    }
                    d*=-1;
                    countNums++;
                    iter++;
                    //numericStack.push(d);
                    continue;
                }
            }
            //check if '-(' or -((, which usually means multipication by -1
            //check the format and decide if it is a - to multiply by -1 or operator
            if (temp+1 <= exp.length()) {
                if (exp[iter] == '-' && exp[temp + 1] == '(') {
                    if (temp - 1 >= 0 || (exp[temp] == MINUS && temp == 0)) {
                        if ((exp[temp] == '-' && temp == 0)) {
                            countNums++;
                            negativeVal++;
                            continue;
                        }
                        //if the previous value wasnt a number and we didnt have something like 2-(5*5)
                        //we understand that the - means a -( == -1* and not operator
                        if (!isdigit(exp[temp - 1])) {
                            countNums++;
                            negativeVal++;
                            continue;
                        } else {
                            //if operator push to operator stack
                            operatorStack.push(MINUS);
                            continue;
                        }
                    } else {
                        countNums++;
                        negativeVal++;
                        continue;
                    }
                }
            }
            //check if the numbers in the input are of int type or double, (has .0 for example)
            int temp2 = iter;
            if (temp2+1 <= exp.length()) {
                c = 0;
                //if we find a number we convert it.
                //if we find a . that means there might be more digits after the .
                if(isdigit(exp[temp2]) && exp[temp2+1] == '.') {
                    while (isdigit(exp[temp2]) && temp2 + 1 <= exp.length()) {
                        d = (exp[temp2] - '0') + (d * 10);
                        temp2++;
                    }
                    //if we find . we check values after .
                    if (exp[temp2] == '.') {
                        double val = 0;
                        while(isdigit(exp[temp2 + 1])) {
                            val = (exp[temp2 + 1] - '0') * (0.10);
                            temp2++;
                            c++;
                        }
                        d = d + val;
                        countNums++;
                        iter = temp2++;
                        //push a value into the numbers stack
                        numericStack.push(d);
                        continue;
                    }
                }
            }
            //if none of the cases above occur, we simply have an single digit number, convert and push
            while(iter < exp.length() && isdigit(exp[iter])) {
                d = (exp[iter] - '0') + (d * 10);
                iter++;
            }
            iter--;
            countNums++;
            numericStack.push(d);
        } else
            //check if current value is an alphabetical value.
        if(isalpha((exp[iter])) || exp[iter] == '_') {
            string temp;
            /*while our text is a variable, we add to the temp string to create the full variable name
             * then we check if it exists in the map, if not that means we are using a variable that is
             * not set, so we throw an error, if not we proceed to push the value of the variable to the
             * number stack. */
            int h = iter;
            //make a string made out of variable name.
            while (!isOp(exp[iter]) && (exp[iter] == '_' || isalpha(exp[iter]) || isdigit(exp[iter]))) {
                temp+= exp[iter];
                iter++;
            }
            iter--;
            if(!checkVars(temp)) {
                cerr << "Variable not set!" << temp << endl;
            }
            for(auto const& x : setV) {
                if (temp == x.second.first) {
                    numericStack.push(x.second.second);
                }
                //maybe its a variable not derived from simulator
                if (temp == x.first) {
                    numericStack.push(x.second.second);
                }
            }
        } else
            //if we reach the end of brackets
        if (exp[iter] == ')') {
            //in this loop we create an expression of the current values we have in our stacks
            //after we reached the end of a brace,
            //once we reach the end of a brace we create an expression of values
            while(!operatorStack.empty() && operatorStack.top() != '(') {
                double tempVal1, tempVal2;
                char tempOp = operatorStack.top();
                operatorStack.pop();
                tempVal1 = numericStack.top();
                numericStack.pop();
                //if we have one numeric stack, then theres a |number OPERATION (SOMETHING)|
                //if not we continue and push an expression with multiply values.
                if (numericStack.empty()) {
                    expStack.push(newExp2(tempVal1, expStack.top(), tempOp));
                    continue;
                }
                tempVal2 = numericStack.top();
                numericStack.pop();
                operatorStack.pop();
                //if we have a (SOMETHING) OPERATOR (SOMETHING) push two expressions and a operator
                if (numericStack.empty() && !operatorStack.empty() && operatorStack.top() != ')'
                    && operatorStack.top() != '(') {
                    expStack.push(newExp3(newExp(tempVal1,tempVal2,tempOp), expStack.top(), operatorStack.top()));
                    operatorStack.pop();
                    continue;
                }
                if(tempOp == SUB || tempOp == MINUS) {
                    expStack.push(newExp(tempVal2,tempVal1,tempOp));
                    continue;
                }
                //else we push a normal expression created by two values and an operator
                expStack.push(newExp(tempVal1,tempVal2,tempOp));
            }
            //check whether our operatorstack is empty to pop the extra
            if (!operatorStack.empty()) {
                operatorStack.pop();
            }
            //check if we had a "-(" in our expression, if yes we multiply by -1
            if(negativeVal > 0 && expStack.empty()) {
                expStack.push(newExp(-1, numericStack.top(), '*'));
                numericStack.pop();
                negativeVal--;
            }
            //check if we had a "-(" in our expression, if yes we multiply by -1 (another case)
            if(negativeVal > 0 && !expStack.empty()) {
                expStack.push(newExp2(-1, expStack.top(), '*'));
                negativeVal--;
            }
        } else {
            //we push operator to stack
            operatorStack.push(exp[iter]);
        }
    }
    //if we have any remaining operators, that means we had an operator outside of the braces
    //we continue and create the full expression.
    int i = 0, flag = 0;
    while (i < exp.length()) {
        if (exp[i] == ')' || exp[i] == '(') {
            flag = 1;
        }
        i++;
    }
    while (!operatorStack.empty()) {
        //check if our numeric stack isn't empty
        if (!numericStack.empty()) {
            double tempVal1;
            tempVal1 = numericStack.top();
            numericStack.pop();
            if (flag == 0) {
                if (!numericStack.empty()) {
                    double tempVal2 = numericStack.top();
                    numericStack.pop();
                    expStack.push(newExp(tempVal1,tempVal2,operatorStack.top()));
                    operatorStack.pop();
                    continue;
                }
            }
            //if we have braces, pop them
            if(operatorStack.top() == ')' || operatorStack.top() == '(' ) {
                operatorStack.pop();
            }
            //create a new expression with remaining values, and push to the expression stack.
            if (!operatorStack.empty()) {
                char tempOp = operatorStack.top();
                expStack.push(newExp2(tempVal1, expStack.top(), tempOp));
                operatorStack.pop();
            }
        }
    }
    //now all the expressions are stacked in the expression stack.
    //return expression
    auto* e = reinterpret_cast<Expression *>(expStack.top());
    return e;
}
//----------------*Supporting Functions*---------------------
//return a new expression with the given values and operator.
Expression *Interpreter::newExp(double x, double y, char op){
    if (op == PLUS) {
        return new Plus(new Value(x), new Value(y));
    }
    if (op == MINUS) {
        return new Minus(new Value(x), new Value(y));
    }
    if (op == MULT) {
        return new Mul(new Value(x), new Value(y));
    }
    return new Div(new Value(x), new Value(y));
}
//return a new expression with the given value, expression and operator.
Expression *Interpreter::newExp2(double x, Expression* ex, char op){
    if (op == PLUS) {
        return new Plus(new Value(x), ex);
    }
    if (op == MINUS) {
        return new Minus(new Value(x), ex);
    }
    if (op == MULT) {
        return new Mul(new Value(x), ex);
    }
    return new Div( new Value(x), ex);
}
//create a new expression with given 2 expressions and an operator.
Expression *Interpreter::newExp3(Expression* ex1, Expression* ex2, char op){
    if (op == PLUS) {
        return new Plus(ex1, ex2);
    }
    if (op == MINUS) {
        return new Minus(ex1, ex2);
    }
    if (op == MULT) {
        return new Mul(ex1, ex2);
    }
    return new Div(ex1, ex2);
}
//check if string has a ';'
bool Interpreter::hasSemiColon(const string &has) {
    int flag = 0;
    for(char ha : has) {
        if(ha == ';') {
            flag = 1;
        }
    }
    return flag == 1;
}
//check if brackets are legal and for each ( there is ).
bool Interpreter::hasLegalBrackets(const string &has) {
    int count = 0, count2 = 0;
    for(char ha : has) {
        if(ha == '(') {
            count++;
        }
    }
    for(char ha : has) {
        if(ha == ')') {
            count2++;
        }
    }
    //if has no brackets, but is a -3*5 for example, we have to give it a pass, and continue.
    if (has[0] == MINUS && isdigit(has[1]) && count == 0 && count2 == 0) {
        return true;
    } else
        return count == count2;
}
//checks if a minus doesnt come before variable immediately.
bool Interpreter::legalVariableOperation(const string &exp) {
    for (int i = 0; i < exp.length(); i++) {
        int temp = i;
        if (temp + 1 <= exp.length()) {
            if (exp[temp] == MINUS && isalpha(exp[temp + 1])) {
                return false;
            }
        }
    }
    return true;
}
//check if current token is an operator
bool Interpreter::isOp(const char &op) {
    return op == PLUS || op == MINUS || op == MULT || op == SUB;
}
//check if variable exists in variable map
bool Interpreter::checkVars(const string &exp) {
    for (auto const &x : setV) {
        if (exp == x.first || exp == x.second.first) {
            return true;
        }
    }
    return false;
}
//this function checks if we have an illegal math expression.
bool Interpreter::illegalOperations(const string &exp) {
    int i = 0;
    //if we have two operators infront of each other that means illegal expression
    while (i<exp.length()) {
        if (i+1 < exp.length()) {
            if(isOp(exp[i]) && isOp(exp[i+1])) {
                return false;
            }
        }
        i++;
    }
    return true;
}
