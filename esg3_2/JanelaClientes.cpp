// Internal Images and assets
#include "assets.h"

// Definitions and globals
#include"globais.h"

#include"JanelaClientes.h"

#include "Core.h"


#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>


// Classe utilizada
#include "CCliente.h"

const int fixedWidth = 50;
const int defaultHeight = 25;

//-------------------------- FUNCOES QUE ESTA JANEAL PODE CHAMAR -------------------------------
void DesenhaJanelaInserirCliente(Fl_Widget*, void*);											//
void DesenhaJanelaDetalhesCliente(int PK);														//
void DesenhaJanelaExcluirCliente(int PK);														//
//-------------------------- FUNCOES QUE ESTA JANEAL PODE CHAMAR -------------------------------																						

// ----------------Widgets da janela
Fl_Button *detalhes_cliente,*modificar_cliente, *excluir_cliente, *inserir_cliente, *sair_cliente;
Fl_Browser *b_clientes;
Fl_Window *janelaClientes;



//-------------------------- Funcoes da janela  ------------------------------------------------
int pk_selecionada_tabela_clientes() // retirn -1 se nao achou, senao retorna um numero inteiro positivo
{
	char *token;
	char linha_selecionada[128];
	char *linha_browser = (char*)b_clientes->text(b_clientes->value());

	if(linha_browser)
	{
		strcpy(linha_selecionada, linha_browser);
		token = strtok(linha_selecionada," \t");
		return atoi(token);
		
	}
	else return -1;
}
void desenha_tabela_clientes()
{
	if(b_clientes)
	{
		if(b_clientes->size())
			b_clientes->clear();

		// preenche a "lista" de clientes no FLTK
		int pk_vec_size;
		int *pk_vec = get_pk_vector("ID","CLIENTES", "ORDER BY NOME DESC", &pk_vec_size);
		for(int i = 0; i < pk_vec_size; i++)
		{
			char table_label[128];
			Cliente cliente(pk_vec[i]); // pega um cliente com essa PK

			sprintf(table_label,"%d\t\t\t%s\t\t\t%s\t\t\t%s", cliente.getid(), cliente.getnome(), cliente.getbairro(), cliente.getcidade(), cliente.getestado());
			b_clientes->add(table_label);
		}
		free(pk_vec); // IMPORTANTE!!!
	}
}


//-------------------------- Callbacks da janela  ------------------------------------------------
void cb_detalhes_cliente(Fl_Widget*, void*)
{
	int pk = pk_selecionada_tabela_clientes();

	if(pk >= 0)
		DesenhaJanelaDetalhesCliente(pk);
	else
		fl_alert("Selecione uma linha antes!");
}
void cb_excluir_cliente(Fl_Widget*, void*)
{
	//Rotina DELETE
	char message[256];
	int PK_selecionada = pk_selecionada_tabela_clientes();

	if(PK_selecionada >= 0)
	{
		Cliente cliente_selecionado(pk_selecionada_tabela_clientes());

		int hotspot = fl_message_hotspot();
		fl_message_hotspot(0);
		fl_message_title("Aviso");
		sprintf(message,"Tem certeza de que deseja excluir '%s' permanentemente ?",cliente_selecionado.getnome());
		int rep = fl_choice(message, 
			"Nao", "Sim", "Não sei...");
		fl_message_hotspot(hotspot);
		if (rep==1)
		{
			if(cliente_selecionado.sql_delete_cliente())
			{
				desenha_tabela_clientes(); // redesenha.
				fl_alert("Cliente excluido.");
			}
		}
	}
	else
		fl_alert("Selecione uma linha antes!");
}
void cb_fechar_janelaClientes(Fl_Widget*, void*)
{
	janelaClientes->hide();
	delete janelaClientes;
	b_clientes = 0;
	janelaClientes = 0;
}
//-------------------------- Callbacks da janela  ------------------------------------------------

void DesenhaJanelaClientes(Fl_Widget*, void*)
{
	if(janelaClientes && janelaClientes->active()) // já existe, cai fora;
		return;

    janelaClientes = new Fl_Double_Window(1200, 620, "Clientes");
	janelaClientes->callback(cb_fechar_janelaClientes);

	b_clientes = new Fl_Browser(10, 110, 1180, 505, "Tabela Clientes");
	b_clientes->align(Fl_Align(37));
	b_clientes->type(FL_HOLD_BROWSER);

	desenha_tabela_clientes();

	inserir_cliente = new Fl_Button(10, 10, 140, 70, "Novo");
	inserir_cliente->callback(DesenhaJanelaInserirCliente);
	inserir_cliente->image(image_inserir_produto); // arrumar depois
	detalhes_cliente = new Fl_Button(160, 10, 140, 70, "Informacoes");
	detalhes_cliente->callback(cb_detalhes_cliente);
	detalhes_cliente->image(image_search);
    excluir_cliente = new Fl_Button(310, 10, 140, 70, "Excluir");
	excluir_cliente->callback(cb_excluir_cliente);
	excluir_cliente->image(image_Delete);
	sair_cliente = new Fl_Button(1050, 10, 140, 70, "Sair");
	sair_cliente->tooltip("Fechar janela de clientes.");
	sair_cliente->callback(cb_fechar_janelaClientes);
	sair_cliente->image(image_exit);
    
    janelaClientes->resizable(b_clientes);
    janelaClientes->end();
    janelaClientes->show();
}