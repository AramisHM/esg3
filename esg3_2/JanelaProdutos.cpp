// Internal Images and assets
#include "assets.h"

// Definitions and globals
#include"globais.h"

#include"JanelaProdutos.h"

#include "Core.h"

Fl_Browser *b_produto;
Fl_Window *janelaProduto;


#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>


const int fixedWidth = 50;
const int defaultHeight = 25;


//-------------------------- FUNCOES QUE ESTA JANELA PODE CHAMAR -------------------------------
void DesenhaJanelaInserirProduto(Fl_Widget*, void*);											//
void DesenhaJanelaDetalhesProduto(int PK);														//
void DesenhaJanelaDetalhesProdutoExcluir(int PK);												//
//-------------------------- FUNCOES QUE ESTA JANELA PODE CHAMAR -------------------------------																						


//-------------------------- Callbacks da janela  ------------------------------------------------
void cb_detalhes_produto(Fl_Widget*, void*)
{
	const char *token;
	char linha_selecionada[256];
	char *chave_pk;
	token = b_produto->text(b_produto->value());
	if(token)
	{
		strcpy(linha_selecionada,token);

		chave_pk=strtok(linha_selecionada,"\t"); // faz um unico strtok e cata o primeiro elemento separado por '\t', nesse caso é a PK Código!
		printf("Chave PK selecionada %s\n",chave_pk );
		DesenhaJanelaDetalhesProduto(atoi(chave_pk));

	}
	else
		fl_message("Selecione uma linha.");

	
}
void cb_produto_excluir(Fl_Widget*, void*)
{
	const char *token;
	char linha_selecionada[256];
	char *chave_pk;
	token = b_produto->text(b_produto->value());
	if(token)
	{
		strcpy(linha_selecionada,token);

		chave_pk=strtok(linha_selecionada,"\t"); // faz um unico strtok e cata o primeiro elemento separado por '\t', nesse caso é a PK Código!
		printf("Chave PK selecionada %s\n",chave_pk );
		DesenhaJanelaDetalhesProdutoExcluir(atoi(chave_pk));
	}
	else
		fl_message("Selecione uma linha antes!");
}
void cb_sair_janela_produto(Fl_Widget*, void*)
{
	janelaProduto->hide();
}
//-------------------------- Callbacks da janela  ------------------------------------------------

void desenha_tabela_produtos()
{
	if(b_produto->active())
	{
		if(b_produto->size())
			b_produto->clear();

		// preenche a "lista" de clientes no FLTK
		int pk_vec_size;
		int *pk_vec = get_pk_vector("ID","PRODUTOS", "ORDER BY NOME DESC", &pk_vec_size);
		for(int i = 0; i < pk_vec_size; i++)
		{
			char table_label[128];
			Produto produto(pk_vec[i]); // pega um cliente com essa PK

			sprintf(table_label,"%d\t\t\t%s", produto.getId(), produto.getNome());
			b_produto->add(table_label);
		}
		free(pk_vec); // IMPORTANTE!!!
	}
}
// ----------------Widgets da janela
Fl_Button *detalhes_produto,*modificar_produto, *excluir_produto,*inserir_produto, *sair_produto;

void DesenhaJanelaProduto(Fl_Widget*, void*)
{	
    janelaProduto = new Fl_Double_Window(1200, 620, "Produtos");
	
	/*
	Fl_Input *label_lista = new Fl_Input(125, 100, 0, 0, "Tabela de Produtos");*/
	b_produto = new Fl_Browser(10, 110, 1180, 505, "Tabela de Produtos");
	b_produto->align(Fl_Align(37));
	b_produto->type(FL_HOLD_BROWSER);


	desenha_tabela_produtos();

	inserir_produto = new Fl_Button(10, 10, 140, 70, "Inserir Novo Produto");
	inserir_produto->callback(DesenhaJanelaInserirProduto);
	inserir_produto->image(image_inserir_produto);
	detalhes_produto = new Fl_Button(160, 10, 140, 70, "Detalhes do Produto");
	detalhes_produto->callback(cb_detalhes_produto);
	detalhes_produto->image(image_search);
    excluir_produto = new Fl_Button(310, 10, 140, 70, "Excluir Produto");
	excluir_produto->callback(cb_produto_excluir);
	excluir_produto->image(image_Delete);
	sair_produto = new Fl_Button(1050, 10, 140, 70, "Sair");
	sair_produto->tooltip("Fechar janela de produto.");
	sair_produto->callback(cb_sair_janela_produto);
	sair_produto->image(image_exit);

    janelaProduto->resizable(b_produto);
    janelaProduto->end();
    janelaProduto->show();
}