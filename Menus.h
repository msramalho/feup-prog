#pragma once

#include <iostream>

#include "defs.h"
#include "utils.h"
#include "Loja.h"

using namespace std;

usi ler_opcao_menu_global();
void menu_global(Loja &supermercado);

usi ler_opcao_menu_clientes();
void menu_clientes(Loja &supermercado);

usi ler_opcao_menu_compras();
void menu_compras(Loja &supermercado);

usi ler_opcao_menu_publicidade();
void menu_publicidade(Loja &supermercado);

inline void clear_console();
void continue_program();
