/*
 *  parser.cpp
 *  Charles Man
 *  2/28/23
 *
 *  CalcYouLater
 *
 *  Purpose: This is the function definition for parseRString.
 * 
 */

#include "parser.h"
#include <iostream>
#include <sstream>

using namespace std;

string parseRString(istream &input) {
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