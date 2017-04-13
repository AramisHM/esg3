#ifndef CVENDA_H
#define CVENDA_H

#include "Core.h" // necessario para rodar juntamente com o software. Possui includes do FLTK e bibliotecas standard. stdlib stdio string

class Venda 
{
	private:
		int id; // ID DA VENDA
		int id_cliente; // FK ID DO CLIENTE
		char date[32];
		float valor_total;
		char observacao[512];
		char tipo_pagamento[64]; // cartao cheque etc
		int n_parcelas; // numero de parcelas
		// NOTA: DEPENDENDO DO TAMANHO DA VARAIVEIS ACIMA,
		// CASO SEJE INSUFICIENTE PARA ARMAZENAR OS DADOS,
		// NA HORA DE FAZER SELECT, O DADO PODE SER SOBRESCRITO
		// OU PERDIDO EM UMA OPERAÇÃO STRCPY

	public:

		// construtores e destrutores
		Venda(int nid, int nfkid_cliente, char* ndate = 0, float nvalor_total = 0, char *nobservacao = 0, char *ntipo_pagamento = 0, int nn_parcelas = 0);
		Venda(int existing_pk); // cria uam isntancia a partir do banco de dados, fornecendo a pk da linha
		~Venda(); // destrutor

		//Getters
		int getid(); // ID DA VENDA
		int getid_cliente(); // FK ID DO CLIENTE
		char* getdate();
		float getvalor_total();
		char* getobservacao();
		char *gettipo_pagamento();
		int getn_parcelas();
		
		//Setters
		void setid(int nid); // ID DA VENDA
		void setid_cliente(int nfkid_cliente); // FK ID DO CLIENTE
		void setdate(char* ndate);
		void setvalor_total(float nvalor_total);
		void setobservacao(char *nobservacao);
		void settipo_pagamento(char *ntipo_pagamento);
		void setn_parcelas(int nn_parcelas);

		// Métodos especiais para banco de dados
		int sql_insert_venda(); // nCliente quer dizer newClient caso vc tenha curiosidade
		// Atualiza a instancia cliente
		int sql_update_venda();
		// Deleta a instancia cliente especificada na tabela
		int sql_delete_venda();
};

#endif