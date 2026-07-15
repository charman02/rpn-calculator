/*
 *  Datum.h
 *  CalcYouLater
 *
 *  Interface of the Datum class: a tagged value that can hold exactly one of
 *  an int, a bool, or an rstring (a string). Every calculator value lives in
 *  a Datum, and the type queries (isInt/isBool/isRString) let callers branch
 *  on which kind of value is stored before reading it.
 *
 *  NOTE: This file was reconstructed from the class's usage across the project
 *  (DatumStack, RPNCalc, and unit_tests.h) because the original Datum.h/.cpp
 *  were never committed to the repository.
 */

#ifndef __DATUM_H__
#define __DATUM_H__

#include <string>

class Datum {
public:
    // constructors — one per value kind
    Datum();                          // empty (defaults to integer 0)
    Datum(int i);                     // integer value
    Datum(bool b);                    // boolean value
    Datum(const std::string &rstr);   // rstring value
    Datum(const char *rstr);          // rstring from a string literal

    // type queries
    bool isInt() const;
    bool isBool() const;
    bool isRString() const;

    // accessors — throw std::runtime_error if the stored type does not match
    int getInt() const;
    bool getBool() const;
    std::string getRString() const;

    // string form of the stored value (useful for printing/debugging)
    std::string toString() const;

private:
    enum Type { INT, BOOL, RSTRING };

    Type type;
    int intVal;
    bool boolVal;
    std::string rstringVal;
};

#endif
