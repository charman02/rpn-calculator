/*
 *  DatumStack.cpp
 *  Charles Man
 *  2/27/23
 *
 *  CalcYouLater
 *
 *  Purpose: This is the class implementation for DatumStack. It contains
 *           all definitions for both public and private member functions of
 *           the class.
 *
 */

#include "DatumStack.h"
#include <iostream>

using namespace std;

/* 
 * default constructor
 * purpose: initializes an empty stack
 * parameters: none
 * returns: none
 */
DatumStack::DatumStack() {}

/* 
 * second constructor
 * purpose: initialize a stack of given Datum array elements and size
 * parameters: Datum array and size integer
 * returns: none
 */
DatumStack::DatumStack(Datum arr[], int size) {
    // call default constructor if size is 0
    if (size == 0) {
        DatumStack();
    }
    // otherwise, initialize stack with given Datum array elements
    else {
        for (int i = 0; i < size; i++) {
            stack.push_back(arr[i]);
        }
    }
}

/* 
 * isEmpty
 * purpose: determine if stack is empty
 * parameters: none
 * returns: true if stack is empty, false if not
 */
bool DatumStack::isEmpty() {
    // return true if stack is empty
    if (stack.empty()) {
        return true;
    }
    // otherwise, return false
    else {
        return false;
    }
}

/* 
 * clear
 * purpose: makes current stack into empty stack
 * parameters: none
 * returns: none
 */
void DatumStack::clear() {
    stack.clear();
}

/* 
 * size
 * purpose: determine size of stack
 * parameters: none
 * returns: number of Datum elements on stack
 */
int DatumStack::size() {
    return stack.size();
}

/* 
 * top
 * purpose: determine top element on stack
 * parameters: none
 * returns: top Datum element on stack
 */
Datum DatumStack::top() {
    // throw runtime error exception if stack is empty
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }
    
    return stack.back();
}

/* 
 * pop
 * purpose: removes top element on stack
 * parameters: none
 * returns: none
 */
void DatumStack::pop() {
    // throw runtime error exception if stack is empty
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }
    stack.pop_back();
}

/* 
 * push
 * purpose: inserts Datum element on top of stack
 * parameters: none
 * returns: none
 */
void DatumStack::push(Datum data) {
    stack.push_back(data);
}