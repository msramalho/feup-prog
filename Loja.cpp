#include "Loja.h"

uint Loja::last_client_id = 0;

Loja::Loja() {
	ler_ficheiros();
	system(CLEAR);
}

void Loja::ler_ficheiros() {
	do {
		ler_ficheiro("clientes", f_clientes);// , &Loja::ler_clientes);
	} while (!ler_clientes());

	do {
		ler_ficheiro("produtos", f_produtos);
	} while (!ler_produtos());

	do {
		ler_ficheiro("compras", f_compras);
	} while (!ler_compras());
}
void Loja::ler_ficheiro(string file_type, string &file_name) {//, bool (Loja::*funcao_leitura)()) {
	stringstream ss;
	ss << "Ups! Nao foi possivel importar os dados de " << file_type << ", tente outro ficheiro .txt";
	string error_message = ss.str();
	ss.str("");
	ss << "Ficheiro de " << file_type << "?";
	string file_prompt = ss.str();

	//LER ficheiro
	cin_value_str(file_name, file_prompt);
	/*f_clientes = "c.txt";
	f_produtos = "i.txt";
	f_compras = "p.txt";*/
	while (!file_exists(file_name)) {
		cout << error_message << endl;
		cin_value_str(file_name, file_prompt);
	}
	cout << endl;
}

bool Loja::ler_clientes() {
	clientes.clear();
	vector <string> lines = read_file(f_clientes);
	for (size_t i = 1; i < lines.size(); i++) {//le todos e ignora a primeira linha com a contagem por ser desnecessária.
		Cliente temp;
		if (temp.read(lines[i])) {
			if (!client_existe(temp.get_nome())) {
				clientes.push_back(temp);
				guardar_cliente_map(temp, clientes.size() - 1);
				if (temp.get_client_id() > last_client_id) {
					last_client_id = temp.get_client_id();
				}
			}
		} else {
			return false;
		}
	}
	return true;
}
bool Loja::ler_produtos() {
	produtos.clear();
	vector <string> lines = read_file(f_produtos);
	for (size_t i = 1; i < lines.size(); i++) {//le todos e ignora a primeira linha com a contagem por ser desnecessária.
		Produto temp;
		if (temp.read(lines[i])) {
			produtos.push_back(temp);
			map_produtos.insert(pair<string, size_t>(temp.get_nome(), produtos.size() - 1));
		} else {
			return false;
		}
	}
	return true;
}
bool Loja::ler_compras() {
	compras.clear();
	vector <string> lines = read_file(f_compras);
	for (size_t i = 1; i < lines.size(); i++) {//le todos e ignora a primeira linha com a contagem por ser desnecessária.
		Compra temp;
		if (temp.read(lines[i])) {
			compras.push_back(temp);
			guardar_compra_mmap(temp.get_client_id(), compras.size() - 1);
		} else {
			return false;
		}
	}
	return true;
}

void Loja::lista_produtos() {
	cout << endl << setw(TEXT_SETW) << "NOME" << " ; " << setw(NUMBER_SETW) << "Preco" << endl;
	for (size_t i = 0; i < produtos.size(); i++) {
		cout << produtos[i] << endl;
	}
	cout << endl;
}

void Loja::estatisticas() {
	cout << "Last Clt. ID = " << last_client_id << endl;
	cout << "# Clientes   = " << clientes.size() << endl;
	cout << "# Produtos   = " << produtos.size() << endl;
	cout << "# Compras    = " << compras.size() << endl;
	float total_compras = 0;
	for (size_t i = 0; i < compras.size(); i++) {
		vector<string> prods = compras[i].get_produtos();
		for (size_t j = 0; j < prods.size(); j++) {
			total_compras += produtos[map_produtos[prods[j]]].get_preco();
		}
	}
	cout << "Total Ganhos = " << total_compras << endl;
}

void Loja::guardar_ficheiros(bool exit) {
	if (clientes_por_atualizar) {
		if (guardar_clientes(exit)) {
			cout << "Dados de clientes guardados com sucesso" << endl;
			clientes_por_atualizar = false;
		} else {
			cout << "Dados de clientes nao guardados!" << endl;
		}
	} else {
		cout << "Nao foram feitas alteracoes aos clientes" << endl;
	}

	if (compras_por_atualizar) {
		if (guardar_compras()) {
			cout << "Dados de compras guardados com sucesso" << endl;
			compras_por_atualizar = false;
		} else {
			cout << "Dados de compras nao guardados!" << endl;
		}
	} else {
		cout << "Nao foram feitas alteracoes as compras" << endl;
	}
}
bool Loja::guardar_clientes(bool exit) {
	bool success = true;
	//if (!exit) {
		Cliente::ordenar(clientes, 2);
	//}
	atualizar_map_clientes();//para o map ficar atualizado
	ofstream outf;
	outf.open(f_clientes);
	if (!outf.is_open()) {
		cerr << "Ficheiro " << f_clientes << " nao encontrado !\n";
		success = false;
	} else {
		outf << clientes.size() << endl;
		for (size_t i = 0; i < clientes.size(); i++) {
			outf << clientes[i] << endl;
		}
	}
	outf.close();
	return success;
}
bool Loja::guardar_compras() {
	bool success = true;
	ofstream outf;
	outf.open(f_compras);
	if (!outf.is_open()) {
		cerr << "Ficheiro " << f_compras << " nao encontrado !\n";
		success = false;
	} else {
		outf << compras.size() << endl;
		for (size_t i = 0; i < compras.size(); i++) {
			outf << compras[i] << endl;
		}
	}
	outf.close();
	return success;
}

int Loja::ler_cliente_index() {
	if (map_clientes.size() > 0) {
		string nome = "";
		cin_value_str(nome, "Qual o nome do cliente('cancel' para parar)?");
		nome = to_lower(nome);
		while (!client_existe(nome) && nome != "cancel") {
			cout << "Cliente nao encontrado, tente outro nome." << endl;
			cin_value_str(nome, "Qual o nome do cliente?");
			nome = to_lower(nome);
		}
		return nome == "cancel" ? -1 : map_clientes[nome];
	} else {
		cout << "Nao ha clientes" << endl;
		return -1;
	}
}

void Loja::atualizar_map_clientes() {
	for (auto i = map_clientes.begin(); i != map_clientes.end(); i++) {
		//como esta garantido que os clientes no map sao os do clientes este find nunca retorna clientes.end()
		i->second = distance(clientes.begin(), find(clientes.begin(), clientes.end(), i->first));
	}
}

inline void Loja::guardar_cliente_map(Cliente temp, size_t index) {
	map_clientes[temp.get_nome()] = index;//guardar no map_clientes
}

void Loja::recalcular_compras() {
	if (clientes.size() > 0) {
		typedef map<string, size_t>::iterator m_it;//iterador para m_produtos
		float total_compras = 0;

		for (size_t i = 0; i < clientes.size(); i++) {//percorrer os clientes
			total_compras = 0;
			pair<mm_it, mm_it> range = mmap_compras.equal_range(clientes[i].get_client_id());//obter os iteradores para inicio e > fim das compras do cliente
			for (mm_it j = range.first; j != range.second; j++) {//percorrer as compras
				vector<string> contar_produtos = compras[j->second].get_produtos();
				for (size_t k = 0; k < compras[j->second].size(); k++) {
					total_compras += produtos[map_produtos[compras[j->second](k)]].get_preco();//o operador () esta overloaded na compra
				}
			}
			clientes[i].set_total_compras(total_compras);
		}
		clientes_por_atualizar = true;
		cout << "Totais recalculados!" << endl;
	} else {
		cout << "Nao ha clientes..." << endl;
	}

}

bool Loja::client_existe(string temp) {
	return map_clientes.find(temp) != map_clientes.end();
}

void Loja::adicionar_cliente() {
	string name;
	cin_value_str(name, "Qual o nome do novo cliente? ('cancel' para parar)");
	while (client_existe(name) && name != "cancel") {
		cout << "Ja existe um cliente com esse nome, tente outro." << endl;
		cin_value_str(name, "Qual o nome do novo cliente? ('cancel' para parar)");
	}
	name = to_lower(name);
	if (name != "cancel") {
		Cliente c(++last_client_id, name);
		clientes.push_back(c);
		guardar_cliente_map(c, clientes.size() - 1);
		clientes_por_atualizar = true;
	}
}
void Loja::editar_cliente() {
	int client_index = ler_cliente_index();
	if (client_index >= 0) {
		string novo_nome;
		cout << "Client id corresponde ao cliente: '" << clientes[client_index].get_nome()
			<< "' total compras: '" << clientes[client_index].get_total_compras() << "'" << endl;
		cin_value(novo_nome, "Qual o novo nome? ('cancel' para cancelar)");
		novo_nome = to_lower(novo_nome);
		if (novo_nome != "cancel") {
			if (client_existe(novo_nome)) {
				cout << "este nome ja existe!" << endl;
			} else {
				map_clientes.erase(clientes[client_index].get_nome());
				map_clientes[novo_nome] = client_index;
				clientes[client_index].set_nome(novo_nome);
				clientes_por_atualizar = true;
				cout << "Cliente Atualizado" << endl;
			}
		}
	}
}
void Loja::eliminar_cliente() {
	int client_index = ler_cliente_index();
	if (client_index >= 0) {
		if (yes_no_question("Deseja eliminar este cliente?")) {
			map_clientes.erase(clientes[client_index].get_nome());
			clientes.erase(clientes.begin() + client_index);
			atualizar_map_clientes();
			cout << "Cliente eliminado." << endl;
			clientes_por_atualizar = true;
		}
	}
}
void Loja::info_cliente() {
	int client_index = ler_cliente_index();
	if (client_index >= 0) {
		cout << setw(NUMBER_SETW) << "ID" << " ; " << setw(TEXT_SETW) << "NOME" << " ; " << setw(NUMBER_SETW) << "TOTAL" << endl;
		cout << clientes[client_index] << endl;
		lista_compras_cliente(clientes[client_index].get_client_id());
	}
}
void Loja::mostrar_info_cliente(int client_index) {
	cout << setw(NUMBER_SETW) << "ID" << " ; " << setw(TEXT_SETW) << "NOME" << " ; " << setw(NUMBER_SETW) << "TOTAL" << endl;
	cout << clientes[client_index] << endl;
	lista_compras_cliente(clientes[client_index].get_client_id());
}
void Loja::lista_clientes() {
	if (map_clientes.size() > 0) {
		cout << setw(NUMBER_SETW) << "ID" << " ; " << setw(TEXT_SETW) << "NOME" << " ; " << setw(NUMBER_SETW) << "TOTAL" << endl;
		for (auto iterator = map_clientes.begin(); iterator != map_clientes.end(); iterator++) {
			cout << clientes[iterator->second] << endl;
		}
	} else {
		cout << "Nao ha clientes." << endl;
	}
}
void Loja::lista_pior_melhor() {
	Cliente::ordenar(clientes, 1);
	atualizar_map_clientes();
	cout << "            " << setw(NUMBER_SETW) << "ID" << " ; " << setw(TEXT_SETW) << "NOME" << " ; " << setw(NUMBER_SETW) << "TOTAL" << endl;
	size_t contar = clientes.size();
	for (size_t i = 0; i < contar; i++) {
		cout << "Pos #" << setw(2) << (contar - i)<< " -> " << clientes[i] << endl;
	}
}

inline void Loja::guardar_compra_mmap(uint id, size_t index) {
	mmap_compras.insert(pair<uint, size_t>(id, index)); //guardar no mmap_compras
}

void Loja::adicionar_compra() {
	int client_index = ler_cliente_index();
	if (client_index >= 0) {
		string data_line, last_item;
		float item_sum = 0;
		vector <string> items_local;
		Data d;
		do {
			cin_value(data_line, "Qual a data (dd/mm/yyyy)? ('cancel' para parar)");
		} while ((!d.read(data_line) || !d.valid()) && data_line != "cancel");
		if (data_line != "cancel") {
			cout << "Eis os produtos disponiveis:" << endl;
			lista_produtos();
			do {
				cin_value_str(last_item, "Qual o proximo produto? ('cancel' para cancelar operacao, 'end' para parar de inserir, 'u' para remover o ultimo)");
				last_item = to_lower(last_item);
				if (last_item == "end" && items_local.size() == 0) {
					cout << "Deve colocar pelo menos um produto no cesto!" << endl;
				} else {
					if (find(items_local.begin(), items_local.end(), last_item) == items_local.end() && last_item != "u") {
						if (last_item != "end" && last_item!= "cancel") {
							if (map_produtos.find(last_item) == map_produtos.end()) {
								cout << "produto inexistente" << endl;
							} else {
								items_local.push_back(last_item);
								item_sum += produtos[map_produtos[last_item]].get_preco();
							}
						}
					} else if (last_item == "u") {
						if (items_local.size() > 0) {
							item_sum -= produtos[map_produtos[items_local[items_local.size() - 1]]].get_preco();
							cout << "produto " << items_local[items_local.size() - 1] << " removido!" << endl;
							items_local.pop_back();
						} else {
							cout << "Nao ha produtos no cesto!" << endl;
						}
					} else {
						cout << "Este produto ja esta no cesto" << endl;
					}

				}
			} while ((last_item != "end" || items_local.size() == 0) && last_item != "cancel");

			if (last_item != "cancel" && items_local.size() > 0) {
				uint c_id = clientes[client_index].get_client_id();
				clientes[client_index].add_compras(item_sum);
				Compra p(c_id, d, items_local);
				compras.push_back(p);
				guardar_compra_mmap(c_id, compras.size() - 1);
				compras_por_atualizar = true;
				clientes_por_atualizar = true;
				cout << "Compra adicionada" << endl;
			}
		}

	}
}
void Loja::eliminar_compra() {
	int client_index = ler_cliente_index();
	if (client_index >= 0) {
		mostrar_info_cliente(client_index);
		size_t compra_index;
		cout << "Qual o indice da compra a eliminar, dadas as compras acima?";
		cin >> compra_index;
		//cin_value(compra_index, "Qual o indice da compra a eliminar, dadas as compras acima?");
		if (yes_no_question("Deseja eliminar esta compra?")) {
			bool found = false;
			pair<mm_it, mm_it> range = mmap_compras.equal_range(clientes[client_index].get_client_id());

			for (mm_it i = range.first; i != range.second; i++) {
				if (i->second == compra_index) {
					float total_sum_removed = 0;
					for (size_t j = 0; j < compras[compra_index].get_produtos().size(); j++) {
						total_sum_removed += produtos[map_produtos[compras[compra_index](j)]].get_preco();
					}
					clientes[client_index].add_compras(-total_sum_removed);
					compras.erase(compras.begin() + compra_index);
					mmap_compras.erase(i);
					found = true;
					compras_por_atualizar = true;
					clientes_por_atualizar = true;
					break;
				}
			}
			cout << (found?"Compra eliminada":"Compra nao encontrada!") << endl;

		}
	}
}
void Loja::lista_compras_cliente(int cliente_id) {
	pair<mm_it, mm_it> range = mmap_compras.equal_range(cliente_id);
	cout << endl << "COMPRAS" << endl;
	for (mm_it i = range.first; i != range.second; i++) {
		cout << setw(3) <<  i->second << " - " << compras[i->second] << endl;
	}
	cout << endl;
}
void Loja::lista_compras_todas() {
	sort(compras.begin(), compras.end());
	cout << endl << "Todas as compras" << endl;
	cout << setw(NUMBER_SETW) << "ID" << " ; " << setw(DATA_SETW) << "DATA" << " ; PRODUTO(S)" << endl;
	for (size_t i = 0; i < compras.size(); i++) {
		cout << compras[i] << endl;
	}
}
void Loja::lista_compras_dia() {
	sort(compras.begin(), compras.end());
	Data d;
	string data_line;
	do {
		cin_value(data_line, "Qual a data (dd/mm/yyyy)? ('cancel' para parar)");
	} while ((!d.read(data_line) || !d.valid()) && data_line != "cancel");

	if (data_line != "cancel") {
		uint contar = 0;
		cout << setw(NUMBER_SETW) << "ID" << " ; " << setw(DATA_SETW) << "DATA" << " ; PRODUTO(S)" << endl;
		for (size_t i = 0; i < compras.size(); i++) {
			if (compras[i].get_data() == d) {
				cout << compras[i] << endl;
				contar++;
			}
		}
		cout << setw(NUMBER_SETW) << contar << " resultado(s)!" << endl;
	}
}
void Loja::lista_compras_intervalo() {
	sort(compras.begin(), compras.end());
	Data d_from, d_to;
	string data_line;
	do {
		cin_value(data_line, "Qual a data de inicio (dd/mm/yyyy)? ('cancel' para parar)");
	} while ((!d_from.read(data_line) || !d_from.valid()) && data_line != "cancel");

	if (data_line != "cancel") {
		data_line == "";
		do {
			cin_value(data_line, "Qual a data de fim (dd/mm/yyyy)? ('cancel' para parar)");
		} while ((!d_to.read(data_line) || !d_to.valid()) && data_line != "cancel");

		if (data_line != "cancel") {
			uint contar = 0;
			cout << setw(NUMBER_SETW) << "ID" << " ; " << setw(DATA_SETW) << "DATA" << " ; PRODUTO(S)" << endl;
			for (size_t i = 0; i < compras.size(); i++) {
				if (compras[i].get_data() >= d_from && compras[i].get_data() <= d_to) {
					cout << compras[i] << endl;
					contar++;
				}
			}
			cout << setw(NUMBER_SETW) << contar << " resultado(s)!" << endl;
		}

	}

}

void Loja::lista_bottom10() {
	Cliente::ordenar(clientes, 1);
	atualizar_map_clientes();
	size_t max = clientes.size() >= 10 ? 10 : clientes.size();
	if (max < 10) {
		cout << "Apenas existem " << max << " clientes no bottom 10" << endl;
	}
	cout << "Ei-los ordenados de pior para melhor cliente:" << endl;
	cout << "          " << setw(NUMBER_SETW) << "ID" << " ; " << setw(TEXT_SETW) << "NOME" << " ; " << setw(NUMBER_SETW) << "TOTAL" << endl;
	for (size_t i = 0; i < max; i++) {
		cout << "Pos #" << setw(2) << i + 1 << " -> " << clientes[i] << endl;
	}
}

void Loja::print_matrix(const vector<vector<bool>> &matrix) {
	//print matrix (debug)
	if (matrix.size() > 0) {
		cout << "ln-";
		for (size_t j = 0; j < matrix[0].size(); j++) {
			cout << setw(2) << j << "-";
		}
		for (size_t i = 0; i < matrix.size(); i++) {
			cout << endl << setw(2) << i << "-";
			for (size_t j = 0; j < matrix[0].size(); j++) {
				cout << setw(2) << matrix[i][j] << "-";
			}
		}
		cout << endl;
	}
}
void Loja::read_matrix(vector<vector<bool>> &matrix, map<size_t, size_t> &map_clientes_matriz) {
	//fill matrix with true where a given client bought a given items
	for (size_t i = 0; i < clientes.size(); i++) {
		pair<mm_it, mm_it> range = mmap_compras.equal_range(clientes[i].get_client_id());
		for (mm_it j = range.first; j != range.second; j++) {
			for (size_t k = 0; k < compras[j->second].get_produtos().size(); k++) {
				matrix
					[map_clientes_matriz[clientes[i].get_client_id()]]
				[map_produtos[compras[j->second](k)]]
				= true;
				//ver nota importante do metodo publicidade_cliente no ponto 20, sem esta restrição seria algo como:
					//matrix[i][map_produtos[compras[j->second](k)]] = true;
			}
		}
	}
}
void Loja::intersect_matrix_and_target(vector<vector<bool>> &matrix, const vector<bool> &target) {
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < target.size(); j++) {
			matrix[i][j] = (matrix[i][j] && target[j]);
		}
	}
}
vector<uint> Loja::get_count_true_values(const vector<vector<bool>> &matrix) {

	vector<uint> client_matches(matrix.size(), 0);
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j]) {
				client_matches[i]++;
			}
		}
	}
	return client_matches;
}
vector<vector<bool>> Loja::get_lines_with_given_count(const vector<vector<bool>> &matrix, const vector<uint> &client_matches, const uint given_count) {
	//returns a matrix with only the clients for a given count of matches
	vector<vector<bool>> temp_matrix;
	for (size_t i = 0; i < client_matches.size(); i++) {
		if (given_count == client_matches[i]) {
			temp_matrix.push_back(matrix[i]);
		}
	}
	return temp_matrix;
}
void Loja::publicidade_cliente() {
	int client_index = ler_cliente_index();
	if (client_index >= 0) {
		cout << "Calculando publicidade personalizada para o cliente " << clientes[client_index].get_nome() << "..." << endl;

		//10 - inicializar matriz a false com as linhas e colunas adequadas
		vector<vector<bool>> matrix(clientes.size(), vector<bool>(produtos.size(), false));//matriz de booleanos
		vector<bool> target(produtos.size());//vector de booleanos que vai guardar os valores do target
		vector<vector<bool>> important_lines;//vector usado para guardar o resultado de operações aritméticas na variável matrix que não a devam alterar
		vector<uint> client_matches;//Vector que guarda o numero de items em comum com o alvo sendo a linha correspondente à da matriz, nao compensa usar um map
		//map<uint, uint> client_matches;//map que associa o numero de produtos em comum de um cliente, x, com o alvo com o index desse cliente na matrix
		int maximum_items = 0, count_best = 0;
		bool found = false;

		//20 - Estabelecer uma associação entre o id de cada cliente e uma linha da matriz de modo a aceder à linha do cliente dado o seu id.
			//NOTA IMPORTANTE - se este ponto não fosse um ponto obrigatório do enunciado 
			//eliminá-lo-ia porque basta usar o indice da linha da matriz como indice do vector clientes
		map<size_t, size_t> map_clientes_matriz;
		for (size_t i = 0; i < clientes.size(); i++) {
			map_clientes_matriz.insert(pair<size_t, size_t>(clientes[i].get_client_id(), i));
		}

		//30 - colocar true nos produtos registados
		read_matrix(matrix, map_clientes_matriz);
		//print_matrix(matrix);
		//40 - percorrer a matriz e comparar com a linha do cliente alvo, NOTA - por questões de eficiência, simplicidade e redundância do código
			//separei a linha do cliente alvo do resto da matriz armazenado-a no vector<bool> target
		target = matrix[client_index];//copiar a linha do cliente alvo
		map_clientes_matriz.erase(map_clientes_matriz[clientes[client_index].get_client_id()]);
		matrix.erase(matrix.begin() + client_index);//removê-la da matriz
		//50 - isolar alvos com melhor correspondência
		important_lines = matrix;
		intersect_matrix_and_target(important_lines, target);
		client_matches = get_count_true_values(important_lines);
		//print_matrix(matrix);
		//print_matrix(important_lines);
		//flip every value in the target vector to prepare it to intersect with the matrix
		target.flip();

		uint i = get_max(client_matches);//starts by the clients with the larger number of matches

		while (i >= 1 && !found) {
			important_lines = get_lines_with_given_count(matrix, client_matches, i);//gets only the lines of the matrix that correspond to clients with i matches
			//print_matrix(important_lines);
			if (important_lines.size() > 0) {
				//intersect again, since it was flipped the column(s) that has(have) the most true values correspond to the product(s) to display
				intersect_matrix_and_target(important_lines, target);

				//transpose to reutilize the get_count_true_values function
				transpose(important_lines);

				//print_matrix(matrix); //for debugging
				//get the best item from the clients that are the current best matches
				vector<uint> items_matches = get_count_true_values(important_lines);
				maximum_items = get_max(items_matches);

				if (maximum_items > 0) {
					found = true;
					for (size_t j = 0; j < produtos.size(); j++) {
						if (items_matches[j] == maximum_items) {
							count_best++;
							cout << "Best match #" << count_best << ": " << produtos[j] << endl;
						}
					}
				}
			}
			i--;
		}

		if (count_best == 0) {
			cout << "Infelizmente nao ha dados suficientes para fazer uma recomendacao para este cliente" << endl;
		}
	}
}

bool Loja::comparar_map_s_i(const pair<string, int>  & a, const pair<string, int> & b) {
	return a.second != b.second ? a.second > b.second : a.first > b.first;
}
void Loja::publicidade_bottom10() {
	if (clientes.size() > 10) {
		Cliente::ordenar(clientes, 1);
		atualizar_map_clientes();
		//vector<Cliente> bottom10(clientes.begin(), clientes.begin() + 10);//desnecessario, basta percorrer os primeiros 10 depois de ordenados
		map<string, int> produtos_bottom10;
		//vector<string> produtos_bottom10_comuns_a_todos;
		vector<size_t> index_clientes_interessantes;
		map<string, int> histograma;
		vector<string> histograma_interessantes;//guarda os produtos interessantes que nenhum bottom 10 comprou

	//guardar os produtos dos bottom10
		//copy(clientes.begin(), clientes.begin() + 10, bottom10.begin());//copia os 10 primeiros, ou seja, os bottom 10
		for (size_t i = 0; i < 10; i++) {//percorre os primeiros 10 clientes
			pair<mm_it, mm_it> range = mmap_compras.equal_range(clientes[i].get_client_id());//obter as compras de cada cliente bottom 10
			for (mm_it j = range.first; j != range.second; j++) {//iterar essas compras
				vector<string> produtos_temp = compras[j->second].get_produtos();
				for (size_t k = 0; k < produtos_temp.size(); k++) {//percorrer os produtos do cliente bottom10
					produtos_bottom10[produtos_temp[k]]++;
					//adiciona o produto e conta o numero de ocorrencias de cada produto, se for 10 quer dizer que e comum a todos os bottom10	
				}
			}
		}

	//encontrar os clientes interessantes e respetivos produtos relevantes
		for (size_t i = 10; i < clientes.size(); i++) {//percorrer os clientes nao bottom 10
			pair<mm_it, mm_it> range = mmap_compras.equal_range(clientes[i].get_client_id());//obter as compras de cada um destes clientes
			vector<string> produtos_cliente;
			for (mm_it j = range.first; j != range.second; j++) {//percorrer essas compras
				vector<string> produtos_temp = compras[j->second].get_produtos();//produtos de cada compra
				produtos_cliente.insert(produtos_cliente.end(), produtos_temp.begin(), produtos_temp.end());
			}

			bool match_all = true;
			auto pos = produtos_bottom10.begin();

			while (match_all && pos != produtos_bottom10.end()) {//averiguar se todos os produtos dos bottom 10 estao neste cliente
				match_all &= find(produtos_cliente.begin(), produtos_cliente.end(), pos->first) != produtos_cliente.end();
				pos++;
			}

			if (match_all) {//Se este cliente comprou todos os dos bottom 10
				for (auto k = produtos_bottom10.begin(); k != produtos_bottom10.end(); k++) {
					if (k->second == 10) {//vai remover os que estao em todos os bottom 10
						produtos_cliente.erase(remove(produtos_cliente.begin(), produtos_cliente.end(), k->first), produtos_cliente.end());//elimina os que estao nos bottom 10
					}
				}
				if (produtos_cliente.size() > 0) {//Se este cliente tiver pelo menos +1 produto que todos os bottom 10 depois da remocao -> cliente interessante
					cout << "cliente interessante: " << clientes[i].get_nome() << endl;
					index_clientes_interessantes.push_back(i);
					for (size_t k = 0; k < produtos_cliente.size(); k++) {
						histograma[produtos_cliente[k]]++;//conta a frequencia deste produto e ordena-o no histograma
					}
				}
			}
		}

	//adiciona ao histograma_interessantes os produtos 
		for (auto prod = histograma.begin(); prod != histograma.end(); prod++) {//percorrer o histograma
			auto found_pos = produtos_bottom10.find(prod->first);//procura este produto nos produtos dos bottom 10
			if (found_pos == produtos_bottom10.end()) {//nao esta no bottom 10
				histograma_interessantes.push_back(prod->first);//guarda os produtos dos clientes interessantes que nao sao de nenhum bottom 10
			}
		}

	//tentar primeira condicao
		if (histograma_interessantes.size() > 0) {
			//mostrar o primeiro produto para a publicidade
			auto prod = histograma_interessantes.rbegin();//iterate reverse order
			uint best_frequency = histograma[*prod];//obter a frequencia do melhor
			cout << endl << "Produto para publicidade: " << endl << endl << setw(TEXT_SETW) << *prod << ", com frequencia: " << histograma[*prod] << endl << endl;
			uint contar = 0;

			//contar quantos tem a mesma frequencia que o 1o da lista
			prod++;
			while (prod != histograma_interessantes.rend() && histograma[*prod] == best_frequency) {
				contar++;
				prod++;
			}
			/*alternativa
			for (prod++; prod != histograma_interessantes.rend(); prod++) {
				if (histograma[*prod] == best_frequency) {
					contar++;
				} else {
					break;
				}
			}*/

			if (contar > 0) {
				cout << "Ha " << contar << " outro(s) produto(s) com igual frequencia, sugerimos que os considere a todos!" << endl;
			}

			//mostrar todos os produtos, caso o utilizador queira e caso existam
			if (histograma_interessantes.size() > 1) {//ver se ha mais produtos interessantes
				if (yes_no_question("Deseja ver os restantes produtos e frequencias?")) {
					prod = histograma_interessantes.rbegin();
					for (prod++; prod != histograma_interessantes.rend(); prod++) {
						cout << "Produto : " << setw(DATA_SETW) << *prod << " |  freq: " << setw(NUMBER_SETW) << histograma[*prod] << endl;
					}
					cout << endl;
				}
			}
		} else {//a primeira nao resultou -> tentar segunda
			//Nesta parte o histograma vai ter os produtos dos clientes interessantes com a respetiva frequencia
				//depois para cada ocorrencia nos bottom 10 essa frequencia diminui 1 unidade, ou seja, 
				//o produto do histograma com a maior frequencia sera o o produto mais frequente entre 
				//os clientes interessantes e menos frequente entre os Bottom10
			cout << "Nao houve nenhum produto para a condicao 1, a procurar para a condicao 2..." << endl;
			histograma.clear();//limpar histograma

			for (size_t i = 0; i < index_clientes_interessantes.size(); i++) {//percorrer clientes interessantes
				//obter as compras de cada cliente interessante
				pair<mm_it, mm_it> range = mmap_compras.equal_range(clientes[index_clientes_interessantes[i]].get_client_id());
				for (mm_it j = range.first; j != range.second; j++) {//percorrer compras dos clientes interessantes
					//vector<string> produtos_temp = compras[j->second].get_produtos();
					size_t max = compras[j->second].size();
					for (size_t k = 0; k < max; k++) {//percorrer as compras
						histograma[compras[j->second](k)]++;//atualiza a frequencia, adcionando
					}
				}
			}

		//copiar os produtos bottom 10 para o histograma com as respetivas frequencias
			for (auto i = produtos_bottom10.begin(); i != produtos_bottom10.end(); i++) {
				histograma[i->first] -= i->second;//atualiza a frequencia, removendo
			}

			vector<pair<string, int>> copia_histograma(histograma.begin(), histograma.end());
			sort(copia_histograma.begin(), copia_histograma.end(), Loja::comparar_map_s_i);//ordenar pelo valor da key
			cout << "Eis os produtos sugeriveis ordenados por ordem decrescente de relevancia:" << endl
				<< "[A frequencia e calculada somando a frequencia do produto nos clientes interessantes e subtraindo a frequencia do produto nos cliente bottom10]" << endl;
			for (size_t i = 0; i < copia_histograma.size(); i++) {
				cout << "Produto : " << setw(DATA_SETW) << copia_histograma[i].first
					<< " |  freq: " << setw(NUMBER_SETW) << copia_histograma[i].second << endl;
			}
		}


	} else {
		cout << "Ha menos de 10 clientes logo nao e possivel realizar esta acao, por nao ser possivel encontrar os clientes relevantes" << endl;
	}

}
