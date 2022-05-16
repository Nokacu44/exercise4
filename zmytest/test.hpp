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
void menuBSTFloat(lasd::BST<float>&);

// MAP FUNCTIONS
void visualizeBSTInt(int&, void*);
void visualizeBSTFloat(float&, void*);

// FOLD FUNCTIONS
void foldBSTInt(const int&, const void*, void*);
void foldBSTFloat(const float&, const void*, void*);

// AUXILIARY FUNCTIONS
int getStructureSize();
int generateRandomInteger();
float generateRandomFloat();

/* ************************************************************************** */

#endif