#include "CProduto.h"
#include "Core.h"

/*Usa-se essa variavel nas funcoes sql. para transferir os atributos para a classe final criada a aprtir de uam chamada sql. por isso esta variavel eh auxiliar*/
Produto *auxiliar;

//Construtores e Destrutores
Produto::Produto (int nid, char *nnome, float nvalor, int nquantidade, char *ncategoria, char *ndescricao)
{
	id = nid;
	if(nnome)
		strcpy(nome, nnome);
	valor = nvalor;
	quantidade = nquantidade;
	if(ncategoria)
		strcpy(categoria, ncategoria);
	if(ndescricao)
		strcpy(descricao, ndescricao);
}

// Funcao especial em sql para criar uma instancia cliente a partir do banco de dados
static int getProd(void *NotUsed, int argc, char **argv, char **azColName)
{
	for(int i = 0; i < argc; i++)
	{
		printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
		if(!strcmp(azColName[i], "ID"))
			auxiliar->setId(atoi(argv[i]));
		if(!strcmp(azColName[i], "NOME"))
			auxiliar->setNome(argv[i]);
		if(!strcmp(azColName[i], "VALOR"))
			auxiliar->setValor(atof(argv[i]));
		if(!strcmp(azColName[i], "CATEGORIA"))
			auxiliar->setCategoria(argv[i]);
		if(!strcmp(azColName[i], "QUANTIDADE"))
			auxiliar->setQuantidade(atoi(argv[i]));
		if(!strcmp(azColName[i], "DESCRICAO"))
			auxiliar->setDescricao(argv[i]);
	}
	printf("\n");
	return 0;
}

Produto::Produto(int existing_pk)
{
	//sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	const char* data = "Callback function called";
	char *sql;
	char sql_command[128];
	sprintf(sql_command,"SELECT * from PRODUTOS where id = %d",existing_pk);

	auxiliar = new Produto(0,"(NULL)");

	rc = sqlite3_exec(db, sql_command, getProd, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);


	}

	setId(auxiliar->getId());
	setNome(auxiliar->getNome());
	setValor(auxiliar->getValor());
	setCategoria(auxiliar->getCategoria());
	setQuantidade(auxiliar->getQuantidade());
	setDescricao(auxiliar->getDescricao());


	// terminamos de usar a isntancia auxiliar
	delete auxiliar;
}

Produto::~Produto()
{
	// libera memoria
}

//Getters
int Produto::getId() 
{
	return id;
}

char* Produto::getNome() 
{
	return nome;
}

float Produto::getValor() 
{
	return valor;
}

int Produto::getQuantidade()
{
	return quantidade;
}

char* Produto::getCategoria()
{
	return categoria;
}

char* Produto::getDescricao() 
{
	return descricao;
}

//Setters
void Produto::setId(int id) {
	Produto::id = id;
}

void Produto::setNome(char *nome) {
	strcpy(Produto::nome, nome);
}

void Produto::setValor(float valor) {
	Produto::valor = valor;
}

void Produto::setQuantidade (int quantidade) 
{
	Produto::quantidade = quantidade;
}

void Produto::setCategoria (char *categoria) 
{
	strcpy(Produto::categoria, categoria);
}

void Produto::setDescricao (char *descricao) 
{
	strcpy(Produto::descricao, descricao);
}

//Setter Geral	DEPRECATED
/*
void Produto::setAll (int id, char *nome, float valor, int quantidade, char *categoria, char *descricao) 
{
	Produto::id = id;
	if(nome)
		strcpy(Produto::nome, nome);
	Produto::valor = valor;
	Produto::quantidade = quantidade;
	if(categoria)
		strcpy(Produto::categoria, categoria);
	if(descricao)
		strcpy(Produto::descricao, descricao);
}*/

// ============================== FUNCOES DE INTERFACE DA INSTANCIA DA CLASSE COM O BANCO DE DADOS ==============================
// Insere na tabela a aprtir de uma instancia da classe criado previamente e passada por parametro
int Produto::sql_insert_produto() // nCliente quer dizer newClient caso vc tenha curiosidade
{
	char sql_command[1024];
	int resultset_command;

	int PK_VAL, 
		n_tries = n_tentativas_sql;

	do
	{
		sprintf (sql_command, "INSERT INTO PRODUTOS(ID, NOME, VALOR, QUANTIDADE, CATEGORIA, DESCRICAO)"\
							  "VALUES (%d, '%s', %f, %d, '%s', '%s');", 
							  getId(), getNome(), getValor(), getQuantidade(), getCategoria(), getDescricao());
		resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

		if(!resultset_command)// falhou ao tentar inserir, provavelmente por causa da PK duplicada
		{
			PK_VAL =rand(); // gera uma nova chave
			setId(PK_VAL);
		}
		n_tries--;

	}while(n_tries && !resultset_command); // vai tentando ate conseguir inserir ou o numero de tentativas expirar
	return resultset_command;
}

// Atualiza a instancia cliente
int Produto::sql_update_produto()
{

	char sql_command[1024];
	int resultset_command;



	sprintf (sql_command, "UPDATE PRODUTOS SET NOME = '%s', VALOR = %f, QUANTIDADE = %d, CATEGORIA = '%s', DESCRICAO = '%s' WHERE id = %d;",
						getNome(), getValor(), getQuantidade(), 
						getCategoria(), getDescricao(), getId());
	resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.


	return resultset_command;
}

// Deleta a instancia cliente especificada na tabela
int Produto::sql_delete_produto()
{
	char sql_command[1024];
	int resultset_command;

	//Deleta da tabela Produtos o ID da instancia atual
	sprintf(sql_command,"DELETE FROM PRODUTOS WHERE ID = %d;", getId());
	resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

	return resultset_command;
}
// ============================== FUNCOES DE INTERFACE DA INSTANCIA DA CLASSE COM O BANCO DE DADOS ==============================