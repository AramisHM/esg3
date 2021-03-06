// generated by Fast Light User Interface Designer (fluid) version 1.0302
#include "JanelaProdutos.h"
#include "Globais.h"			// fltk includes, and images assets
#include "Core.h"				// time() sqlite functions and more

Fl_Double_Window* JanelaInserirProduto; //Widget da Janela
// Widgets na janela
Fl_Input	*nome_produto_inserir,
			*valor_produto_inserir,
			*quantidade_produto_inserir,
			*categoria_produto_inserir,
			*descricao_produto_inserir;
Fl_Button	*gravar_produto_inserir,
			*cancelar_produto_inserir;

void cancelar_window_callback_produto(Fl_Widget*, void*)
{
	int hotspot = fl_message_hotspot();
	fl_message_hotspot(0);
	fl_message_title("Aviso");
	int rep = fl_choice("Deseja mesmo cancelar o cadastro?", 
		"Cancelar", "Sair", "N�o sei...");
	fl_message_hotspot(hotspot);
	if (rep==1) {
		JanelaInserirProduto->hide();
	}
	else if (rep==2)
		fl_message("Bom, talvez voce devesse saber antes de cancelar...");
}

// Fun��o a se executar para o SQL
void INSERIR_PRODUTO(Fl_Widget*, void*)
{

	int PK_VAL;
	PK_VAL = rand();
	Produto novo_produto(PK_VAL, (char*) nome_produto_inserir->value(), atof(valor_produto_inserir->value()), atoi(quantidade_produto_inserir->value()),
							     (char*) categoria_produto_inserir->value(), (char*) descricao_produto_inserir->value());
	novo_produto.sql_insert_produto();
	desenha_tabela_produtos();
	
	
}

void DesenhaJanelaInserirProduto(Fl_Widget*, void*)
{
	// Inicializa a interface gr�fica
	JanelaInserirProduto = new Fl_Double_Window(670, 300, "Cadastro de Produtos- G3Software");

	nome_produto_inserir = new Fl_Input(105, 110, 340, 25, "Nome:");
	nome_produto_inserir->tooltip("Nome do produto.");
	nome_produto_inserir->color((Fl_Color)231);

	valor_produto_inserir = new Fl_Input(535, 110, 115, 25, "Valor (R$):");
	valor_produto_inserir->tooltip("Valor do produto.");
	valor_produto_inserir->color((Fl_Color)231);
	
	categoria_produto_inserir = new Fl_Input(105, 140, 340, 25, "Categoria:");
	categoria_produto_inserir->tooltip("Categoria do Produto");
	
	quantidade_produto_inserir = new Fl_Input(535, 140, 115, 25, "Quantidade:");
	quantidade_produto_inserir->tooltip("Quantidade de unidades do produto.");

	descricao_produto_inserir = new Fl_Input(105, 170, 545, 65, "Descri\303\247\303\243o:");
	descricao_produto_inserir->tooltip("Descricao do Produto.");

	gravar_produto_inserir = new Fl_Button(510, 260, 135, 25, "Gravar");
	gravar_produto_inserir->tooltip("Gravar");
	gravar_produto_inserir->shortcut(0xff0d);
	gravar_produto_inserir->align(Fl_Align(256));
	gravar_produto_inserir->image(image_save);
	gravar_produto_inserir->callback(INSERIR_PRODUTO);
	
	cancelar_produto_inserir = new Fl_Button(370, 260, 135, 25, "Cancelar");
	cancelar_produto_inserir->tooltip("Cancelar");
	cancelar_produto_inserir->shortcut(0xff0d);
	cancelar_produto_inserir->align(Fl_Align(256));
	cancelar_produto_inserir->image(image_decline);
	cancelar_produto_inserir->callback(cancelar_window_callback_produto);


	Fl_Group* bg_logo = new Fl_Group(0, 0, 670, 100);
	bg_logo->image(image_default_bg); // default in code image

	bg_logo->align(Fl_Align(FL_ALIGN_CENTER));
	bg_logo->end();


	JanelaInserirProduto->show();
	JanelaInserirProduto->end();
}
