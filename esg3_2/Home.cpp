// Internal Images and assets
#include "assets.h"

// Definitions and globals
#include"globais.h"
// Os outros modulos que esta janela consegue chamar
#include "Home.h"
#include "JanelaClientes.h"
#include "JanelaProdutos.h"
#include "JanelaVendas.h"
#include <FL/fl_ask.H>

Fl_Button *clientes, *produtos, *vendas, *contas, *fornecedores;
Fl_Double_Window  *main_window;

void window_callback(Fl_Widget*, void*)
{
	exit(0);
}

void DesenhaJanelaHome(Fl_Widget*, void*)
{
	
	main_window = new Fl_Double_Window(830, 170, titulo_software);

	main_window->position((Fl::w()/2)-(main_window->decorated_w()/2),0); // posiciona a janela no centro superior do monitopr ativo
	clientes = new Fl_Button(20, 5, 150, 150, "Clientes");
	clientes->image(image_Clientes);
	clientes->callback(DesenhaJanelaClientes);
	
	
	produtos = new Fl_Button(180, 5, 150, 150, "Produtos");
	produtos->image(image_Produto);
	produtos->callback(DesenhaJanelaProduto);
	
	vendas = new Fl_Button(340, 5, 150, 150, "Vendas");
	vendas->image(image_Vendas);
	vendas->callback(DesenhaJanelaVendas);
	
	contas = new Fl_Button(500, 5, 150, 150, "Contas");
	contas->image(image_Contas);
	
	fornecedores = new Fl_Button(660, 5, 150, 150, "Fornecedores");
	fornecedores->image(image_Fornecedor);
	
	main_window->callback(window_callback);

    main_window->end();
    main_window->show();
	
}