// Módulo de vendas, escrito a partir do zero em 2014.11.19
// Vlw, flw
// - Aramis
#include "CProduto_Venda.h"

/*Usa-se essa variavel nas funcoes sql. para transferir os atributos para a classe final criada a aprtir de uma chamada sql. por isso esta variavel eh auxiliar*/
Produto_Venda *auxiliar;

// Construtores e destrutores
Produto_Venda::Produto_Venda(int nid, int nid_venda, int nid_produto, int nvalor_unit, int nquantidade)
{
	id = nid;
	if(nid_venda)
		id_venda = nid_venda;
	if(nid_produto)
		id_produto = nid_produto;
	if(nvalor_unit)
		valor_unit = nvalor_unit;
	if(nquantidade)
		quantidade = nquantidade;
}

// Funcao interna especial em sql para criar uma instancia cliente a aprtir do banco de dados
static int sql_get_produto_cliente(void *NotUsed, int argc, char **argv, char **azColName)
{
	for(int i=0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

		if(!strcmp(azColName[i], "ID"))
			auxiliar->setid(atoi(argv[i]));

		if(!strcmp(azColName[i], "ID_VENDA"))
			auxiliar->setid_venda(atoi(argv[i]));

		if(!strcmp(azColName[i], "ID_PRODUTO"))
			auxiliar->setid_produto(atoi(argv[i]));

		if(!strcmp(azColName[i], "VALOR_UNITARIO"))
			auxiliar->setvalor_unit(atof(argv[i]));

		if(!strcmp(azColName[i], "QUANTIDADE"))
			auxiliar->setquantidade(atoi(argv[i]));
	}
	printf("\n");
	return 0;
}
Produto_Venda::Produto_Venda(int existing_pk)
{
	//sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	const char* data = "Callback function called";
	char *sql;
	char sql_command[128];
	sprintf(sql_command,"SELECT * from PRODUTOS_VENDAS where ID = %d",existing_pk);

	auxiliar = new Produto_Venda(0, 0, 0);

	rc = sqlite3_exec(db, sql_command, sql_get_produto_cliente, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	// Copia da classe auxiliar para a classe que vamos retornar
	id = auxiliar->getid();
	setid_venda(auxiliar->getid_venda());
	setid_produto(auxiliar->getid_produto());
	setvalor_unit(auxiliar->getvalor_unit());
	setquantidade(auxiliar->getquantidade());

	// terminamos de usar a isntancia auxiliar
	delete auxiliar;
}
Produto_Venda::~Produto_Venda()
{
	// libera memoria
}


//Getters
int Produto_Venda::getid()// ID DA VENDA
{
	return id;
}
int Produto_Venda::getid_venda() // FK ID DA VENDA
{
	return id_venda;
}
int Produto_Venda::getid_produto() // FK ID DO PRODUTO
{
	return id_produto;
}
float Produto_Venda::getvalor_unit() // valor unitário, apesar de já existir no produto, os produtos podem mudar de valor ao longo do tempo
{
	return valor_unit;
}
int Produto_Venda::getquantidade() // quantidades do produto acima presente na venda acima
{
	return quantidade;
}

//Setters
void Produto_Venda::setid(int nid) // ID DA VENDA
{
	id = nid;
}
void Produto_Venda::setid_venda(int nid_venda) // FK ID DA VENDA
{
	id_venda = nid_venda;
}
void Produto_Venda::setid_produto(int nid_produto) // FK ID DO PRODUTO
{
	id_produto = nid_produto;
}
void Produto_Venda::setvalor_unit(int nvalor_unit) // valor unitário, apesar de já existir no produto, os produtos podem mudar de valor ao longo do tempo
{
	valor_unit = nvalor_unit;
}
void Produto_Venda::setquantidade(int nquantidade) // quantidades do produto acima presente na venda acima
{
	quantidade = nquantidade;
}




// ============================== FUNCOES DE INTERFACE DA INSTANCIA DA CLASSE COM O BANCO DE DADOS ==============================
// Insere na tabela a aprtir de uma instancia da classe criado previamente e passada por parametro
int Produto_Venda::sql_insert_produto_venda() // nCliente quer dizer newClient caso vc tenha curiosidade
{
	char sql_command[1024];
	int resultset_command;
	int PK_VAL, 
		n_tries = n_tentativas_sql;

	do
	{
		sprintf(sql_command,"INSERT INTO PRODUTOS_VENDAS(ID, ID_VENDA, ID_PRODUTO, VALOR_UNITARIO, QUANTIDADE) "\
							"VALUES (%d, %d, %d, %f, %d);", 
							getid(), getid_venda(), getid_produto(), getvalor_unit(), getquantidade());
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
int Produto_Venda::sql_update_produto_venda()
{
	char sql_command[1024];
	int resultset_command;

	sprintf(sql_command,"UPDATE PRODUTOS_VENDAS SET ID_VENDA = %d, ID_PRODUTO = %d, VALOR_UNITARIO = %f, QUANTIDADE = %d WHERE ID = %d; ",\
						getid_venda(), getid_produto(), getvalor_unit(), getquantidade(), getid());

	resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

	return resultset_command;
}

// Deleta a instancia cliente especificada na tabela
int Produto_Venda::sql_delete_produto_venda()
{
	char sql_command[1024];
	int resultset_command;

	sprintf(sql_command,"DELETE FROM PRODUTOS_VENDAS WHERE ID = %d;", getid());
	resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

	return resultset_command;
}
// ============================== FUNCOES DE INTERFACE DA INSTANCIA DA CLASSE COM O BANCO DE DADOS ==============================