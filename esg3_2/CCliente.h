#ifndef CCLIENTE_H
#define CCLIENTE_H

#include "Core.h" // necessario para rodar juntamente com o software. Possui includes do FLTK e bibliotecas standard. stdlib stdio string

class Cliente 
{
	private:
		int id;
		char pessoa[32];
		char cpfcnpj[32];
		char nome[128];
		char cep[32];
		char cidade[32];
		char bairro[32];
		char rua[32];
		int numero;
		char estado[32];
		char complemento[32];
		char fone[32];
		char email[128];
		char observacao[128];
		// NOTA: DEPENDENDO DO TAMANHO DA VARAIVEIS ACIMA,
		// CASO SEJE INSUFICIENTE PARA ARMAZENAR OS DADOS,
		// NA HORA DE FAZER SELECT, O DADO PODE SER SOBRESCRITO
		// OU PERDIDO EM UMA OPERAÇÃO STRCPY

	public:

		// construtores e destrutores
		Cliente(int nid, char *nnome, char *npessoa = 0, char *ncpfcnpj = 0, char *ncep = 0, char *ncidade = 0, char *nbairro = 0, char* nrua = 0, int nnumero = 0, char* nestado = 0, char* ncomplemento = 0, char* nfone = 0, char* nemail = 0, char* nobservacao = 0);
		Cliente(int existing_pk); // cria uam isntancia a partir do banco de dados, fornecendo a pk da linha
		~Cliente(); // destrutor

		//Getters
		int getid();
		char* getpessoa();
		char* getcpfcnpj();
		char* getnome();
		char* getcep();
		char* getcidade();
		char* getbairro();
		char* getrua();
		int getnumero();
		char* getestado();
		char* getcomplemento();
		char* getfone();
		char* getemail();
		char* getobservacao();
		
		//Setters
		void setid(int nid);
		void setpessoa(char *npessoa);
		void setcpfcnpj(char *ncpfcnpj);
		void setnome(char *nnome);
		void setcep(char *ncep);
		void setcidade(char *ncidade);
		void setbairro(char *nbairro);
		void setrua(char *nrua);
		void setnumero(int nnumero);
		void setestado(char *nestado);
		void setcomplemento(char *ncomplemento);
		void setfone(char *nfone);
		void setemail(char *nemail);
		void setobservacao(char *nobservacao);




		// Métodos especiais para banco de dados <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< AQUÊ DONA MARÓCAS ! :}}
		int sql_insert_cliente(); // nCliente quer dizer newClient caso vc tenha curiosidade
			
		// Atualiza a instancia cliente
		int sql_update_cliente();
		
		// Deleta a instancia cliente especificada na tabela
		int sql_delete_cliente();
};

#endif