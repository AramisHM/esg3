// Módulo de vendas, escrito a partir do zero em 2014.11.19
// Vlw, flw
// - Aramis
#include "CVenda.h"
Venda *auxiliar;

// construtores e destrutores
Venda::Venda(int nid, int nfkid_cliente, char* ndate, float nvalor_total, char *nobservacao, char *ntipo_pagamento, int nn_parcelas)
{
	id = nid;
	if(nfkid_cliente)
		id_cliente = nfkid_cliente;
	if(ndate)
		strcpy(date, ndate);
	if(nvalor_total)
		valor_total = nvalor_total;
	if(nobservacao)
		strcpy(observacao, nobservacao);
	if(ntipo_pagamento)
		strcpy(tipo_pagamento, ntipo_pagamento);
	if(nn_parcelas)
		n_parcelas = nn_parcelas;
}
// Funcao interna especial em sql para criar uma instancia cliente a aprtir do banco de dados
static int sql_get_venda(void *NotUsed, int argc, char **argv, char **azColName)
{
	for(int i=0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

		if(!strcmp(azColName[i], "ID"))
			auxiliar->setid(atoi(argv[i]));

		if(!strcmp(azColName[i], "ID_CLIENTE"))
			auxiliar->setid_cliente(atoi(argv[i]));

		if(!strcmp(azColName[i], "DATA_VENDA"))
			auxiliar->setdate(argv[i]);

		if(!strcmp(azColName[i], "VALOR_TOTAL"))
			auxiliar->setvalor_total(atof(argv[i]));

		if(!strcmp(azColName[i], "OBSERVACAO"))
			auxiliar->setobservacao(argv[i]);

		if(!strcmp(azColName[i], "TIPO_PAGAMENTO"))
			auxiliar->settipo_pagamento(argv[i]);

		if(!strcmp(azColName[i], "N_PARCELAS"))
			auxiliar->setn_parcelas(atoi(argv[i]));
	}
	printf("\n");
	return 0;
}
// cria uam isntancia a partir do banco de dados, fornecendo a pk da linha
Venda::Venda(int existing_pk)
{
	//sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	const char* data = "Callback function called";
	char *sql;
	char sql_command[128];
	sprintf(sql_command,"SELECT * from VENDAS where id = %d",existing_pk);

	auxiliar = new Venda(0,0);

	rc = sqlite3_exec(db, sql_command, sql_get_venda, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	// Copia da classe auxiliar para a classe que vamos retornar
	id = auxiliar->getid();
	setid_cliente(auxiliar->getid_cliente());
	setdate(auxiliar->getdate());
	setvalor_total(auxiliar->getvalor_total());
	setobservacao(auxiliar->getobservacao());
	settipo_pagamento(auxiliar->gettipo_pagamento());
	setn_parcelas(auxiliar->getn_parcelas());


	// terminamos de usar a isntancia auxiliar
	delete auxiliar;
}
// destrutor
Venda::~Venda()
{
	// libera memoria?
}

//Getters
int Venda::getid()				// ID DA VENDA
{
	return id;
}
int Venda::getid_cliente()		// FK ID DO CLIENTE
{
	return id_cliente;
}
char* Venda::getdate()
{
	// data da venda
	return date;
}
float Venda::getvalor_total()
{
	return valor_total;
}
char* Venda::getobservacao()
{
	return observacao;
}
int Venda::getn_parcelas()
{
	return n_parcelas;
}
char *Venda::gettipo_pagamento()
{
	return tipo_pagamento;
}

//Setters
void Venda::setid(int nid) // ID DA VENDA
{
	id = nid;
}
void Venda::setid_cliente(int nfkid_cliente) // FK ID DO CLIENTE
{
	id_cliente = nfkid_cliente;
}
void Venda::setdate(char* ndate)
{
	strcpy(date, ndate);
}
void Venda::setobservacao(char *nobservacao)
{
	strcpy(observacao, nobservacao);
}
void Venda::setvalor_total(float nvalor_total)
{
	valor_total = nvalor_total;
}
void Venda::settipo_pagamento(char *ntipo_pagamento)
{
	strcpy(tipo_pagamento, ntipo_pagamento);
}
void Venda::setn_parcelas(int nn_parcelas)
{
	n_parcelas = nn_parcelas;
}

// Insere na tabela a aprtir de uma instancia da classe criado previamente e passada por parametro
int Venda::sql_insert_venda() // nCliente quer dizer newClient caso vc tenha curiosidade
{
	char sql_command[1024];
	int resultset_command;
	int PK_VAL, 
		n_tries = n_tentativas_sql;

	do
	{
		sprintf(sql_command,"INSERT INTO VENDAS(ID, ID_CLIENTE, DATA_VENDA, VALOR_TOTAL, OBSERVACAO, TIPO_PAGAMENTO, N_PARCELAS) "\
							"VALUES (%d, %d, '%s', %f, '%s', '%s', %d);", 
							getid(), getid_cliente(), getdate(), getvalor_total(), getobservacao(), gettipo_pagamento(), getn_parcelas());
		resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

		if(!resultset_command)// falhou ao tentar inserir, provavelmente por causa da PK duplicada
		{
			PK_VAL =rand(); // gera uma nova chave
			setid(PK_VAL);
		}
		n_tries--;

	}while(n_tries && !resultset_command); // vai tentando ate conseguir inserir ou o numero de tentativas expirar
	return resultset_command;
}
// Atualiza a instancia cliente
int Venda::sql_update_venda()
{
	char sql_command[1024];
	int resultset_command;

	sprintf(sql_command,"UPDATE VENDAS SET ID_CLIENTE = %d, DATA_VENDA = '%s', VALOR_TOTAL = %f, OBSERVACAO = '%s', TIPO_PAGAMENTO = '%s', N_PARCELAS = %d WHERE ID = %d; ",\
						getid_cliente(), getdate(), getvalor_total(), getobservacao(), gettipo_pagamento(), getn_parcelas(), getid());

	resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

	return resultset_command;
}
// Deleta a instancia cliente especificada na tabela
int Venda::sql_delete_venda()
{
	char sql_command[1024];
	int resultset_command;

	sprintf(sql_command,"DELETE FROM VENDAS WHERE ID = %d;", getid());
	resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

	return resultset_command;
}