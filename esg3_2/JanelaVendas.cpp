// Internal Images and assets
#include "assets.h"

// Definitions and globals
#include"globais.h"

#include"JanelaVendas.h"

#include "Core.h"


#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>


// Classe utilizada
#include "CVenda.h"
#include "CProduto_Venda.h"

const int fixedWidth = 50;
const int defaultHeight = 25;

//-------------------------- FUNCOES QUE ESTA JANEAL PODE CHAMAR -------------------------------
void DesenhaJanelaInserirVenda(Fl_Widget*, void*);		
void DesenhaJanelaConsultarVenda(int PK_VENDA);
//-------------------------- FUNCOES QUE ESTA JANEAL PODE CHAMAR -------------------------------																						

// ----------------Widgets da janela
Fl_Button *detalhes_venda,*modificar_venda, *excluir_venda, *inserir_venda, *sair_venda;
Fl_Browser *b_vendas;
Fl_Window *janelaVendas;



//-------------------------- Funcoes da janela  ------------------------------------------------

int pk_selecionada_tabela_vendas() // retirn -1 se nao achou, senao retorna um numero inteiro positivo
{
	char *token;
	char linha_selecionada[128];
	char *linha_browser = (char*)b_vendas->text(b_vendas->value());

	if(linha_browser)
	{
		strcpy(linha_selecionada, linha_browser);
		token = strtok(linha_selecionada," \t");
		return atoi(token);
		
	}
	else return -1;
}
void desenha_tabela_vendas()
{
	if(b_vendas)
	{
		if(b_vendas->size())
			b_vendas->clear();

		// preenche a "lista" de venda no FLTK
		int pk_vec_size;
		int *pk_vec = get_pk_vector("ID", "VENDAS", "ORDER BY ID DESC", &pk_vec_size);
		for(int i = 0; i < pk_vec_size; i++)
		{
			char table_label[128];
			Venda venda(pk_vec[i]); // pega um venda com essa PK

			sprintf(table_label,"%d\t\t%s", venda.getid(), venda.getdate());
			b_vendas->add(table_label);
		}
		free(pk_vec); // IMPORTANTE!!!
	}
}
void cb_fechar_janelaVendas(Fl_Widget*, void*)
{
	janelaVendas->hide();
	delete janelaVendas;
	b_vendas = 0;
	janelaVendas = 0;
}

//-------------------------- Funcoes da janela  ------------------------------------------------

void cb__consultar_informacoes_venda(Fl_Widget*, void*)
{
	DesenhaJanelaConsultarVenda(pk_selecionada_tabela_vendas());	
}
//-------------------------- Callbacks da janela  ------------------------------------------------



//-------------------------- Callbacks da janela  ------------------------------------------------
void DesenhaJanelaVendas(Fl_Widget*, void*)
{
	if(janelaVendas && janelaVendas->active()) // já existe, cai fora;
		return;

    janelaVendas = new Fl_Double_Window(1200, 620, "Vendas");
	janelaVendas->callback(cb_fechar_janelaVendas);

	b_vendas = new Fl_Browser(10, 110, 1180, 505, "Tabela Vendas");
	b_vendas->align(Fl_Align(37));
	b_vendas->type(FL_HOLD_BROWSER);

	desenha_tabela_vendas();

	inserir_venda = new Fl_Button(10, 10, 140, 70, "Novo");
	inserir_venda->callback(DesenhaJanelaInserirVenda);
	inserir_venda->image(image_inserir_produto); // arrumar depois

	detalhes_venda = new Fl_Button(160, 10, 140, 70, "Informacoes");
	//detalhes_venda->callback(cb_detalhes_venda);
	detalhes_venda->image(image_search);
	detalhes_venda->callback(cb__consultar_informacoes_venda);

    excluir_venda = new Fl_Button(310, 10, 140, 70, "Excluir");
	//excluir_venda->callback(cb_excluir_venda);
	excluir_venda->image(image_Delete);
	sair_venda = new Fl_Button(1050, 10, 140, 70, "Sair");
	sair_venda->tooltip("Fechar janela de vendas.");
	sair_venda->callback(cb_fechar_janelaVendas);
	sair_venda->image(image_exit);
    
    janelaVendas->resizable(b_vendas);
    janelaVendas->end();
    janelaVendas->show();
}