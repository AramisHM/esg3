#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strcpy and other stuff for strings
#include <sqlite3.h>

#include <time.h>
#include <ctime> // datas etc

#include "Globais.h" // all the important definitions and stuff for GUI


// Usuarios pre programados do sistema
#define n_usuarios 3

// Usuarios pre programados do sistema
extern char *usuarios[n_usuarios];
extern char *senhas_usuarios[n_usuarios] ;
extern int prioridades[n_usuarios];


// variavel do banco de dados do software
extern sqlite3 *db;

extern int nivel_usuario; // define o nivel de acesso do usuario no sistema

void InicializarBancoDeDados();
int ExecutarBancoDeDados(char*);

/*Função que permite descobrir todas as pks de uma tabela de forma automatica - NÃO SE ESQUECA DE LIBERAR O RETORNO DESTA FUNCAO DEPOIS DE USA-LA*/
int *get_pk_vector(char *pk_name, char *table_name, char *condition, int *table_size);

#endif