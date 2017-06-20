#include "Produto.h"

Produto::Produto() {
	nome = "";
	preco = 0;
}

Produto::Produto(string line) {
	read(line);
}

string Produto::get_nome() {
	return nome;
}

float Produto::get_preco() {
	return preco;
}

bool Produto::read(string line) {
	vector<string> temp = split(line);
	if (temp.size() == 2) {
		try {
			nome = to_lower(temp[0]);
			preco = stof(temp[1]);
			return true;
		} catch (int e) {
			cerr << "erro ao ler produto: " << e << " na linha'" << line << "'";
			return false;
		}
	}
	return false;
}

bool Produto::operator < (const Produto &p_right) {
	return (nome < p_right.nome);
}

ostream& operator<<(ostream& out, const Produto &produto) {
	out << setw(TEXT_SETW) << produto.nome << " ; " << setw(NUMBER_SETW) << produto.preco;
	return out;
}
