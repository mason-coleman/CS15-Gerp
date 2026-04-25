/*
 *  unit_tests.cpp
 *  
 *  CS 15 Project 2 Gerp
 *
 *  Tests for the functions in processing.cpp
 *
 */
 
#include "processing.h"
#include <cassert>
#include <iostream>
 
using namespace std;
 
//clean alphanumeric string unchanged
void testStripNoChange() {
    assert(stripNonAlphaNum("hello")  == "hello");
    assert(stripNonAlphaNum("abc123") == "abc123");
    assert(stripNonAlphaNum("A")      == "A");
}
 
//leading non-alphanumeric characters removed
void testStripLeading() {
    assert(stripNonAlphaNum("...hello") == "hello");
    assert(stripNonAlphaNum("!!word")   == "word");
    assert(stripNonAlphaNum("---42")    == "42");
}
 
//trailing non-alphanumeric characters removed
void testStripTrailing() {
    assert(stripNonAlphaNum("hello...") == "hello");
    assert(stripNonAlphaNum("word!!")   == "word");
    assert(stripNonAlphaNum("42---")    == "42");
}
 
//leading/trailing non-alphanumeric characters removed
void testStripBothEnds() {
    assert(stripNonAlphaNum("...hello...") == "hello");
    assert(stripNonAlphaNum("(test)")      == "test");
    assert(stripNonAlphaNum("'quoted'")    == "quoted");
}
 
// Non-alphanumeric characters should be preserved
void testStripInteriorPreserved() {
    assert(stripNonAlphaNum("don't")   == "don't");
    assert(stripNonAlphaNum("he-llo")  == "he-llo");
    assert(stripNonAlphaNum("..a-b..") == "a-b");
}
 
//only non-alphanumeric characters return empty string
void testStripAllNonAlpha() {
    assert(stripNonAlphaNum("...") == "");
    assert(stripNonAlphaNum("!!!") == "");
    assert(stripNonAlphaNum("---") == "");
}
 
//empty string
void testStripEmptyString() {
    assert(stripNonAlphaNum("") == "");
}