#pragma once

#include<iostream>
#include <string>
#include <typeinfo>

typedef unsigned short int usi;
typedef unsigned int uint;

const uint NUMBER_SETW = 6;
const uint TEXT_SETW = 20;
const uint DATA_SETW = 10;
#ifdef _WIN32
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif