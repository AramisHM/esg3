// generated by Fast Light User Interface Designer (fluid) version 1.0302
#include "JanelaVendas.h"
#include "Globais.h"			// fltk includes, and images assets
#include "Core.h"				// time() sqlite functions and more



// Widgets na janela
Fl_Double_Window *janelaInserirVendas;
Fl_Input *id_produto, *quantidade;
Fl_Browser *lista_produtos;
Fl_Output *nomeProduto, *subtotal,*preco_unitario;
Fl_Button *adicionar, *pesquisar, *finalizar_venda,*cancelar_venda;

int PK_PRODUTO_VENDA;
Produto *prod_selecionado;

void cb_pesquisar_produto(Fl_Widget*, void*)
{
	char auxiliar[32];
	PK_PRODUTO_VENDA = atoi(id_produto->value());
	prod_selecionado = new Produto(PK_PRODUTO_VENDA);

	sprintf (auxiliar, "%.2f", prod_selecionado->getValor());
	nomeProduto->value(prod_selecionado->getNome());
	preco_unitario->value(auxiliar);
	quantidade->value("1");
}

void cb_adicionar_produto(Fl_Widget*, void*)
{
	int VENDA_PK_VAL, PRODUTO_VENDA_PK_VAL;
	VENDA_PK_VAL = rand();
	PRODUTO_VENDA_PK_VAL = rand();
	// Variaveis para data de hoje ---------------------------------
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* today = ctime(&now);
	tm *gmtm = gmtime(&now);
	today = asctime(gmtm);
	// Variaveis para data de hoje ---------------------------------

	Venda nova_venda(VENDA_PK_VAL,0,today, atof(subtotal->value()), "Sem Observacao", "Indefinido", 0);
	nova_venda.sql_insert_venda();

	Produto_Venda produto_venda(PRODUTO_VENDA_PK_VAL, VENDA_PK_VAL, atoi(id_produto->value()), prod_selecionado->getValor(), atoi(quantidade->value()));
	produto_venda.sql_insert_produto_venda();

	float auxiliar_sub_total = atoi(quantidade->value()) * atof(preco_unitario->value());
	char auxiliar[128];
	sprintf (auxiliar, "%s - %s - %sx - %.2f", id_produto->value(), nomeProduto->value(), quantidade->value(), auxiliar_sub_total); 
	lista_produtos->add(auxiliar);
	float auxiliar_total_venda = atof(subtotal->value()) + auxiliar_sub_total;
	sprintf (auxiliar, "%.2f", auxiliar_total_venda); 
	subtotal->value(auxiliar);
}

void cancelar_venda_window_callback_venda(Fl_Widget*, void*)
{
	int hotspot = fl_message_hotspot();
	fl_message_hotspot(0);
	fl_message_title("Aviso");
	int rep = fl_choice("Deseja mesmo cancelar o cadastro?", 
		"Cancelar", "Sair", "N�o sei...");
	fl_message_hotspot(hotspot);
	if (rep==1) {
		janelaInserirVendas->hide();
	}
	else if (rep==2)
		fl_message("Bom, talvez voce devesse saber antes de cancelar...");
}

// Fun��o a se executar para o SQL
void cb_finalizar_venda(Fl_Widget*, void*)
{
	desenha_tabela_vendas();
	janelaInserirVendas->hide();
}

void DesenhaJanelaInserirVenda(Fl_Widget*, void*)		
{
	janelaInserirVendas = new Fl_Double_Window(860, 560);

	id_produto = new Fl_Input(10, 10, 705, 90, "ID Produto");
	id_produto->type(4);
	id_produto->labeltype(FL_ENGRAVED_LABEL);
	id_produto->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));

	pesquisar = new Fl_Button(730, 10, 110, 90, "Pesquisar Produto");
	pesquisar->align(Fl_Align(FL_ALIGN_WRAP));
	pesquisar->callback(cb_pesquisar_produto);

	lista_produtos = new Fl_Browser(550, 120, 290, 285, "Lista itens");
	lista_produtos->labeltype(FL_ENGRAVED_LABEL);
	lista_produtos->align(Fl_Align(FL_ALIGN_TOP_LEFT));

	subtotal = new Fl_Output(550, 415, 290, 55, "SubTotal R$: ");
	subtotal->type(12);
	subtotal->labeltype(FL_ENGRAVED_LABEL);
	subtotal->textfont(5);
	subtotal->textsize(30);
	subtotal->textcolor((Fl_Color)108);

	nomeProduto = new Fl_Output(10, 130, 290, 35, "Nome do Produto");
	nomeProduto->labeltype(FL_ENGRAVED_LABEL);
	nomeProduto->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));

	quantidade = new Fl_Input(10, 190, 290, 35, "Quantidade");
	quantidade->labeltype(FL_ENGRAVED_LABEL);
	quantidade->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));

	preco_unitario = new Fl_Output(10, 250, 290, 35, "Pre\303\247o Unit\303\241rio R$");
	preco_unitario->labeltype(FL_ENGRAVED_LABEL);
	preco_unitario->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));

	adicionar = new Fl_Button(10, 315, 525, 90, "Adicionar");
	adicionar->callback(cb_adicionar_produto);

	finalizar_venda = new Fl_Button(730, 480, 110, 55, "Finalizar");
	finalizar_venda->callback(cb_finalizar_venda);

	cancelar_venda = new Fl_Button(610, 480, 110, 55, "Cancelar");

	janelaInserirVendas->end();
	janelaInserirVendas->show();
}



