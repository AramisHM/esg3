#include "JanelaLogin.h"



// Widgets da janela
Fl_Double_Window *janelaLogin;
Fl_Input *wglogin;
Fl_Input *wgsenha;

// Função a se executar para o SQL
void cb_sair(Fl_Widget*, void*)
{
	exit(1);
}

// Função a se executar para o SQL
void cb_logar(Fl_Widget*, void*)
{
	char nome[128];
	char senha[128];

	strcpy(nome, wglogin->value());
	strcpy(senha, wgsenha->value());

	if (nome && senha)
	{
		// procura o nome
		int indice = 0;
		do
		{
			if (!strcmp(nome, usuarios[indice]))
				break;
			else
				indice++;
		}while(indice < n_usuarios);

		if (indice < n_usuarios)
		{
			if (!strcmp(senhas_usuarios[indice], wgsenha->value()))
				nivel_usuario = prioridades[indice];
			else
			{
				fl_alert("Senha incorreta");
				wglogin->value("");
				wgsenha->value("");
			}

		}
		else
		{
			fl_alert("Usuário inexistente");
			wglogin->value("");
			wgsenha->value("");
		}
	}
}


void DesenhaJanelaLogin()
{
	janelaLogin = new Fl_Double_Window(270, 150, "Login");
	janelaLogin->position((Fl::w()/2)-(janelaLogin->decorated_w()/2),(Fl::h()/2)-(janelaLogin->decorated_h()/2));
	wglogin = new Fl_Input(60,10,180,25,"Login: ");
	wgsenha = new Fl_Input(60,40,180,25,"Senha: ");
	wgsenha->type(FL_SECRET_INPUT);
	Fl_Button *sair = new Fl_Button(90, 70, 70, 60, "Sair");
	sair->tooltip("Sair do programa.");
	sair->image(image_logout);
	sair->callback(cb_sair);

	Fl_Button *entrar = new Fl_Button(170, 70, 70, 60, "Entrar");
	entrar->callback(cb_logar);

	entrar->tooltip("Efetuar login no sistema.");
	entrar->image(image_login);

	//se login admin/admin mostra todos os menus -return 1
	//se login user/user mostra clientes/produtos/vendas -return 1
	//se login errado retorno default 0

	janelaLogin->end();
    janelaLogin->show();
	
	while(!nivel_usuario)
	{
		Fl::check();
	}
	janelaLogin->hide();

	char menssagem_boas_vindas[128];

	sprintf(menssagem_boas_vindas,"Bem vindo %s", wglogin->value());
	fl_alert(menssagem_boas_vindas);
}