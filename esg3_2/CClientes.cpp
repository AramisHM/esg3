
#include "CCliente.h"
#include "Core.h"

/*Usa-se essa variavel nas funcoes sql. para transferir os atributos para a classe final criada a aprtir de uma chamada sql. por isso esta variavel eh auxiliar*/
Cliente *auxiliar;

// Construtores e destrutores
Cliente::Cliente(int nid, char *nnome, char *npessoa, char *ncpfcnpj, char *ncep, char *ncidade, char *nbairro, char* nrua, int nnumero, char* nestado, char* ncomplemento, char* nfone, char* nemail, char* nobservacao)
{
	id = nid;
	if(nnome)
		strcpy(nome, nnome);
	if(npessoa)
		strcpy(pessoa, npessoa);
	if(ncpfcnpj)
		strcpy(cpfcnpj, ncpfcnpj);
	if(ncep)
		strcpy(cep, ncep);
	if(ncidade)
		strcpy(cidade, ncidade);
	if(nbairro)
		strcpy(bairro, nbairro);
	if(nrua)
		strcpy(rua, nrua);
	if(nnumero)
		numero = nnumero;
	if(nestado)
		strcpy(estado, nestado);
	if(ncomplemento)
		strcpy(complemento, ncomplemento);
	if(nfone)
		strcpy(fone, nfone);
	if(nemail)
		strcpy(email, nemail);
	if(nobservacao)
		strcpy(observacao, nobservacao);
}

// Funcao interna especial em sql para criar uma instancia cliente a aprtir do banco de dados
static int sql_get_cliente(void *NotUsed, int argc, char **argv, char **azColName)
{
	for(int i=0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

		if(!strcmp(azColName[i], "ID"))
			auxiliar->setid(atoi(argv[i]));

		if(!strcmp(azColName[i], "NOME"))
			auxiliar->setnome(argv[i]);

		if(!strcmp(azColName[i], "PESSOA"))
			auxiliar->setpessoa(argv[i]);

		if(!strcmp(azColName[i], "CPFCNPJ"))
			auxiliar->setcpfcnpj(argv[i]);

		if(!strcmp(azColName[i], "CEP"))
			auxiliar->setcep(argv[i]);

		if(!strcmp(azColName[i], "CIDADE"))
			auxiliar->setcidade(argv[i]);

		if(!strcmp(azColName[i], "BAIRRO"))
			auxiliar->setbairro(argv[i]);

		if(!strcmp(azColName[i], "RUA"))
			auxiliar->setrua(argv[i]);

		if(!strcmp(azColName[i], "NUMERO"))
			auxiliar->setnumero(atoi(argv[i]));

		if(!strcmp(azColName[i], "ESTADO"))
			auxiliar->setestado(argv[i]);

		if(!strcmp(azColName[i], "COMPLEMENTO"))
			auxiliar->setcomplemento(argv[i]);

		if(!strcmp(azColName[i], "FONE"))
			auxiliar->setfone(argv[i]);

		if(!strcmp(azColName[i], "EMAIL"))
			auxiliar->setemail(argv[i]);

		if(!strcmp(azColName[i], "OBSERVACAO"))
			auxiliar->setobservacao(argv[i]);
	}
	printf("\n");
	return 0;
}
Cliente::Cliente(int existing_pk)
{
	//sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	const char* data = "Callback function called";
	char *sql;
	char sql_command[128];
	sprintf(sql_command,"SELECT * from CLIENTES where id = %d",existing_pk);

	auxiliar = new Cliente(0,"(NULL)");

	rc = sqlite3_exec(db, sql_command, sql_get_cliente, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	// Copia da classe auxiliar para a classe que vamos retornar
	id = auxiliar->getid();
	setpessoa(auxiliar->getpessoa());
	setcpfcnpj(auxiliar->getcpfcnpj());
	setnome(auxiliar->getnome());
	setcep(auxiliar->getcep());
	setcidade(auxiliar->getcidade());
	setbairro(auxiliar->getbairro());
	setrua(auxiliar->getrua());
	setnumero(auxiliar->getnumero());
	setestado(auxiliar->getestado());
	setcomplemento(auxiliar->getcomplemento());
	setfone(auxiliar->getfone());
	setemail(auxiliar->getemail());
	setobservacao(auxiliar->getobservacao());


	// terminamos de usar a isntancia auxiliar
	delete auxiliar;
}
Cliente::~Cliente()
{
	// libera memoria
}

// Metodos
//Getters
int Cliente::getid()
{
	return id;
}
char* Cliente::getpessoa()
{
	return pessoa;
}
char* Cliente::getcpfcnpj()
{
	return cpfcnpj;
}
char* Cliente::getnome()
{
	return nome;
}
char* Cliente::getcep()
{
	return cep;
}
char* Cliente::getcidade()
{
	return cidade;
}
char* Cliente::getbairro()
{
	return bairro;
}
char* Cliente::getrua()
{
	return rua;
}
int Cliente::getnumero()
{
	return numero;
}
char* Cliente::getestado()
{
	return estado;
}
char* Cliente::getcomplemento()
{
	return complemento;
}
char* Cliente::getfone()
{
	return fone;
}
char* Cliente::getemail()
{
	return email;
}
char* Cliente::getobservacao()
{
	return observacao;
}

//Setters
void Cliente::setid(int nid)
{
	id = nid;
}
void Cliente::setpessoa(char *npessoa)
{
	strcpy(pessoa, npessoa);
}
void Cliente::setcpfcnpj(char *ncpfcnpj)
{
	strcpy(cpfcnpj, ncpfcnpj);
}
void Cliente::setnome(char *nnome)
{
	strcpy(nome, nnome);
}
void Cliente::setcep(char *ncep)
{
	strcpy(cep, ncep);
}
void Cliente::setcidade(char *ncidade)
{
	strcpy(cidade, ncidade);
}
void Cliente::setbairro(char *nbairro)
{
	strcpy(bairro, nbairro);
}
void Cliente::setrua(char *nrua)
{
	strcpy(rua, nrua);
}
void Cliente::setnumero(int nnumero)
{
	numero = nnumero;
}
void Cliente::setestado(char *nestado)
{
	strcpy(estado, nestado);
}
void Cliente::setcomplemento(char *ncomplemento)
{
	strcpy(complemento, ncomplemento);
}
void Cliente::setfone(char *nfone)
{
	strcpy(fone, nfone);
}
void Cliente::setemail(char *nemail)
{
	strcpy(email, nemail);
}
void Cliente::setobservacao(char *nobservacao)
{
	strcpy(observacao, nobservacao);
}


// ============================== FUNCOES DE INTERFACE DA INSTANCIA DA CLASSE COM O BANCO DE DADOS ==============================
// FunÁıes especiais para banco de dados
// Insere na tabela a aprtir de uma instancia da classe criado previamente e passada por parametro
int Cliente::sql_insert_cliente() // nCliente quer dizer newClient caso vc tenha curiosidade
{
	//sqlite3 *db;
	/*
	char *zErrMsg = 0;
	const char* data = "Callback function called";
	*/
	char sql_command[1024];
	int resultset_command;

	int PK_VAL, 
		n_tries = n_tentativas_sql;

	do
	{
		sprintf(sql_command,"INSERT INTO CLIENTES(ID, CPFCNPJ, PESSOA, NOME, CEP, CIDADE, BAIRRO, ESTADO, RUA, NUMERO, COMPLEMENTO, FONE, EMAIL, OBSERVACAO) "\
							"VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s', '%s', '%s', '%s');", 
							getid(), getcpfcnpj(), getpessoa(), getnome(), getcep(), getcidade(), getbairro(), getestado(),  
							getrua(), getnumero(), getcomplemento(), getfone(), getemail(), getobservacao());
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
int Cliente::sql_update_cliente()
{
	//sqlite3 *db;
	/*
	char *zErrMsg = 0;
	const char* data = "Callback function called";
	*/
	char sql_command[1024];
	int resultset_command;
	/*
	int PK_VAL, 
		n_tries = n_tentativas_sql;
		*/

	//do
	//{
		sprintf(sql_command,"UPDATE CLIENTES SET CPFCNPJ = '%s', PESSOA = '%s', NOME = '%s', CEP = '%s', CIDADE = '%s', BAIRRO = '%s', ESTADO = '%s', RUA = '%s', NUMERO = %d, COMPLEMENTO = '%s', FONE = '%s', EMAIL = '%s', OBSERVACAO = '%s' WHERE ID = %d;",\
							getcpfcnpj(), getpessoa(), getnome(), getcep(), getcidade(), getbairro(), getestado(),  
							getrua(), getnumero(), getcomplemento(), getfone(), getemail(), getobservacao(), getid());
		resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

		/*
		if(!resultset_command)// falhou ao tentar inserir, provavelmente por causa da PK duplicada
		{
			PK_VAL =rand(); // gera uma nova chave
			setid(PK_VAL);
		}
		n_tries--;
		*/ // Ou voce tem a PK ou vc nao tem, nao existe tentar denovo aqui seu Z………… :}

	//}while(n_tries && !resultset_command); // vai tentando ate conseguir inserir ou o numero de tentativas expirar
	return resultset_command;
}

// Deleta a instancia cliente especificada na tabela
int Cliente::sql_delete_cliente()
{
	char sql_command[1024];
	int resultset_command;
	

	//do
	//{
		sprintf(sql_command,"DELETE FROM CLIENTES WHERE ID = %d;", getid());
		resultset_command = ExecutarBancoDeDados(sql_command); // executa o comando e retorna 1 se executou o comando sem problemas, e 0 se houve algum erro.

		/*
		if(!resultset_command)// falhou ao tentar inserir, provavelmente por causa da PK duplicada
		{
			PK_VAL =rand(); // gera uma nova chave
			setid(PK_VAL);
		}
		n_tries--;
		*/ // Ou voce tem a PK ou vc nao tem, nao existe tentar denovo aqui seu Z………… :}

	//}while(n_tries && !resultset_command); // vai tentando ate conseguir inserir ou o numero de tentativas expirar
	return resultset_command;
}
// ============================== FUNCOES DE INTERFACE DA INSTANCIA DA CLASSE COM O BANCO DE DADOS ==============================