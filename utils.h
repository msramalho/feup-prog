#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include <cstdlib>//cls
#include <fstream>//file read/write

#include "defs.h"


using namespace std;

/**
Tests if cin reading operation was successful changes the value of success
accordingly so it can be handled by the caller

@param success boolean value representing cin operation result
@function return value: success, as it is passed by reference
*/
void cin_test(bool &success);

/**
Read any type of variable from the keyboard through std::cin, after outputing a message related to the value to read.
@param message the message to show to user while asking for a valid value
Returns:
@param result read int value
*/
template<typename T1>
void cin_value(T1 &result, string message);

/**
Read string from the keyboard through std::cin.getline(), after outputing a message related to the
value to read so as to allow strings with word-breaks.
@param message the message to show to user while asking for a non-empty string
Returns:
@param result read string value
*/
void cin_value_str(string &result, string message);

/**
Read any type of variable from the keyboard by checking if it is a string---->cin_value_str OR any other type---->cin_value_any
@param message the message to show to user while asking for a valid value
Returns:
@param result read int value
*/
//template<typename T1>
//void cin_value(T1 &result, string message = "Valor escolhido?");

/**
Read int and related types, short, long, unsigned, ... from the keyboard by calling cin_value until the number is between the valid intervals.
@param message the message to show to user while asking for a valid int
Returns:
@param result read numerical value
*/
void cin_value_between(usi &result, string message, usi min, usi max);

/**
Convert a string to lower case
@param original the string to transform
@function return value: string with the result of the operation
*/
string to_lower(string original);

/**
Splits a string by every occurence and stores the parts in a vector<string>
@param line the string to split
@param delimiter char to identify spliting points
@function return value: vector of strings with the result of the operation
*/
vector<string> split(string line, char delimiter = ';');

/**
Trim the original string, by removing all occurences of trimmed_char from its left and right and allowing only one betwee other chars
@param original the string to trim
@param char_trim char to remove
@function return value: s string trimmed
*/
string trim(string s, char char_trim = ' ');

/**
Get the maximum value of a vector<T1>
@param test vector to test
@function return value: the max value or NULL, if test is empty
*/
uint get_max(vector<uint> test);

/**
Transposes a matrix (usefull for the custom advertising algorithm)
@param matrix to transpose
@function return value: the matrix of booleans transposed
*/
void transpose(vector<vector<bool>> &matrix);

template<typename T1>
bool in_vector(const vector<T1> &v, T1 value);

bool yes_no_question(string message);

/**
Reads al the lines from a file into a vector<string>
@param file_name of the file to be read
@function return value: vector <string> with all the lines, error of operation
*/
vector <string> read_file(string file_name);

/**
Tests if a filename corresponds to a valid file
@param file_name to search
@function return value: boolean true if the file exists/ is readable or false if it does not
*/
bool file_exists(string file_name);