#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../list/list.hpp"
#include "../bst/bst.hpp"

#include <iostream>

/* ************************************************************************** */
// BEGIN OF THE TEST
void startTest();

// MENU
void menuBSTInteger(lasd::BST<int>&);

// MAP FUNCTIONS
void visualizeBSTInt(int&, void*);

// FOLD FUNCTIONS
void foldBSTInt(const int&, const void*, void*);

// AUXILIARY FUNCTIONS
int getStructureSize();
int generateRandomInteger();

/* ************************************************************************** */

#endif