#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "defs.h"
#include "utils.h"
#include "Data.h"

using namespace std;

class Compra {
	friend ostream &operator<<(ostream &out, const Compra &compra);
private:
	uint client_id;
	Data data;
	vector<string> produtos;
public:
	Compra();
	Compra(string line);
	Compra(uint client_id, Data data, vector<string> produtos);

	uint get_client_id();
	Data get_data();
	vector<string> get_produtos();
	bool read(string line);
	size_t size();

	bool operator<(const Compra &p_right);
	string & operator()(size_t index);
	string operator()(size_t index) const;
};