/*
 *  Datum.cpp
 *  CalcYouLater
 *
 *  Implementation of the Datum class. A Datum stores exactly one of an int,
 *  a bool, or an rstring, tracked by a type tag. Accessors verify the tag and
 *  throw std::runtime_error on a type mismatch so callers can't silently read
 *  the wrong field.
 *
 *  NOTE: Reconstructed from project usage; see Datum.h.
 */

#include "Datum.h"
#include <stdexcept>

using namespace std;

// empty Datum: behaves as integer 0
Datum::Datum() : type(INT), intVal(0), boolVal(false), rstringVal("") {}

Datum::Datum(int i) : type(INT), intVal(i), boolVal(false), rstringVal("") {}

Datum::Datum(bool b) : type(BOOL), intVal(0), boolVal(b), rstringVal("") {}

Datum::Datum(const string &rstr)
    : type(RSTRING), intVal(0), boolVal(false), rstringVal(rstr) {}

Datum::Datum(const char *rstr)
    : type(RSTRING), intVal(0), boolVal(false), rstringVal(rstr) {}

bool Datum::isInt() const { return type == INT; }
bool Datum::isBool() const { return type == BOOL; }
bool Datum::isRString() const { return type == RSTRING; }

int Datum::getInt() const {
    if (type != INT) {
        throw runtime_error("Datum is not an int");
    }
    return intVal;
}

bool Datum::getBool() const {
    if (type != BOOL) {
        throw runtime_error("Datum is not a bool");
    }
    return boolVal;
}

string Datum::getRString() const {
    if (type != RSTRING) {
        throw runtime_error("Datum is not an rstring");
    }
    return rstringVal;
}

string Datum::toString() const {
    if (type == INT) {
        return to_string(intVal);
    } else if (type == BOOL) {
        return boolVal ? "#t" : "#f";
    } else {
        return rstringVal;
    }
}
