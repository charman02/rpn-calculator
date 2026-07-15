/*
 *  DatumStack.h
 *  Charles Man
 *  2/27/23
 *
 *  CalcYouLater
 *
 *  Purpose: This is the class interface for DatumStack. It contains all
 *           of the public and private member functions and variables for the
 *           class. The public members can be accessed by the user, while the
 *           private members can only be accessed by other members of the
 *           class. DatumStack.h includes the header file for the Datum class.
 *
 */

#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__

#include "Datum.h"
#include <list>

class DatumStack {
public:
    // constructors
    DatumStack();
    DatumStack(Datum arr[], int size);
    
    // functions
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum data);

private:
    std::list<Datum> stack;

};

#endif