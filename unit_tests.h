/*
 *  unit_tests.h
 *  Charles Man
 *  2/28/23
 *
 *  CalcYouLater
 *
 *  Purpose: This file contains all unit tests for testing the member
 *           functions of the DatumStack class.
 *
 */

#include "DatumStack.h"
#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

/* CONSTRUCTOR TESTS */

// make sure no fatal memory errors/leaks in the default constructor
void default_constructor_1() {
    DatumStack test_stack;
}

// make sure no items exist in the stack using default constructor
void default_constructor_2() {
    DatumStack test_stack;
    assert(test_stack.isEmpty());
}

// tests for empty stack using second constructor
void second_constructor_empty() {
    Datum test_arr[] = {};
    DatumStack test_stack(test_arr, 0);
    assert(test_stack.isEmpty());
}

// tests for 1-element stack using second constructor
void second_constructor_single() {
    Datum test_arr[] = {Datum(1)};
    DatumStack test_stack(test_arr, 1);
    assert(test_stack.size() == 1);
    assert(test_stack.top().getInt() == 1);
}

// tests for 3-element stack using second constructor
void second_constructor_three_elements() {
    Datum test_arr[] = {Datum(1), Datum(2), Datum(false)};
    DatumStack test_stack(test_arr, 3);
    assert(test_stack.size() == 3);
    assert(test_stack.top().getBool() == false);
}

/* FUNCTIONS */

// tests isEmpty for an empty stack
void isEmpty_correct() {
    DatumStack test_stack;
    assert(test_stack.isEmpty());
}

// tests isEmpty for a non-empty stack
void isEmpty_incorrect() {
    Datum test_arr[] = {Datum(1)};
    DatumStack test_stack(test_arr, 1);
    assert(not test_stack.isEmpty());
}

// tests clear for a empty stack
void clear_empty() {
    DatumStack test_stack;
    test_stack.clear();
    assert(test_stack.isEmpty());
}

// tests clear for 1-element stack
void clear_single() {
    Datum test_arr[] = {Datum(1)};
    DatumStack test_stack(test_arr, 1);
    test_stack.clear();
    assert(test_stack.isEmpty());
}

// tests clear for 3-element stack
void clear_three_elements() {
    Datum test_arr[] = {Datum(1), Datum(2), Datum(true)};
    DatumStack test_stack(test_arr, 3);
    test_stack.clear();
    assert(test_stack.isEmpty());
}

// tests clear for 1000-element stack
void clear_many_elements() {
    DatumStack test_stack;
    for (int i = 0; i < 1000; i++) {
        test_stack.push(Datum(1));
    }
    test_stack.clear();
    assert(test_stack.isEmpty());
}

// tests size for empty stack
void size_empty() {
    DatumStack test_stack;
    assert(test_stack.size() == 0);
}

// tests size for 1-element stack
void size_single() {
    Datum test_arr[] = {Datum(1)};
    DatumStack test_stack(test_arr, 1);
    assert(test_stack.size() == 1);
}

// tests size for 3-element stack
void size_three_elements() {
    Datum test_arr[] = {Datum(1), Datum(2), Datum(true)};
    DatumStack test_stack(test_arr, 3);
    assert(test_stack.size() == 3);
}

// tests size for 1000-element stack
void size_many_elements() {
    DatumStack test_stack;
    for (int i = 0; i < 1000; i++) {
        test_stack.push(Datum('a'));
    }
    assert(test_stack.size() == 1000);
}

// tests top for empty stack
void top_empty() {
    bool runtime_error_thrown = false;
    string error_message = "";
    DatumStack test_stack;
    // try to call top on empty stack
    try {
        test_stack.top();
    }
    // if top is implemented correctly, a runtime_error will be thrown and
    // we will end up here
    catch (const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// tests top for 1-element stack
void top_single() {
    Datum test_arr[] = {Datum("{ 1 1 + }")};
    DatumStack test_stack(test_arr, 1);
    assert(test_stack.top().getRString() == "{ 1 1 + }");
}

// tests top for 3-element stack
void top_three_elements() {
    Datum test_arr[] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test_stack(test_arr, 3);
    assert(test_stack.top().getInt() == 3);
}

// tests top for 1000-element stack
void top_many_elements() {
    DatumStack test_stack;
    for (int i = 0; i < 999; i++) {
        test_stack.push(Datum(1));
    }
    test_stack.push(Datum(2));
    assert(test_stack.top().getInt() == 2);
}

// tests pop for empty stack
void pop_empty() {
    bool runtime_error_thrown = false;
    string error_message = "";
    DatumStack test_stack;
    // try to call pop on empty stack
    try {
        test_stack.pop();
    }
    // if pop is implemented correctly, a runtime_error will be thrown and
    // we will end up here
    catch (const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// tests pop for 1-element stack
void pop_single() {
    Datum test_arr[] = {Datum(1)};
    DatumStack test_stack(test_arr, 1);
    test_stack.pop();
    assert(test_stack.isEmpty());
}

// tests pop for 3-element stack
void pop_three_elements() {
    Datum test_arr[] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test_stack(test_arr, 3);
    test_stack.pop();
    assert(test_stack.size() == 2);
    assert(test_stack.top().getInt() == 2);
}

// tests pop for 1000-element stack
void pop_many_elements() {
    DatumStack test_stack;
    for (int i = 0; i < 999; i++) {
        test_stack.push(Datum(1));
    }
    test_stack.push(Datum(2));
    test_stack.pop();
    assert(test_stack.size() == 999);
    assert(test_stack.top().getInt() == 1);
}

// tests push for empty stack
void push_empty() {
    DatumStack test_stack;
    test_stack.push(Datum(1));
    assert(test_stack.size() == 1);
    assert(test_stack.top().getInt() == 1);
}

// tests push for 1-element stack
void push_single() {
    Datum test_arr[] = {Datum(1)};
    DatumStack test_stack(test_arr, 1);
    test_stack.push(Datum(2));
    assert(test_stack.size() == 2);
    assert(test_stack.top().getInt() == 2);
}

// tests push for 3-element stack
void push_three_elements() {
    Datum test_arr[] = {Datum(1), Datum(2), Datum(3)};
    DatumStack test_stack(test_arr, 3);
    test_stack.push(Datum(4));
    assert(test_stack.size() == 4);
    assert(test_stack.top().getInt() == 4);
}

// tests push for 1000-element stack
void push_many_elements() {
    DatumStack test_stack;
    for (int i = 0; i < 1000; i++) {
        test_stack.push(Datum(1));
    }
    test_stack.push(Datum(2));
    assert(test_stack.size() == 1001);
    assert(test_stack.top().getInt() == 2);
}