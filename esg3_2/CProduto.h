#ifndef CPRODUTO_H
#define CPRODUTO_H

class Produto 
{
	private:
		int id;
		char nome[128];
		float valor;
		int quantidade;
		char categoria[128];
		char descricao[128];
	public:
		//Construtores e Destrutores
		Produto(int nid, char *nnome, float nvalor = 0, int nquantidade = 0, char *ncategoria = 0, char *ndescricao = 0);
		Produto(int existing_pk);
		~Produto();


		//Getters
		int   getId			();
		char* getNome		();
		float getValor		();
		int   getQuantidade	();
		char* getCategoria	();
		char* getDescricao	();

		//Setters
		void setId			(int id);
		void setNome		(char *nome);
		void setValor		(float valor);
		void setQuantidade	(int quantidade);
		void setCategoria	(char *categoria);
		void setDescricao	(char *descricao);

		//Setter Geral
		void setAll         (int id, char *nome, float valor, int quantidade, char *categoria, char *descricao);

		// Métodos especiais para banco de dados
		int sql_insert_produto();
			
		// Atualiza a instancia produto
		int sql_update_produto();
		
		// Deleta a instancia produto especificada na tabela
		int sql_delete_produto();
};

#endif