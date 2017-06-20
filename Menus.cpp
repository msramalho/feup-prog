#include "Menus.h"


usi ler_opcao_menu_global() {
	usi opcao;
	cout << endl << "Menu Inicial" << endl;
	cout << endl;
	cout << "1 - Gestao de clientes" << endl;
	cout << "2 - Gestao de compras" << endl;
	cout << "3 - Publicidade direcionada" << endl;
	cout << "4 - Lista produtos disponiveis" << endl;
	cout << "5 - Estatisticas" << endl;
	cout << "6 - Guardar Ficheiros" << endl;
	cout << "7 - Sair do programa" << endl << endl;
	cin_value_between(opcao, "Qual a sua opcao?: ", 1, 7);

	return (opcao == 7 ? 0 : opcao);
}
void menu_global(Loja &loja) {
	usi opcao;
	string nome;
	while ((opcao = ler_opcao_menu_global())) {
		switch (opcao) {
		case 1:
			clear_console();
			menu_clientes(loja);
			break;
		case 2:
			clear_console();
			menu_compras(loja);
			break;
		case 3:
			clear_console();
			menu_publicidade(loja);
			break;
		case 4:
			loja.lista_produtos();
			continue_program();
			break;
		case 5:
			loja.estatisticas();
			continue_program();
			break;
		case 6:
			loja.guardar_ficheiros();
			continue_program();
			break;
		}
	}
	loja.guardar_ficheiros(true);
}

usi ler_opcao_menu_clientes() {
	usi opcao;

	cout << endl << "Menu Gestao de Clientes" << endl;
	cout << endl;
	cout << "1 - Adicionar cliente" << endl;
	cout << "2 - Editar cliente" << endl;
	cout << "3 - Eliminar cliente" << endl;
	cout << "4 - Informacao cliente" << endl;
	cout << "5 - Lista clientes (alfabeticamente)" << endl;
	cout << "6 - Lista clientes (de pior para melhor)" << endl;
	cout << "7 - Voltar ao menu inicial" << endl << endl;
	cin_value_between(opcao, "Qual a sua opcao?: ", 1, 7);

	return (opcao == 7 ? 0 : opcao);

}
void menu_clientes(Loja &loja) {
	usi opcao;
	clear_console();
	while ((opcao = ler_opcao_menu_clientes())) {
		switch (opcao) {
		case 1: 
			loja.adicionar_cliente();
			break;
		case 2:
			loja.editar_cliente();
			break;
		case 3:
			loja.eliminar_cliente();
			break;
		case 4:
			loja.info_cliente();
			break;
		case 5:
			loja.lista_clientes();
			break;
		case 6:
			loja.lista_pior_melhor();
			break;
	}
		if (opcao != 0) continue_program();
	}
	clear_console();
}

usi ler_opcao_menu_compras() {
	usi opcao;
	
	clear_console();
	cout << endl << "Menu Gestao de compras" << endl;
	cout << endl;
	cout << "1 - Adicionar compra" << endl;
	cout << "2 - Eliminar compra" << endl;
	cout << "3 - Todos as compras (cronologicamente)" << endl;
	cout << "4 - Todos as compras (cronologicamente) para um dia" << endl;
	cout << "5 - Todos as compras (cronologicamente) para um intervalo de duas datas" << endl;
	cout << "6 - Recalcular compras totais" << endl;
	cout << "7 - Voltar ao menu inicial" << endl << endl;
	cin_value_between(opcao, "Qual a sua opcao?: ", 1, 7);

	return (opcao == 7 ? 0 : opcao);
}
void menu_compras(Loja &loja) {
	usi opcao;
	clear_console();
	while ((opcao = ler_opcao_menu_compras())) {
		switch (opcao) {
		case 1:
			loja.adicionar_compra();
			break;
		case 2:
			loja.eliminar_compra();
			break;
		case 3:
			loja.lista_compras_todas();
			break;
		case 4:
			loja.lista_compras_dia();
			break;
		case 5:
			loja.lista_compras_intervalo();
			break;
		case 6:
			loja.recalcular_compras();
			break;
	}
		if (opcao != 0) continue_program(); 
	}
	clear_console();

}

usi ler_opcao_menu_publicidade() {
	usi opcao;

	cout << endl << "Menu Publicidade Direcionada" << endl;
	cout << endl;
	cout << "1 - Lista Bottom 10" << endl;
	cout << "2 - Publicidade para 1 cliente" << endl;
	cout << "3 - Publicidade para Bottom 10" << endl;
	cout << "4 - Voltar ao menu inicial" << endl << endl;
	cin_value_between(opcao, "Qual a sua opcao?: ", 1, 4);

	return (opcao == 4 ? 0 : opcao);

}
void menu_publicidade(Loja &loja) {
	usi opcao;
	clear_console();
	while ((opcao = ler_opcao_menu_publicidade())) {
		switch (opcao) {
		case 1:
			loja.lista_bottom10();
			break;
		case 2:
			loja.publicidade_cliente();
			break;
		case 3:
			loja.publicidade_bottom10();
			break;
		}
		if (opcao != 0)continue_program();
	}
	clear_console();

}

inline void clear_console() {
	system(CLEAR);
}

void continue_program() {
	char temp;
	cout << "Enter para continuar" << endl;
	temp = cin.get();
	clear_console();
}
