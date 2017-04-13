/*
	Grupo 3 Engenharia de Software

	Nome do produto: G3Vendas
	Data de início de desenvolvimento: 31/10/2014

	Desenvolvedores
		Aramis Hornung Moraes - Programmer lead
		Alexandre Martins	  - Programmer executive
		Erick Muller		  - Programmer hu3
*/

// Recursos da splash screen
#include "Splash.h"

#include "globais.h"
#include "Home.h"
#include "Core.h"
#include "JanelaLogin.h"


int main()
{	
	ShowWindow( GetConsoleWindow(), SW_HIDE );
	CSplash splash1(TEXT(".\\splash1.bmp"), RGB(128, 128, 128));
	splash1.ShowSplash();

	InicializarBancoDeDados();

	Sleep(2000);
	splash1.CloseSplash();
	
	DesenhaJanelaLogin();

	
	

	DesenhaJanelaHome(0,0);

	while(Fl::check())
	{}
	return 1;
}