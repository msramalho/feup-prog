#include "Data.h"

Data::Data() {
	dia = 1;
	mes = 1;
	ano = 1;
}
Data::Data(string line) {
	this->read(line);
}
Data::Data(usi dia, usi mes, usi ano) {
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}

inline usi Data::get_dia() {
	return dia;
}
inline usi Data::get_mes() {
	return mes;
}
inline usi Data::get_ano() {
	return ano;
}

Data & Data::set_dia(usi dia) {
	this->dia = dia;
	return *this;
}
Data & Data::set_mes(usi mes) {
	this->mes = mes;
	return *this;
}
Data & Data::set_ano(usi ano) {
	this->mes = mes;
	return *this;
}

bool Data::read(string data) {
	vector<string> temp = split(data,'/');
	if (temp.size() == 3) {
		dia = stoi(temp[0]);
		mes = stoi(temp[1]);
		ano = stoi(temp[2]);
		return true;
	}
	return false;
}

bool Data::bissexto() {
	return ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0));
}

bool Data::valid_day() {
	vector<usi> dias_por_mes = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (bissexto())
		dias_por_mes[1] = 29;
	return valid_month()? dia >= 1 && dia <= dias_por_mes[mes - 1]:false;
}

bool Data::valid_month() {
	return mes >= 1 && mes <=12;
}

bool Data::valid_year() {
	return ano > 0;
}

bool Data::valid() {
	return valid_year() && valid_day();//o valid_day verifica o mes
}

Data Data::operator=(const Data &d_right) {//não sei se é perigoso receber referência e devolver
	dia = d_right.dia;
	mes = d_right.mes;
	ano = d_right.ano;
	return d_right;
}
bool Data::operator<(const Data &d_right) {
	return (
		ano < d_right.ano ||
		(ano == d_right.ano && mes < d_right.mes) ||
		(ano == d_right.ano && mes == d_right.mes && dia < d_right.dia)
		);
}
bool Data::operator>(const Data &d_right) {
	return !this->operator<(d_right);
	/* (ano > d_right.ano ||
		(ano == d_right.ano && mes > d_right.ano) ||
		(ano == d_right.ano && mes == d_right.ano && dia > d_right.dia)
		);*/
}
bool Data::operator==(const Data &d_right) {
	return (ano == d_right.ano && mes == d_right.mes && dia == d_right.dia);
}

inline bool Data::operator!=(const Data &d_right) {
	return !(this->operator==(d_right));
}
bool Data::operator>=(const Data &d_right) {
	return (this->operator>(d_right) || this->operator==(d_right));
}
bool Data::operator<=(const Data &d_right) {
	return (this->operator<(d_right) || this->operator==(d_right));
}

ostream &operator << (ostream &out, const Data &data) {
	out << setw(2) << data.dia << "/" << setw(2) << data.mes << "/" << setw(4) << data.ano;
	return out;
}
istream &operator >> (istream &in, Data &data) {
	char temp;
	in >> data.dia;
	in >> temp;
	if (temp == '/')in >> data.mes;
	in >> temp;
	if (temp == '/')in >> data.ano;
	return in;
}
