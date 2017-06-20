/*
FILE		: main.cpp
DATE		: 2016/05/20
AUTHOR		: up201403027
FACULTY		: Faculdade de Engenharia da Universidade do Porto
COURSE		: Mestrado Integrado em Engenharia Inform�tica e Computa��o
SUBJECT		: PROGRAMA��O
PROGRAM PURPOSE:
- Gerir o um sistema simulado de compras, vendas e publicidade para um loja
- Fornecer organiza��o, facilidade de cria��o de campanhas publicit�rias
- Gerar sugest�es para clientes com base no seu perfil de compras e nos clientes semelhantes
- Identificar e tentar dinamizar o uso da loja no que toca aos 10 piores clientes, Bottom10
*/

#include<iostream>

#include "Menus.h"
#include "Loja.h"
using namespace std;

int main() {
	Loja loja;
	menu_global(loja);
	return 0;
}