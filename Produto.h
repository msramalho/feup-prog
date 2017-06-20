#pragma once

#include <iostream>
#include<iomanip>
#include <sstream>
#include <vector>
#include <string>

#include "defs.h"
#include "utils.h"

using namespace std;

class Produto {
private:
	string nome;
	float preco;
public:
	Produto();
	Produto(string line);
	string get_nome();
	float get_preco();

	bool read(string line);

	bool operator<(const Produto &p_right);

	friend ostream &operator<<(ostream &out, const Produto &produto);
};