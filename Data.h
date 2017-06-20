#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "defs.h"
#include "utils.h"

using namespace std;

class Data {
	friend ostream& operator<<(ostream& out, const Data &data);
	friend istream& operator>>(istream& in, Data &data);
private:
	usi dia;
	usi mes;
	usi ano;
public:
	Data();
	Data(string line);
	Data(usi dia, usi mes, usi ano);

	usi get_dia();
	usi get_mes();
	usi get_ano();

	Data & set_dia(usi dia);
	Data & set_mes(usi mes);
	Data & set_ano(usi ano);

	bool read(string data);

	bool bissexto();
	bool valid_day();
	bool valid_month();
	bool valid_year();

	bool valid();

	Data operator=(const Data &d_right);
	bool operator<(const Data &d_right);
	bool operator>(const Data &d_right);
	bool operator<=(const Data &d_right);
	bool operator>=(const Data &d_right);
	bool operator==(const Data &d_right);
	bool operator!=(const Data &d_right);


};