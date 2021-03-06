// generated by Fast Light User Interface Designer (fluid) version 1.0302

#include "Core.h"
#include "CVenda.h"
#include "CProduto.h"
#include "CProduto_Venda.h"

// Widgets da janela
Fl_Browser *produtos_vendidos, *informacoes_gerais_venda;
Fl_Button *confirmar_consulta;
Fl_Double_Window* JanelaConsultarVenda;




void desenha_tabela_produto_vendas()
{
	if(produtos_vendidos)
	{
		if(produtos_vendidos->size())
			produtos_vendidos->clear();

		// preenche a "lista" de venda no FLTK
		int pk_vec_size;
		int *pk_vec = get_pk_vector("ID", "PRODUTOS_VENDAS", "ORDER BY ID", &pk_vec_size);
		for(int i = 0; i < pk_vec_size; i++)
		{
			char table_label[128];
			Produto_Venda produto_da_venda(pk_vec[i]); // pega um venda com essa PK
			Produto produto (produto_da_venda.getid_produto());
			sprintf(table_label,"%d\t%s", produto_da_venda.getid(),produto.getNome());
			produtos_vendidos->add(table_label);
		}
		free(pk_vec); // IMPORTANTE!!!
	}
}

void DesenhaJanelaConsultarVenda(int PK_VENDA)		
{
	JanelaConsultarVenda = new Fl_Double_Window(680, 602);
	confirmar_consulta = new Fl_Button(505, 545, 140, 35, "Ok");
	
	produtos_vendidos = new Fl_Browser(25, 230, 620, 290, "Produtos vendidos");
	produtos_vendidos->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));
  
	informacoes_gerais_venda = new Fl_Browser(25, 25, 620, 175, "Informa\303\247\303\265""es gerais");
	informacoes_gerais_venda->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));

	desenha_tabela_produto_vendas();

	JanelaConsultarVenda->end();
	JanelaConsultarVenda->show();
}




