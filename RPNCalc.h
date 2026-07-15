/*
 *  RPNCalc.h
 *  Charles Man
 *  2/27/23
 *
 *  CalcYouLater
 *
 *  Purpose: This is the class interface for RPNCalc. It contains all
 *           of the public and private member functions and variables for the
 *           class. The public members can be accessed by the user, while the
 *           private members can only be accessed by other members of the
 *           class. RPNCalc.h includes the header file for the DatumStack
 *           class.
 *
 */

#ifndef __RPNCALC_H__
#define __RPNCALC_H__

#include "DatumStack.h"
#include <string>

class RPNCalc {
public:
    //constructor
    RPNCalc();

    //destructor
    ~RPNCalc();

    void run();

private:

    DatumStack calcStack;

    void run_helper(std::istream &is);
    bool got_int(std::string s, int *resultp);
    void pushNum(int num);
    void pushTrue();
    void pushFalse();
    void pushNot();
    void print();
    void clear();
    void drop();
    void dup();
    void swap();
    void operation(std::string symbol);
    void operate(int second, int first, std::string symbol);
    void compare(int second, int first, std::string symbol);
    std::string parseRString(std::istream &input);
    void pushRString(std::string rstring);
    void exec();
    void file();
    void if_command();
    Datum top_stack();
};

#endif