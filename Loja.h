#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "defs.h"
#include "Cliente.h"
#include "Produto.h"
#include "Compra.h"
using namespace std;

typedef multimap<uint, size_t>::iterator mm_it;

class Loja {
private:
	string f_clientes, f_compras, f_produtos;//caminho para os ficheiros
	bool clientes_por_atualizar, compras_por_atualizar;//bools que indicam se houve alterações a guardar nos ficheiro
	static uint last_client_id;//guarda o ultimo id para saber qual será o do próximo a ser adicionado
	vector<Cliente> clientes;
	vector<Produto> produtos;
	vector<Compra> compras;
	map<string, size_t> map_clientes;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
	map<string, size_t> map_produtos;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
	multimap<uint, size_t> mmap_compras; // multimap para "traduzir" o id do cliente nos indices das suas compras no vetor de compras
public:
	//construtor(es)
	Loja();
	//funcoes principais
	void ler_ficheiros();
	void ler_ficheiro(string file_type, string &file_name);// , bool (Loja::*funcao_leitura)());
	bool ler_clientes();
	bool ler_produtos();
	bool ler_compras();
	void lista_produtos();
	void estatisticas();
	void guardar_ficheiros(bool exit = false);
	bool guardar_clientes(bool exit = false);
	bool guardar_compras();
//acoes clientes
	int ler_cliente_index();
	void atualizar_map_clientes();
	inline void guardar_cliente_map(Cliente temp, size_t index);
	void recalcular_compras();//recalcula o total de compras
	bool client_existe(string temp);
	void adicionar_cliente();
	void editar_cliente();
	void eliminar_cliente();
	void info_cliente();
	void mostrar_info_cliente(int client_index);
	void lista_clientes();
	void lista_pior_melhor();
//acoes compras
	inline void Loja::guardar_compra_mmap(uint id, size_t index);
	void adicionar_compra();
	void eliminar_compra();
	void lista_compras_cliente(int cliente_id);
	void lista_compras_todas();
	void lista_compras_dia();
	void lista_compras_intervalo();
//acoes publicidade
	void lista_bottom10();
	/**
	Print matrix of bools for debug purposes
	@param matrix to print
	@function return value: (none)
	*/
	void Loja::print_matrix(const vector<vector<bool>> &matrix);
	/**
	Fill the matrix of booleans with each line being a client and each column an item, the value of a cell is true if the client bought the item
	Returns:
	@param matrix - the matrix to fill to
	@function return value: (none)
	*/
	void read_matrix(vector<vector<bool>> &matrix, map<size_t, size_t> &map_clientes_matriz);
	/**
	Gets the result of matrix[line] ^ target, for each line in the matrix, works like a boolean && for the entire matrix and a vector
	@param target vector of boolean values
	Returns:
	@param matrix the matrix whose lines will be intersected with the target, the number of columns should match the vector
	@function return value: (none)
	*/
	void intersect_matrix_and_target(vector<vector<bool>> &matrix, const vector<bool> &target);
	/**
	Count the number of times the value true is in each line of a matrix and adds it to a vector<uint>
	@param matrix to process
	@function return value: a vector with the total count of each line of the matrix in each of its lines
	*/
	vector<uint> get_count_true_values(const vector<vector<bool>> &matrix);
	/**
	returns a matrix with only the clients for a given count of matches to the target, each line is a client
	@param matrix - the matrix to extract from
	@param client_matches contains the count of 'true' values of each line of the matrix in each of its lines
	@given_count the value of count of 'true' in the clients to return
	Returns:
	@function return value: matrix with the clients (that have exactly 'given_count' matches with the target) in each line
	*/
	vector<vector<bool>> get_lines_with_given_count(const vector<vector<bool>> &matrix, const vector<uint> &client_matches, const uint given_count);
	/**
	Perform the custom advertising algorithm to obtain the item(s), if any, that should be suggested to a certain client, the target
	Prompts for the target client
	Reads the client's item's into a matrix
	Removes the target line from the matrix and into a vector
	Intersects each line of the matrix with the target, this way the count of 'true' values in each line corresponds to the number of
	items that the client in that line has in common with the target
	Get the vector client_matches in which each line has the count of 'true' in the matrix's lines
	(the number of matches the client in each line has with the target)
	Flip the boolean values in target and intersect it with the ORIGINAL matrix, this way the items the user
	already bought are false and will return false in the intersect operation
	Perform a while loop that iterates from the clients with the largest value of matches with the target until the one with less
	(but at least one item in common)
	FOR EACH ITERACTION:
	.Get the lines of the original matrix that correspond to the number of matches being analyzed into another matrix, important_lines
	.Intersect this new matrix with the flipped target vector->this operation allows us to know which products the other
	clients in important_lines bought that the target didn't, as they correspond to 'true' in this intersection
	.Since now the values we want to count are in the columns and we already had a function to count the number of 'true'
	in the lines of a matrix, important_lines is transposed and we call the same function to count the true values
	this values are the items that the target did't buy and the clients in important_lines bought
	.Evaluate whether this iteraction provided any items (the other clients coul have the exact same items of the target, or less)
	If there was any item exit while loop
	Else iterate again but now the number of matches decreases by one (since it started the verification with the largest number of matches)
	Print the items that correspond to this max or, in other words, the best suggestions for the target
	(or another message if there were no possible suggestions)
	@function return value: (none)
	*/
	void publicidade_cliente();
	static bool comparar_map_s_i(const pair<string, int>  & a, const pair<string, int> & b);
	void publicidade_bottom10();
};