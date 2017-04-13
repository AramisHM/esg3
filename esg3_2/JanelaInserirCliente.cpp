#include "JanelaClientes.h"
#include "Core.h"				// time() sqlite functions and more

Fl_Double_Window* JanelaInserirClientes; //Widget da Janela

// Widgets na janela
Fl_Input *nome,*CEP,*numero, *complemento,*bairro,*Fone,*cnpjcpf,*email,*observ,*rua,*cidade;
Fl_Input_Choice *Pessoa, *estado;
Fl_Button *gravar,*cancelar;

//-------------------------- Callbacks da janela  ------------------------------------------------
void cb_inserir_cliente(Fl_Widget*, void*)
{
	
	int PK_VAL;
	PK_VAL = rand();
	Cliente novo_cliente(PK_VAL, (char*)nome->value(), (char*)Pessoa->value(), (char*)cnpjcpf->value(), (char*)CEP->value(), (char*)cidade->value(),\
						 (char*)bairro->value(), (char*)rua->value(), atoi(numero->value()), (char*)estado->value(),   (char*)complemento->value(),\
						(char*) Fone->value(), (char*)email->value(), (char*)observ->value());
	if(novo_cliente.sql_insert_cliente())
	{
		desenha_tabela_clientes(); // atualiza a tabela
		JanelaInserirClientes->hide();
		JanelaInserirClientes = 0;
	}
	
}
void cb_fechar_JanelaInserirClientes(Fl_Widget*, void*)
{
	JanelaInserirClientes->hide();
	delete JanelaInserirClientes;
	JanelaInserirClientes = 0;
}
//-------------------------- Callbacks da janela  ------------------------------------------------

void populaEstados(){
	estado->add("AC");
	estado->add("AL");
	estado->add("AP");
	estado->add("AM");
	estado->add("BA");
	estado->add("CE");
	estado->add("DF");
	estado->add("ES");
	estado->add("GO");
	estado->add("MA");
	estado->add("MT");
	estado->add("MS");
	estado->add("MG");
	estado->add("PA");
	estado->add("PB");
	estado->add("PR");
	estado->add("PE");
	estado->add("PI");
	estado->add("RJ");
	estado->add("RN");
	estado->add("RS");
	estado->add("RR");
	estado->add("SC");
	estado->add("SP");
	estado->add("SE");
	estado->add("TO");
}
void DesenhaJanelaInserirCliente(Fl_Widget*, void*)
{

	if(JanelaInserirClientes && JanelaInserirClientes->active()) // já existe, cai fora;
		return;

	// Inicializa a interface gráfica
	JanelaInserirClientes = new Fl_Double_Window(670, 545, "Cadastro de Clientes - G3Software");
	JanelaInserirClientes->callback(cb_fechar_JanelaInserirClientes);

	cnpjcpf = new Fl_Input(105, 110, 225, 25, "CNPJ/CPF:");
	cnpjcpf->tooltip("Nome do cliente.");
	cnpjcpf->color((Fl_Color)231);

	Pessoa = new Fl_Input_Choice(535, 110, 115, 25, "Pessoa:");
	Pessoa->add("fisica");
	Pessoa->add("juridica");
	
	nome = new Fl_Input(105, 145, 550, 25, "Nome:");
	nome->tooltip("Nome do cliente.");
	nome->color((Fl_Color)231);
	nome->image(image_people);
	
	CEP = new Fl_Input(105, 210, 160, 25, "CEP:");
	CEP->tooltip("Nome do cliente.");
	CEP->color((Fl_Color)231);

	cidade = new Fl_Input(320, 210, 330, 25, "Cidade:");
	cidade->tooltip("Cidade do cliente.");

	bairro = new Fl_Input(105, 240, 325, 25, "Bairro:");
	bairro->tooltip("Bairro do cliente.");
	
	estado = new Fl_Input_Choice(490, 240, 160, 25, "Estado:");
	populaEstados();

	estado->tooltip("Estado onde reside o cliente.");

	rua = new Fl_Input(105, 270, 325, 25, "Rua:");
	rua->tooltip("Rua onde reside o cliente.");

	numero = new Fl_Input(490, 270, 160, 25, "N\303\272mero:");
	numero->tooltip("N\303\272mero da rua onde reside o cliente.");
    
	complemento = new Fl_Input(105, 300, 545, 25, "Complemento:");
	complemento->tooltip("Complemento da residencia do cliente.");
	
	Fone = new Fl_Input(105, 355, 225, 25, "Fone:");
	Fone->tooltip("Nome do cliente.");
    
	email = new Fl_Input(105, 385, 545, 25, "E-mail:");
	email->tooltip("Nome do cliente.");

	observ = new Fl_Input(105, 425, 545, 65, "Observa\303\247\303\243o:");
	observ->tooltip("Nome do cliente.");

	gravar = new Fl_Button(510, 505, 135, 25, "Gravar");
	gravar->tooltip("Gravar");
	gravar->shortcut(0xff0d);
	gravar->align(Fl_Align(256));
	gravar->image(image_save);
	gravar->callback(cb_inserir_cliente);
	
	cancelar = new Fl_Button(370, 505, 135, 25, "Cancelar");
	cancelar->tooltip("Cancelar cadastro");
	cancelar->callback(cb_fechar_JanelaInserirClientes);
	cancelar->shortcut(0xff0d);
	cancelar->align(Fl_Align(256));
	cancelar->image(image_decline);


	Fl_Group* bg_logo = new Fl_Group(0, 0, 670, 100);
	bg_logo->image(image_default_bg); // default in code image

	bg_logo->align(Fl_Align(FL_ALIGN_CENTER));
	bg_logo->end();


	JanelaInserirClientes->show();
	JanelaInserirClientes->end();
}