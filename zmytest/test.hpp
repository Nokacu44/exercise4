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
void menuBSTString(lasd::BST<std::string>&);

// MAP FUNCTIONS
void visualizeBSTInt(int&, void*);
void visualizeBSTFloat(float&, void*);
void visualizeBSTString(std::string&, void*);

// FOLD FUNCTIONS
void foldBSTInt(const int&, const void*, void*);
void foldBSTFloat(const float&, const void*, void*);
void foldBSTString(const std::string&, const void*, void*);

// AUXILIARY FUNCTIONS
int getStructureSize();
int generateRandomInteger();
float generateRandomFloat();
std::string generateRandomString();

/* ************************************************************************** */

#endif