#pragma once

#include <iostream>
#include<iomanip>
#include<algorithm>//para o sort
#include <vector>
#include <string>

#include "defs.h"
#include "utils.h"

using namespace std;

class Cliente {
	friend ostream& operator<<(ostream& out, const Cliente &cliente);
	friend bool comparar_compras(const Cliente &cliente_1, const Cliente &cliente_2);
	friend bool comparar_ids(const Cliente &cliente_1, const Cliente &cliente_2);
private:
	uint client_id;
	string nome;
	float total_compras;
public:
	
	Cliente();
	Cliente(uint client_id, string nome, float total_compras = 0);
	Cliente(string line);

	uint get_client_id();
	string get_nome();
	float get_total_compras();
	Cliente & set_nome(string nome);
	Cliente & add_compras(float val);
	Cliente & set_total_compras(float total);

	bool read(string line);
	static void Cliente::ordenar(vector<Cliente> &clientes, usi type = 0);
	bool operator<(const Cliente &c_right);
	bool operator==(const Cliente &c_right);
	bool operator==(const string &c_right);
};