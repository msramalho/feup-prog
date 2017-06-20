#include "Cliente.h"

uint Cliente::get_client_id() {
	return client_id;
}
string Cliente::get_nome() {
	return nome;
}
float Cliente::get_total_compras() {
	return total_compras;
}

Cliente & Cliente::set_nome(string nome) {
	this->nome = to_lower(nome);
	return *this;
}
Cliente & Cliente::add_compras(float val) {
	total_compras = total_compras + val > 0 ? total_compras + val : 0;//nulo ou positivo, nao negativo
	return *this;
}
Cliente & Cliente::set_total_compras(float total) {
	total_compras = total;
	return *this;
}

Cliente::Cliente() {
	client_id = 0;
	nome = "";
	total_compras = 0;
}
Cliente::Cliente(uint client_id, string nome, float total_compras) {
	this->client_id = client_id;
	this->nome = nome;
	this->total_compras = total_compras;
}
Cliente::Cliente(string line) {
	read(line);
}

bool Cliente::read(string line) {
	vector<string> temp = split(line);
	if (temp.size() == 3) {
		try {
			client_id = (uint)stoi(temp[0]);
			nome = to_lower(temp[1]);
			total_compras = stof(temp[2]);
			return true;
		} catch (int e) {
			cout  << "erro ao ler cliente: " << e << " na linha'" << line << "'";
			return false;
		}
	}
	return false;
}


void Cliente::ordenar(vector<Cliente> &clientes, usi type) {
	switch (type) {
	case 1://por total de compras
		sort(clientes.begin(), clientes.end(),comparar_compras);
		break;
	case 2://por id
		sort(clientes.begin(), clientes.end(), comparar_ids);
		break;
	default://alfabeticamente
		sort(clientes.begin(), clientes.end());//como o operador < está definido não é preciso explicitar comparador
		break;
	}
}
bool comparar_compras(const Cliente &cliente_1, const Cliente &cliente_2) {
	return cliente_1.total_compras < cliente_2.total_compras;
}
bool comparar_ids(const Cliente &cliente_1, const Cliente &cliente_2) {
	return cliente_1.client_id < cliente_2.client_id;
}

bool Cliente::operator < (const Cliente &c_right) {
	return (nome < c_right.nome);
}

bool Cliente::operator==(const Cliente & c_right) {
	return  client_id == c_right.client_id
		&& nome == c_right.nome
		&& total_compras == c_right.total_compras;
}

bool Cliente::operator==(const string & c_right) {
	return nome == c_right;
}

ostream& operator<<(ostream& out, const Cliente &cliente) {
	out << setw(NUMBER_SETW) << cliente.client_id << " ; " << setw(TEXT_SETW) << cliente.nome << " ; " << setw(NUMBER_SETW) << cliente.total_compras;
	return out;
}