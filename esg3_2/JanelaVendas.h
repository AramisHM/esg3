#ifndef JANELAVENDAS_H
#define JANELAVENDAS_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Browser.H>

#include "CVenda.h"	// Classe vendas
#include "CProduto.h" //Classe Produtos
#include "CProduto_Venda.h" //Classe Produto_Venda

void DesenhaJanelaVendas(Fl_Widget*, void*);
void desenha_tabela_vendas();

#endif