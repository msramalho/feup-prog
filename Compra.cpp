#include "Compra.h"

Compra::Compra() {
	client_id = 0;
	data = Data();
	vector<string> temp;
	produtos = temp;
}
Compra::Compra(string line) {
	read(line);
}
Compra::Compra(uint client_id, Data data, vector<string> produtos) {
	this->client_id = client_id;
	this->data = data;
	this->produtos = produtos;
}

bool Compra::read(string line) {
	vector<string> temp = split(line);
	if (temp.size() == 3) {
		try {
			client_id = stoi(temp[0]);
			data = Data(temp[1]);
			produtos = split(temp[2], ',');
			return true;
		} catch (int e) {
			cerr << "erro ao ler compra: " << e << " na linha'" << line << "'";
			return false;
		}
	}
	return false;
}

size_t Compra::size() {
	return produtos.size();
}

uint Compra::get_client_id() {
	return client_id;
}
Data Compra::get_data() {
	return data;
}
vector<string> Compra::get_produtos() {
	return produtos;
}

bool Compra::operator<(const Compra &c_right) {
	return data == c_right.data ? produtos.size() < c_right.produtos.size() : data < c_right.data;
}

string & Compra::operator()(size_t index) {
	return produtos.at(index);
}

string Compra::operator()(size_t index) const {
	return produtos.at(index);
}

ostream &operator<<(ostream &out, const Compra &compra) {
	out << setw(NUMBER_SETW) << compra.client_id << " ; "  << compra.data << " ; " ;
	for (size_t i = 0; i < compra.produtos.size() - 1; i++) {
		out << compra.produtos[i] << " , " ;
	}
	out << compra.produtos[compra.produtos.size() - 1];
	return out;
}

