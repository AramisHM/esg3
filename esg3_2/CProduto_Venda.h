#ifndef CPRODUTO_VENDA_H
#define CPRODUTO_VENDA_H

#include "Core.h" // necessario para rodar juntamente com o software. Possui includes do FLTK e bibliotecas standard. stdlib stdio string

class Produto_Venda 
{
	
	private:
		int id;
		int id_venda; // FK ID DA VENDA
		int id_produto; // FK ID DO PRODUTO
		float valor_unit; // valor unitário, apesar de já existir no produto, os produtos podem mudar de valor ao longo do tempo
		int quantidade; // quantidades do produto acima presente na venda acima
		// NOTA: DEPENDENDO DO TAMANHO DA VARAIVEIS ACIMA,
		// CASO SEJE INSUFICIENTE PARA ARMAZENAR OS DADOS,
		// NA HORA DE FAZER SELECT, O DADO PODE SER SOBRESCRITO
		// OU PERDIDO EM UMA OPERAÇÃO STRCPY

	public:

		// construtores e destrutores
		Produto_Venda(int nid, int nid_venda, int nid_produto, int nvalor_unit = 0, int nquantidade = 0);
		Produto_Venda(int existing_pk); // cria uam isntancia a partir do banco de dados, fornecendo a pk da linha
		~Produto_Venda(); // destrutor

		//Getters
		int getid(); // ID DA VENDA
		int getid_venda(); // FK ID DA VENDA
		int getid_produto(); // FK ID DO PRODUTO
		float getvalor_unit(); // valor unitário, apesar de já existir no produto, os produtos podem mudar de valor ao longo do tempo
		int getquantidade(); // quantidades do produto acima presente na venda acima
		
		//Setters
		void setid(int nid); // ID DA VENDA
		void setid_venda(int nid_venda); // FK ID DA VENDA
		void setid_produto(int nid_produto); // FK ID DO PRODUTO
		void setvalor_unit(int nvalor_unit); // valor unitário, apesar de já existir no produto, os produtos podem mudar de valor ao longo do tempo
		void setquantidade(int nquantidade); // quantidades do produto acima presente na venda acima

		// Métodos especiais para banco de dados
		int sql_insert_produto_venda(); // nCliente quer dizer newClient caso vc tenha curiosidade
		// Atualiza a instancia cliente
		int sql_update_produto_venda();
		// Deleta a instancia cliente especificada na tabela
		int sql_delete_produto_venda();
};

#endif
