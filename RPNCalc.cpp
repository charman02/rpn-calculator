/*
 *  RPNCalc.cpp
 *  Charles Man
 *  3/3/23
 *
 *  CalcYouLater
 *
 *  Purpose: This is the class implementation for RPNCalc. It contains
 *           all definitions for both public and private member functions of
 *           the class.
 *
 */
#include "RPNCalc.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

/* 
 * default constructor
 * purpose: initializes a RPNCalc object
 * parameters: none
 * returns: none
 */
RPNCalc::RPNCalc() {
    
}

/* 
 * destructor
 * purpose: destroys/deletes/recycles any heap-allocated data
 * parameters: none
 * returns: none
 */
RPNCalc::~RPNCalc() {
    
}

/* 
 * run
 * purpose: calls run_helper
 * parameters: none
 * returns: none
 */
void RPNCalc::run() {
    run_helper(cin);
}

/* 
 * run_helper
 * purpose: helper function for run that reads in commands from cin
 * parameters: reference to an input stream
 * returns: none
 */
void RPNCalc::run_helper(istream &is) {
    string input = "";
    int value = 0;
    bool quitted = false;

    try {
        while (not quitted and (is >> input)) {
            if (input == "#t") {
                pushTrue();
            } else if (input == "#f") {
                pushFalse();
            } else if (input == "not") {
                pushNot();
            } else if (input == "print") {
                print();
            } else if (input == "clear") {
                clear();
            } else if (input == "drop") {
                drop();
            } else if (input == "dup") {
                dup();
            } else if (input == "swap") {
                swap();
            } else if (input == "+" or input == "-" or input == "*" or input ==
            "/" or input == "mod" or input == "<" or input == ">" or input ==
            "<=" or input == ">=" or input == "==") {
                operation(input);
            } else if (input == "{") {
                pushRString(parseRString(is));
            } else if (input == "exec") {
                exec();
            } else if (input == "file") {
                file();
            } else if (input == "if"){
                if_command();
            } else if (got_int(input, &value)) {
                pushNum(value);
            } else if (input == "quit") {
                quitted = true;
                cerr << "Thank you for using CalcYouLater." << endl;
            } else {
                cerr << input << ": unimplemented\n";
            }
        }
    } catch (runtime_error &error) {
        cerr << error.what();
        run_helper(cin);
    }
}

/* 
 * got_int
 * purpose: tests whether a string can be interpreted as an integer, and if
 *          so, what the value of the integer is
 * parameters: string and pointer to location for associated integer
 * returns: true if string can be interpreted as an integer and false if not
 */
bool RPNCalc::got_int(string s, int *resultp) {
    
    // holds the first non-whitespace character after the integer
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* 
 * pushNum
 * purpose: pushes a Datum containing the given number onto the stack
 * parameters: number
 * returns: none
 */
void RPNCalc::pushNum(int num) {
    calcStack.push(Datum(num));
}

/* 
 * pushTrue
 * purpose: pushes a Datum containing the boolean true onto the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::pushTrue() {
    calcStack.push(Datum(true));
}

/* 
 * pushFalse
 * purpose: pushes a Datum containing the boolean false onto the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::pushFalse() {
    calcStack.push(Datum(false));
}

/* 
 * pushNot
 * purpose: reads and pops the top element off the stack, a boolean, and
 *          pushes a Datum with the opposite boolean onto the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::pushNot() {
    // throw a runtime error if the top element is not a boolean value
    if (not top_stack().isBool()) {
        drop();
        throw runtime_error("Error: datum_not_bool\n");
    }

    bool top_bool = top_stack().getBool();
    bool opp_bool = not top_bool;
    drop();
    calcStack.push(Datum(opp_bool));
}

/* 
 * print
 * purpose: prints the value on the top of the stack to cout followed
 *          by a new line
 * parameters: none
 * returns: none
 */
void RPNCalc::print() {
    // if top element is int
    if (top_stack().isInt()) {
        cout << top_stack().getInt() << endl;
    }
    // if top element is bool
    else if (top_stack().isBool()) {
        if (top_stack().getBool()) {
            cout << "#t" << endl;
        } else {
            cout << "#f" << endl;
        }
    }
    // otherwise, top element must be rstring or empty
    else {
        cout << top_stack().getRString() << endl;
    }
}

/* 
 * clear
 * purpose: clears the calculator, emptying the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::clear() {
    calcStack.clear();
}

/* 
 * drop
 * purpose: removes the top element on the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::drop() {
    // throw runtime error if that stack is empty
    if (calcStack.isEmpty()) {
        throw runtime_error("Error: empty_stack\n");
    }

    calcStack.pop();
}

/* 
 * dup
 * purpose: duplicates the top element on the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::dup() {
    
    calcStack.push(top_stack());
}

/* 
 * swap
 * purpose: swaps the top two elements on the stack
 * parameters: none
 * returns: none
 */
void RPNCalc::swap() {
    // throw runtime error if stack size is 0 or 1
    if (calcStack.size() < 2) {
        drop();
        throw runtime_error("Error: empty_stack\n");
    }

    Datum first = top_stack();
    drop();

    Datum second = top_stack();
    drop();

    calcStack.push(first);
    calcStack.push(second);
}

/* 
 * operation
 * purpose: calls operate or compare depending on given operator
 * parameters: an operator
 * returns: none
 */
void RPNCalc::operation(string symbol) {
    // throw runtime error if stack is empty
    if (calcStack.size() < 2) {
        drop();
        throw runtime_error("Error: empty_stack\n");
    }
    // throw runtime error if top element is not an int value
    if (not top_stack().isInt()) {
        drop();
        drop();
        throw runtime_error("Error: datum_not_int\n");
    }

    int first = top_stack().getInt();
    drop();

    if (not top_stack().isInt()) {
        drop();
        throw runtime_error("Error: datum_not_int\n");
    }

    int second = top_stack().getInt();
    drop();
    // call operate if symbol is an operator
    if (symbol == "+" or symbol == "-" or symbol == "*" or
    symbol == "/" or symbol == "mod") {
        operate(second, first, symbol);
    } 
    // call compare if symbol is logical comparison operator
    else {
        compare(second, first, symbol);
    }
}

/* 
 * operate
 * purpose: performs appropriate operation using given operator, with the
 *          first operand being the first (deeper) item on the stack
 * parameters: two integers and an operator
 * returns: none
 */
void RPNCalc::operate(int second, int first, string symbol) {
    if (symbol == "+") {
        pushNum(second + first);
    } else if (symbol == "-") {
        pushNum(second - first);
    } else if (symbol == "*") {
        pushNum(second * first);
    } else if (symbol == "/") {
        pushNum(second / first);
    } else if (symbol == "mod") {
        pushNum(second % first);
    }
}

/* 
 * compare
 * purpose: performs appropriate comparison using given operator, with the
 *          first operand being the first (deeper) item on the stack
 * parameters: two integers and an operator
 * returns: none
 */
void RPNCalc::compare(int second, int first, string symbol) {
    if (symbol == "<") {
        if (second < first) {
            pushTrue();
        } else {
            pushFalse();
        }
    } else if (symbol == ">") {
        if (second > first) {
            pushTrue();
        } else {
            pushFalse();
        }
    } else if (symbol == "<=") {
        if (second <= first) {
            pushTrue();
        } else {
            pushFalse();
        }
    } else if (symbol == ">=") {
        if (second >= first) {
            pushTrue();
        } else {
            pushFalse();
        }
    } else if (symbol == "==") {
        if (second == first) {
            pushTrue();
        } else {
            pushFalse();
        }
    }
}

/* 
 * parseRString
 * purpose: reads input from stream until all curly braces are matched or
 *          end of input is reached, and returns an rstring
 * parameters: reference to input stream
 * returns: rstring
 */
string RPNCalc::parseRString(istream &input) {
    // counts number of "{" seen, already seen 1
    int count = 1;
    string final = "{";
    string temp;
    while (count > 0) {
        input >> temp;
        // increment count if input is "{"
        if (temp == "{") {
            count++;
        }
        // decrement count if input is "}"
        else if (temp == "}") {
            count--;
        }
        final = final + " " + temp;
    }
    return final;
}

/* 
 * pushRString
 * purpose: puts given rstring inside of a Datum as a string and pushes it
 *          onto the stack
 * parameters: rstring
 * returns: none
 */
void RPNCalc::pushRString(string rstring) {
    calcStack.push(Datum(rstring));
}

/* 
 * exec
 * purpose: takes top element, which must be an rstring, and processes its
 *          contents as a sequence of commands
 * parameters: none
 * returns: none
 */
void RPNCalc::exec() {
    // send error message to cerr if top element is not an rstring
    if (not top_stack().isRString()) {
        cerr << "Error: cannot execute non rstring\n";
    } 
    // otherwise, execute commands within rstring
    else {
        string top_rstring = top_stack().getRString();
        // exclude outer "{" and "}" from rstring
        top_rstring = top_rstring.substr(2, top_rstring.length() - 4);
        stringstream ss(top_rstring);
        drop();
        run_helper(ss);
    }
}

/* 
 * file
 * purpose: pops top element off of the stack, which must be an rstring,
 *          and reads/processes the named file
 * parameters: none
 * returns: none
 */
void RPNCalc::file() {
    // send error message to cerr if top element is not an rstring
    if (not top_stack().isRString()) {
        cerr << "Error: file operand not rstring\n";
    } 
    // otherwise, open file and read in commands
    else {
        ifstream input;
        string rstring = top_stack().getRString();
        cerr << rstring << endl;
        // exclude "{" and "}" from file rstring
        string filename = rstring.substr(2, rstring.length() - 4);
        drop();
        input.open(filename);
        // send error message to cerr if file is not open
        if (not input.is_open()) {
            cerr << "Unable to read " << filename << "\n";
        } 
        // otherwise, read in commands
        else {
            run_helper(input);
            input.close();
        }
    }
}

/* 
 * if
 * purpose: pops two rstrings and a boolean, executes FalseCase if bool is
 *          false and TrueCase if true
 * parameters: none
 * returns: none
 */
void RPNCalc::if_command() {
    // store values of top three elements and pop them
    Datum first = top_stack();
    drop();
    Datum second = top_stack();
    drop();
    Datum third = top_stack();
    drop();
    // if third element was boolean, store value
    if (third.isBool()) {
        bool test_condition = third.getBool();
        // if second element was rstring, store value
        if (second.isRString()) {
            string true_case = second.getRString();
            // if first element was rstring, store value
            if (first.isRString()) {
                string false_case = first.getRString();
                // push TrueCase if test condition is true
                if (test_condition) {
                    pushRString(true_case);
                } 
                // otherwise, push FalseCase
                else {
                    pushRString(false_case);
                }
                exec();
            } 
            // otherwise, cerr rstring error message
            else {
                cerr << "Error: expected rstring in if branch\n";
            }
        } 
        // otherwise, cerr rstring error message
        else {
            cerr << "Error: expected rstring in if branch\n";
        }
    } 
    // otherwise, cerr bool error message
    else {
        cerr << "Error: expected boolean in if test\n";
    }
}

/* 
 * top_stack
 * purpose: throws runtime error if stack is empty, returns top element of
 *          stack if not
 * parameters: none
 * returns: top element
 */
Datum RPNCalc::top_stack() {
    // throw runtime error if stack is empty
    if (calcStack.isEmpty()) {
        throw runtime_error("Error: empty_stack\n");
    }

    return calcStack.top();
}