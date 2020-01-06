//
// Created by mohamad on 30/12/2019.
//

#ifndef FLIGHTGEAR_EXPRESSION_H
#define FLIGHTGEAR_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};


#endif //FLIGHTGEAR_EXPRESSION_H
