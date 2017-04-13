#include "Core.h"

// nivel usuário logado
int nivel_usuario = 0;

// database
sqlite3 *db;


// Usuarios pre programados do sistema
char *usuarios[n_usuarios] = { "admim", "vendedor", "dona marocas" };
char *senhas_usuarios[n_usuarios] = { "admin", "123", "123" };
int prioridades[n_usuarios] = { 3, 2, 5 };

//callback para select // ----------------------------------------------
static int callback_select(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++)
   {
      printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
int ExecutarBancoDeDados(char* commando)
{
	//sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	const char* data = "Callback function called";
	char *sql;

	rc = sqlite3_exec(db, commando, callback_select, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}
	else
	{
		fprintf(stdout, "Command entered with success.\n");
		return 1; // Sucesso
	}
}
void database_open() 
{
	/* Open database */
	int  rc = sqlite3_open("test.db", &db);
	if( rc )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else
	{
		fprintf(stdout, "Opened database successfully\n");
	}
}
//callback para select // ----------------------------------------------

// Tabelas ----------------------------------------------
// TODO: Mover cada tabela para sua respectiva classe? Seria interessante....
void cria_tabela_clientes()
{
	/* Create SQL statement */
	char *sql = "CREATE TABLE CLIENTES("						\
		  "ID			INT			PRIMARY KEY		NOT NULL,"	\
		  "CPFCNPJ		CHAR(20)	NOT NULL,"					\
		  "PESSOA		CHAR(10)	NOT NULL,"					\
		  "NOME			TEXT		NOT NULL,"					\
		  "CEP			CHAR(10)	NOT NULL,"					\
		  "CIDADE		CHAR(50),"								\
		  "BAIRRO		CHAR(50),"								\
		  "ESTADO		CHAR(2),"								\
		  "RUA			CHAR(50),"								\
		  "NUMERO		INT,"									\
		  "COMPLEMENTO	CHAR(50),"								\
		  "FONE			CHAR(16),"								\
		  "EMAIL		CHAR(50),"								\
		  "OBSERVACAO	CHAR(50));";
	ExecutarBancoDeDados(sql);
}
void cria_tabela_produtos() 
{
	/* Create SQL statement */
	char *sql = "CREATE TABLE PRODUTOS("						\
		  "ID			INT			PRIMARY KEY		NOT NULL,"	\
		  "NOME			CHAR(20)	NOT NULL,"					\
		  "VALOR		FLOAT		NOT NULL,"					\
		  "QUANTIDADE	INT			NOT NULL,"					\
		  "CATEGORIA	CHAR(20)	NOT NULL,"					\
		  "DESCRICAO	CHAR(50));";
	ExecutarBancoDeDados(sql);
}
void cria_tabela_vendas()
{
	/* Create SQL statement */
	char *sql = "CREATE TABLE VENDAS("								\
		  "ID				INT			PRIMARY KEY		NOT NULL,"	\
		  "ID_CLIENTE		INT,"									\
		  "DATA_VENDA		DATETIME,"								\
		  "VALOR_TOTAL		FLOAT,"									\
		  "OBSERVACAO		CHAR(128),"								\
		  "TIPO_PAGAMENTO	CHAR(64),"
		  "N_PARCELAS		INT);";
	ExecutarBancoDeDados(sql);
}
void cria_tabela_produtos_vendas()
{
	/* Create SQL statement */
	char *sql = "CREATE TABLE PRODUTOS_VENDAS("						\
		  "ID				INT			PRIMARY KEY		NOT NULL,"	\
		  "ID_VENDA			INT	NOT NULL references VENDAS (ID),"	\
		  "ID_PRODUTO		INT	NOT NULL references PRODUTOS (ID),"	\
		  "VALOR_UNITARIO	FLOAT,"									\
		  "QUANTIDADE		INT);";
	ExecutarBancoDeDados(sql);
}
// Tabelas ----------------------------------------------

// Testes // TODO REMOVER MAIS TARDE ------------------
void teste_stress_cliente ()
{
	// Teste de stress
	/*
	char *sql = "INSERT INTO CLIENTES(ID, CPFCNPJ, PESSOA, NOME, CEP, CIDADE, BAIRRO, ESTADO, RUA, NUMERO, COMPLEMENTO, FONE, EMAIL, OBSERVACAO) "\
				 "VALUES (1, '012345678', 'fisica', 'Aramis Hornung Moraes', '1111000', 'Curitiba', 'Bairrodatreta','Parana', 'RUARUA', 1111000, 'AP 1001', '9999999', 'aram@treata.com', 'teste1');";
	ExecutarBancoDeDados(sql);

	char sql2[1024] = {0};
	for(int lol = 0; lol < 5; lol++)
	{
		
		sprintf(sql2,"INSERT INTO CLIENTES(ID, CPFCNPJ, PESSOA, NOME, CEP, CIDADE, BAIRRO, ESTADO, RUA, NUMERO, COMPLEMENTO, FONE, EMAIL, OBSERVACAO) "\
					 "VALUES (%d, '012345678', 'fisica', 'Alguem', '1111000', 'Curitiba', 'Bairrodatreta','Parana', 'RUARUAtreta', 3000, 'AP 1001', '9999999', 'aram@treata.com', 'teste1');", lol);
		ExecutarBancoDeDados(sql2);
	}
	*/

	char	*sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (111,'44664','fisica, juridica','Maia Q Vega','5429','Dover','Kent','New Caledonia','PO Box 235, 3862 Neque St','42138884461831','nulla ante,','(037625) 050744','ProinvelitSed@Sedidrisuscom','ad litora torquent per');";ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (1,'44166508771148','fisica, juridica','Maia Q Vega','5429','Dover','Kent','New Caledonia','PO Box 235, 3862 Neque St','42138884461831','nulla ante,','(037625) 050744','ProinvelitSed@Sedidrisuscom','ad litora torquent per');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (1001,'21588603311837','fisica, juridica','Chloe O Francis','66338','Newbury','Ontario','Ireland','Ap #817-7779 Vehicula Avenue','11778998134038','Nulla','(037307) 889261','convallisest@Aeneaneuismodca','et libero Proin mi Aliquam');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (2001,'12302698248144','fisica, juridica','Melanie Y Stone','G9 8YY','Tilburg','Noord Brabant','Latvia','351-1857 Pellentesque Avenue','28887463685034','lorem ipsum sodales','(032396) 488342','ligulaAliquam@rhoncusProinca','Vestibulum ut eros');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (3001,'91419252794109','fisica, juridica','Yetta R Turner','A6R 1R9','Trowbridge','Wiltshire','Mayotte','4751 Imperdiet St','38679413580826','Praesent eu dui','(034474) 126025','musDonec@Pellentesqueultriciesedu','velit Quisque varius');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (4001,'2606535689859','fisica, juridica','MacKenzie X Hart','22848','Lang','Saskatchewan','Benin','PO Box 181, 7979 Malesuada Road','12965532756217','purus','(083) 85684602','faucibus@egetlacusMaurisedu','malesuada augue ut');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (5001,'17830959967735','juridica, fisica','Tobias U Bryan','49921','Crato','Ceará','Tunisia','624-8524 Eget Ave','75616294602388','tempor bibendum Donec','(0882) 88032953','Aliquamgravida@NullafacilisisSuspendissecouk','sed, est Nunc laoreet lectus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (6001,'42671617180294','juridica, fisica','Bethany G Woods','61904','Rutigliano','PU','Rwanda','Ap #821-5784 At Avenue','28220582467722','lobortis','(063) 69093253','orci@Integercouk','sem, vitae aliquam eros turpis');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (7001,'40031242315341','fisica, juridica','Ulric B Lane','24815-624','Notre-Dame-du-Nord','Quebec','Kenya','Ap #658-3928 Sagittis Ave','18681702981855','sit','(026) 76837925','Maurisblanditenim@semperpretiumorg','pede Praesent eu dui Cum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (8001,'9363947512592','fisica, juridica','Hop U Keith','5505CG','Albury','New South Wales','Belarus','693-9412 Enim Road','81355312220737','Fusce dolor quam,','(038) 84509930','arcuac@aliquetmetuscouk','in');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (9001,'41560243295605','fisica, juridica','Xaviera Y Prince','00973-378','Okene','KO','Suriname','792-1613 Adipiscing Rd','23725615006745','eu','(0916) 45033739','rhoncusNullamvelit@semedu','Proin dolor');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (10001,'11346823402175','fisica, juridica','Amal W Randall','6359DE','Hastings','SS','Myanmar','Ap #321-3924 Integer Street','19420639141392','tristique','(072) 94108761','sodalesMaurisblandit@egetvariusedu','augue ut lacus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (11001,'23590926749177','fisica, juridica','Shad Y Hartman','8131','Lloydminster','Saskatchewan','Cyprus','Ap #153-8433 Sociis Av','15959516432953','augue','(03957) 7038362','quamCurabitur@augueidorg','ipsum Phasellus vitae');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (12001,'34103954540754','juridica, fisica','Zorita W Ball','354311','Wommelgem','Antwerpen','Swaziland','PO Box 754, 7786 Et Street','45254350079627','mattis','(0373) 14790078','tincidunt@Intinciduntnet','sed pede Cum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (13001,'27996432384422','fisica, juridica','Tasha S Bruce','QA8 1ZA','Zelzate','OV','Holy See (Vatican City State)','2876 Nec Avenue','10239145333786','neque','(035883) 053492','telluseuaugue@nisiorg','arcu Vestibulum ante ipsum primis');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (14001,'21914790722922','juridica, fisica','Ferdinand J Salinas','14236','Buguma','RI','Jersey','Ap #608-4870 Eget St','22922621234245','tempor','(00621) 6947773','natoque@Aliquamadipiscinglobortisorg','Aliquam ultrices iaculis odio');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (15001,'10951048291881','fisica, juridica','Phoebe R Bryan','82805','Castelló','CV','Gabon','Ap #966-8401 Pede St','51014347990324','Nunc','(038610) 088544','semut@vehiculacom','Sed malesuada augue');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (16001,'24213177854261','fisica, juridica','Rae F Terry','785413','Horsham','VI','Martinique','PO Box 315, 6668 Odio Ave','21870954030526','eget ipsum Suspendisse','(06634) 5245003','quamvelsapien@ultriciesornareedu','eu metus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (17001,'29835163355638','juridica, fisica','Wallace O Castaneda','33228','Huntly','NI','Palestine, State of','Ap #221-227 Proin Rd','10592287456607','sapien, gravida non,','(068) 74419560','nonlobortis@dolorcouk','Suspendisse aliquet molestie tellus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (18001,'46399068553845','fisica, juridica','Vance M Clarke','5811','Tullibody','CL','Malaysia','835-4563 Lorem Street','13709728593883','ullamcorper, nisl arcu','(025) 60015001','nequeInornare@placeratorg','lorem');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (19001,'56607536543751','fisica, juridica','Lisandra H Gay','3253','Vancouver','WA','Curaçao','PO Box 502, 8115 Pharetra St','1324504663017','Duis','(036665) 409463','IntegermollisInteger@ullamcorperDuiscursusedu','placerat, augue Sed molestie');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (20001,'17129758410635','juridica, fisica','Chloe H Mcgee','1522','Campofelice di Fitalia','SI','Congo (Brazzaville)','8495 Amet Road','11234398886261','id ante dictum','(043) 90594240','pulvinar@nonjustoca','elit, pretium');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (21001,'38374931419475','fisica, juridica','Noble O Whitley','73473','Township of Minden Hills','ON','Kenya','PO Box 584, 6636 Mus Street','68758872704748','non, lacinia at,','(062) 23178228','fringillaporttitorvulputate@ligulanet','rutrum lorem');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (22001,'11579349776631','fisica, juridica','Lacey N Kelly','5872','Campli','AB','Pakistan','Ap #720-2411 Lacus St','77970468621715','dolor, nonummy ac,','(038358) 599597','Praesenteu@metusedu','sit amet, risus Donec');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (23001,'12220894805196','fisica, juridica','Thane D Ramirez','23163','Berlin','Berlin','Portugal','854-3433 Adipiscing St','12921151986488','amet nulla','(093) 45125442','Nullaeget@maurisedu','ultricies');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (24001,'26622826194065','fisica, juridica','Christine U English','205599','Hamburg','Hamburg','Somalia','7544 Enim St','93106562304556','vel nisl','(09066) 9788831','Nullamvelit@iaculisodiocouk','tincidunt Donec vitae erat');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (25001,'23319414850117','juridica, fisica','Dolan F Mcbride','57355','Puntarenas','Puntarenas','Mozambique','Ap #605-2078 Pharetra Av','39000729082166','Praesent','(07945) 5340925','estacfacilisis@tempororg','morbi tristique');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (26001,'21734844113798','fisica, juridica','Sara X Shelton','DT0 2WU','South Burlington','Vermont','Virgin Islands, British','9723 Lectus St','11869188758924','sit','(031252) 203472','Donec@CurabiturmassaVestibulumnet','nec ante blandit');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (27001,'99982263637467','fisica, juridica','Alice Y Cochran','930514','Gasteiz','PV','Sri Lanka','PO Box 773, 1522 In Av','69816379973562','arcu Morbi sit','(0509) 48141231','loremloremluctus@nibhPhasellusnullaedu','dolor Fusce feugiat');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (28001,'12309689066297','juridica, fisica','Echo Q West','31297-065','Naperville','Illinois','Lithuania','PO Box 256, 8016 Aliquet Rd','63402008674734','congue','(05806) 8961336','risusNullaeget@semutorg','est ac mattis semper,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (29001,'20752657718961','fisica, juridica','Moana C Jefferson','70116','Limoges','LI','New Zealand','2984 Gravida Road','20442935653715','facilisis eget, ipsum','(039) 48248461','ipsumnuncid@tristiqueedu','Nam porttitor');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (30001,'46630999525146','juridica, fisica','Malachi V Williamson','7630','Invercargill','SI','British Indian Ocean Territory','9681 Mauris Rd','78774905387327','mauris','(0029) 54956758','disparturient@scelerisquenequesedorg','at risus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (31001,'30071450703309','juridica, fisica','Tanisha F Giles','24951','Swan','WA','Mauritius','577-495 Vel Road','10120833904931','congue In scelerisque','(036781) 777776','mi@tinciduntnequeorg','et ultrices posuere');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (32001,'17935921462353','fisica, juridica','Anika B Cherry','64-988','Ch�tillon','Luxemburg','Uruguay','685-5721 Augue St','38136310600685','Aliquam adipiscing','(05864) 2030770','ametconsectetueradipiscing@Sednecmetuscouk','dignissim');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (33001,'21224502825353','juridica, fisica','Moana G Barker','8927','Cambridge','NI','Antigua and Barbuda','393-9362 Lorem, Av','3702883898132','pede, ultrices a,','(084) 05116745','nunc@MorbimetusVivamusorg','per conubia');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (34001,'165455709064','juridica, fisica','Gregory E Kirk','9995WU','Funtua','KT','Turkmenistan','1307 Curabitur St','82614581685425','tempus','(0933) 12545897','metusAliquam@velvulputateca','vulputate,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (35001,'19820606801932','juridica, fisica','Clinton E Kline','2962','Morwell','Victoria','New Zealand','Ap #479-973 Sed St','43158320763861','elit,','(058) 30555470','Phaselluslibero@Maurismolestiecom','egestas hendrerit neque');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (36001,'57586442085647','juridica, fisica','Eve F Nelson','88030','Kraków','Małopolskie','Saint Pierre and Miquelon','8832 Elementum, Ave','84129995167931','Curabitur','(07054) 1025660','nuncQuisque@facilisiSedcouk','arcu eu odio');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (37001,'14043483561481','juridica, fisica','Pearl E Rasmussen','71706','Kitchener','ON','Saint Kitts and Nevis','PO Box 102, 739 Elit Rd','21044298144633','nulla In','(08133) 5694749','Donec@purusinca','ultricies');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (38001,'33364363323123','fisica, juridica','Michelle K Estrada','73889','San José de Alajuela','Alajuela','Iceland','175-1094 Vivamus Avenue','30536386405761','pede Praesent eu','(036629) 359057','utcursus@auctorullamcorpernet','Duis mi enim, condimentum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (39001,'5658148243422','juridica, fisica','Nyssa M Levine','CT0I 1YQ','North Bay','ON','Japan','482-9938 Suspendisse Avenue','53219401700742','ipsum','(088) 91718525','tempus@vitaesodalesatedu','nec, diam Duis mi');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (40001,'50712372751814','juridica, fisica','Larissa V Navarro','93964','Berlin','BE','Solomon Islands','7702 Auctor, Street','17558718286507','enim Curabitur massa','(007) 98622450','Nulla@ligulaAeneangravidacom','non, vestibulum nec,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (41001,'20410009324912','fisica, juridica','Joel T Brown','54739','Cambrai','NO','Benin','850-2012 Donec Rd','64069352596831','nulla magna,','(024) 97284492','ipsum@egetmassaSuspendisseorg','Suspendisse ac metus vitae velit');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (42001,'28684156880866','fisica, juridica','Tana I Sargent','3570','Dawson Creek','British Columbia','Norway','4848 Mauris, Ave','1947759820399','est','(029) 86699541','dolorsitamet@portaelitaorg','nonummy');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (43001,'73029691024386','fisica, juridica','Blake W Ryan','K3J 2M3','Watermaal-Bosvoorde','Brussels Hoofdstedelijk Gewest','Lesotho','705-8139 Ligula Road','22425605450831','magna Nam ligula','(035) 65906731','ullamcorper@loremcouk','sociosqu ad litora torquent');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (44001,'66236101387712','fisica, juridica','Phillip L Phelps','1492','Spokane','WA','Japan','3963 Diam Av','44125172772807','In nec orci','(077) 44493787','Phasellus@Suspendissecom','dolor');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (45001,'12271705706772','fisica, juridica','Kylan T Hutchinson','3564LG','Opole','Opolskie','Libya','8110 Aliquet, Avenue','99908494172979','ornare,','(0141) 41996912','estcongue@convallisincom','vel turpis');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (46001,'26454914676158','fisica, juridica','Gillian E Ellis','X8J 3J4','Husum','Saarland','Macao','5576 Pharetra, Road','096251326878635','ligula','(009) 78233498','porttitorerosnec@ametcouk','quam');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (47001,'11909543019047','juridica, fisica','Kato N Woodard','99149','VTM','VB','Jersey','636-8607 Dis Ave','43579780205848','ipsum porta','(0190) 78428223','duiquis@sedleocom','Phasellus elit pede, malesuada vel,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (48001,'42255429406053','juridica, fisica','Barry Z Castillo','1793XP','Neyveli','Tamil Nadu','Zimbabwe','353 Id St','10642260981836','risus Donec egestas','(033413) 432150','consectetuer@Sedetliberoedu','Aliquam');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (49001,'4831514613197','fisica, juridica','Adele T Shannon','N0L 8K7','Goes','Zeeland','Mali','177-8692 Ligula Rd','5890643368296','consectetuer rhoncus Nullam','(030285) 593168','Cras@hymenaeoscouk','pede Cras vulputate');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (50001,'28869933211185','juridica, fisica','Gillian G Austin','H3J 6B4','Cap-Rouge','Quebec','Timor-Leste','294-5347 Ac Ave','13542669674988','Morbi neque tellus,','(04765) 0922401','Donecluctusaliquet@nislQuisquefringillaca','enim Etiam');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (51001,'30138258171319','fisica, juridica','Claire L Maxwell','7193','Oss','N','Christmas Island','PO Box 499, 8116 Sit Road','12602387132793','lorem ipsum sodales','(01542) 8389505','ipsumCurabitur@montesnasceturridiculuscom','mattis velit');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (52001,'1970785673425','juridica, fisica','Chantale R Hebert','66867','Clovenfords','Selkirkshire','Pitcairn Islands','Ap #537-3281 Arcu St','17922073081492','Phasellus fermentum convallis','(08827) 4138403','aliquam@penatibusetmagnisorg','mollis nec, cursus a, enim');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (53001,'29185566103647','fisica, juridica','Gloria T Rivas','03-886','Temuka','South Island','Northern Mariana Islands','Ap #216-3202 Pede St','19488003773981','lorem semper','(090) 99104768','urna@laciniamattisIntegerorg','sed consequat auctor, nunc nulla');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (54001,'58058867271684','juridica, fisica','Kyle N Gutierrez','5638','Amiens','Picardie','Tunisia','PO Box 172, 7466 Est, Rd','35121385605569','non','(041) 80044509','eget@necmollisvitaeorg','nibh Donec');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (55001,'38562975406306','juridica, fisica','Coby H Carver','332338','Aurora','CO','Lebanon','PO Box 715, 2302 Mi Ave','63984067966151','ipsum','(038361) 789654','eget@sempereratincom','ut mi Duis risus odio,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (56001,'21933205586067','juridica, fisica','Andrew B Dominguez','7922','Katsina','KT','Botswana','PO Box 760, 3885 Nascetur Rd','47955473382354','bibendum fermentum','(0047) 57749035','ipsum@tellusNuncca','ut lacus Nulla tincidunt, neque');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (57001,'14139588210904','juridica, fisica','Clayton P Pierce','4047','Wrocław','Dolnośląskie','Niue','Ap #787-9575 Libero Rd','9132336959015','sem','(01568) 7636719','mi@rutrumloremacca','dictum placerat, augue Sed');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (58001,'24827384339684','fisica, juridica','Madonna N Blanchard','97-032','Adelaide','SA','Palau','PO Box 333, 6814 Eget Rd','10246591171874','metus sit','(0361) 03313544','ridiculusmus@velnislQuisqueca','penatibus et');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (59001,'29588889448392','juridica, fisica','Bianca B Robertson','3753','Kraków','MP','Timor-Leste','775-8861 Erat Rd','10840509125629','ac','(038582) 752404','gravida@sedtortorcom','consequat purus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (60001,'88820547760697','juridica, fisica','Ross P Hutchinson','06232','Kano','Kano','French Guiana','3904 Per Rd','17758325410035','ligula Nullam','(0507) 52108348','fringillaporttitorvulputate@commodoauctorcom','nec quam Curabitur');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (61001,'4033503884956','juridica, fisica','Coby J Alexander','51186','Sokoto','Sokoto','Marshall Islands','Ap #820-2440 Lacus Rd','37047278889105','ipsum','(036036) 115816','semegetmassa@Quisquenet','mi eleifend egestas');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (62001,'4419666510152','fisica, juridica','Maite J Osborn','1023WW','Banda','UP','Czech Republic','PO Box 753, 7152 Lorem St','12007187467328','luctus et ultrices','(001) 76361146','senectus@temporbibendumca','velit Pellentesque');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (63001,'29511490862494','fisica, juridica','Bernard H Clay','49457-889','Puri','OR','Ireland','Ap #932-2530 Nec St','62436952113989','aliquet Proin velit','(014) 70111144','consequatnec@metusedu','enim Nunc ut');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (64001,'19050548112152','juridica, fisica','Reagan X Guzman','21490','Agartala','Tripura','Cambodia','337-1532 Justo St','21712712585599','dui,','(04157) 7262745','lectusNullamsuscipit@Crasedu','Sed molestie Sed id');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (65001,'24914840955425','juridica, fisica','Stephen Q Ferguson','9776','Algeciras','Andalucía','Dominica','142-5371 Semper Rd','4271361132578','est, mollis','(0185) 87723327','anteblandit@elitpedeorg','blandit congue In scelerisque scelerisque');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (66001,'16400147983193','juridica, fisica','Melodie B Nixon','62387-227','Wanneroo','Western Australia','Burundi','PO Box 791, 4101 Erat St','18841795778771','ligula eu enim','(00809) 1807156','senectus@egetcom','lacus, varius');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (67001,'85280478214705','juridica, fisica','Francis T Weeks','EW3V 4JM','Alcorcón','Madrid','Svalbard and Jan Mayen Islands','Ap #809-5328 Auctor Avenue','10743235913736','augue','(066) 18842294','elitsed@justonecanteorg','metus Aenean sed');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (68001,'32924817199668','fisica, juridica','Stacy Z Carrillo','1684','Villeneuve-d'Ascq','NO','Montenegro','PO Box 223, 5486 Sit Ave','66130544371758','blandit mattis','(0329) 69208729','orciluctus@magnanecca','magna');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (69001,'40986093322333','juridica, fisica','Curran P Blackwell','9968','Alcobendas','MA','Rwanda','1966 Dapibus Street','77933055572427','vitae, orci Phasellus','(053) 27248784','velest@aliquetliberoIntegeredu','In');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (70001,'32605672038964','fisica, juridica','Porter F Barker','31704','Gdynia','Pomorskie','Bonaire, Sint Eustatius and Saba','817-9180 Habitant Rd','19186399285868','eu','(031729) 468795','nuncestmollis@nonnet','cursus luctus, ipsum leo elementum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (71001,'78580044813307','juridica, fisica','Zephania S Jefferson','A3G 8A9','Cartagena','MU','Barbados','Ap #148-1186 Luctus Ave','55691849838522','Proin','(039079) 512331','rhoncus@etcommodoca','Class');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (72001,'32154104065918','juridica, fisica','Ainsley H Schneider','1674','Eindhoven','N','Saudi Arabia','Ap #597-9719 Dictum St','1699880357183','pharetra','(0015) 18624459','mollis@miacmattiscom','nisi a odio semper');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (73001,'37842401983608','juridica, fisica','Jonas T Dickson','5076','Sambalpur','Odisha','French Guiana','629-7324 Gravida St','21800996512051','facilisis','(035619) 981374','Curabitur@nullaorg','amet, risus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (74001,'32067610865951','juridica, fisica','Leo S Dale','7515','Tulsa','Oklahoma','Mauritania','9104 Metus St','27337919236127','interdum ligula eu','(0902) 76453579','neque@aliquamca','id, ante');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (75001,'69366493477393','juridica, fisica','Martina L Conrad','6255','Pievepelago','ER','Papua New Guinea','PO Box 875, 8551 Aenean Road','18372788507734','sed, sapien Nunc','(080) 81546697','pharetra@feugiatmetusorg','natoque');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (76001,'31934826861819','fisica, juridica','Brielle A Ingram','5016','St Catharines','ON','Afghanistan','7578 Curabitur St','44245943281331','semper','(033668) 111016','enimSuspendisse@duicom','vulputate, lacus Cras interdum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (77001,'12334977756524','juridica, fisica','Regina B Burton','48-132','Foz do Iguaçu','Paraná','Mauritania','Ap #428-3469 Fermentum Av','76060070216102','ante ipsum','(08940) 3849819','idantedictum@acmattisedu','egestas');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (78001,'40546922893945','fisica, juridica','Jolie V Hayes','82616','Valéncia','CV','Cayman Islands','718-9016 Non, Av','20684397957415','velit','(02096) 5419583','Donec@Nullafacilisiorg','nisi Aenean eget');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (79001,'98237364680088','juridica, fisica','Tarik A Mcneil','37579','New Orleans','Louisiana','Barbados','PO Box 734, 1625 Commodo St','47976365458491','nunc In','(035398) 391791','nisimagnased@eueratsemperorg','magna Nam ligula');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (80001,'15713824492603','fisica, juridica','Joy F Maynard','7136','Adoni','AP','Dominican Republic','453-414 Consequat, Rd','29253491878263','adipiscing,','(061) 88748409','conubianostra@nonmassanonedu','in sodales elit');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (81001,'74094685296233','juridica, fisica','Lars O York','51157','Leamington','ON','Papua New Guinea','444-3319 Quam Avenue','12596616838087','odio a purus','(03183) 5569845','velit@utdolornet','sed libero Proin sed turpis');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (82001,'9984498318758','fisica, juridica','Gail P Wade','R0X 9V6','Morwell','Victoria','Mozambique','PO Box 800, 9347 Arcu Road','13438240510068','In mi','(053) 22614668','lectuspede@quisnet','magna nec quam Curabitur');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (83001,'120448459815','fisica, juridica','Gay B Workman','2049QY','Louisville','KY','Latvia','582-2112 Eu Rd','87499807982465','Nullam vitae','(0042) 65396709','elitpellentesquea@montesnet','aliquet Proin');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (84001,'17380889498068','fisica, juridica','Scarlett J Roberson','BU70 9SM','Heidelberg','Baden','Mauritius','826-118 At Rd','59484502834055','et','(0602) 11595920','idmollisnec@tinciduntaliquamorg','nulla');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (85001,'1563986470024','juridica, fisica','Galvin O Norris','40323','Sosnowiec','Sląskie','Norfolk Island','598-6832 Vel Ave','15697751474564','at auctor ullamcorper,','(02598) 2083672','feugiat@viverraDoneccom','augue');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (86001,'18282835932745','fisica, juridica','Imogene W Rose','18-703','Le Mans','PA','Malta','Ap #444-4781 Arcu Av','15932754630593','sed pede','(038794) 932450','ornareegestasligula@Nullamedu','varius');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (87001,'1723283308917','juridica, fisica','Cassady C Pacheco','21364','Zielona Góra','LB','Liberia','3526 Erat Street','87171197226696','Maecenas malesuada','(036920) 583443','dolorelitpellentesque@idrisusca','consequat');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (88001,'32927286315916','fisica, juridica','Adena S Willis','5144','Winnipeg','Manitoba','Liberia','7560 Consequat St','59185871490662','risus','(0471) 05934552','dolor@risusDonecnibhnet','id nunc interdum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (89001,'93277074085694','fisica, juridica','Dolan O Obrien','5265','Leganés','Madrid','Guernsey','392-766 Integer St','13138062064251','Aliquam adipiscing','(05380) 0002465','egestashendrerit@esttemporbibendumcouk','lacus vestibulum lorem, sit amet');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (90001,'10650083991865','juridica, fisica','Raven D Eaton','6143','Breda','N','Andorra','Ap #865-6207 Felis Rd','26507727086273','Nullam','(014) 32060777','lacinia@Maurisvelturpisnet','Donec felis orci, adipiscing');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (91001,'28910057825891','fisica, juridica','Venus J Chapman','52283','San Pedro','San José','Israel','666-1287 Tincidunt Av','64966555360851','morbi','(01391) 1434277','ullamcorpervelitin@egetodioAliquamorg','id magna et ipsum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (92001,'21246550136318','juridica, fisica','Indira F Terry','6875','Newton Abbot','Devon','Finland','Ap #139-6164 Urna, Av','73987624973455','vulputate, posuere','(00723) 6106208','Sednullaante@Nullaca','diam eu');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (93001,'36377686646697','fisica, juridica','Patricia A Hayden','4378','Vienna','Wi','Kyrgyzstan','417-9829 Facilisis Road','36920256324998','cursus et, eros','(04640) 8629231','nislarcu@facilisica','vel turpis Aliquam adipiscing lobortis');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (94001,'67935743123255','fisica, juridica','Demetrius J Boyle','2753','Hengelo','Overijssel','Venezuela','PO Box 596, 8822 Metus Rd','57079721110897','Sed malesuada augue','(0953) 40210878','euismodacfermentum@ipsumnonca','arcu ac orci');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (95001,'43638179266821','fisica, juridica','Amena G Carr','72654','Moradabad','UP','India','Ap #440-4100 Non, Street','30034732596329','venenatis lacus','(0678) 08399671','mattisvelitjusto@turpisegestasorg','bibendum');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (96001,'56482766538013','juridica, fisica','Yeo F Merrill','Y6R 1OM','Madison','Wisconsin','Ecuador','PO Box 215, 6295 Adipiscing Av','23683468655718','quis, pede Suspendisse','(0153) 01995726','nunc@sedcom','lorem, auctor quis, tristique ac,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (97001,'1292953066001','juridica, fisica','Eric I Gallagher','8301','Gudivada','Andhra Pradesh','Saint Barthélemy','2930 Nunc St','13267111055334','est ac mattis','(04765) 9210875','Aenean@arcuimperdietcom','Nunc mauris elit, dictum eu,');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (98001,'45423939377633','fisica, juridica','Benedict E Carney','933603','Meridian','ID','Indonesia','Ap #633-6573 Ut, St','42691198042293','Morbi accumsan','(030643) 687440','a@atcom','facilisis, magna tellus');"; ExecutarBancoDeDados(sql);
			sql = "INSERT INTO CLIENTES (ID,CPFCNPJ,PESSOA,NOME,CEP,CIDADE,BAIRRO,ESTADO,RUA,NUMERO,COMPLEMENTO,FONE,EMAIL,OBSERVACAO) VALUES (99001,'35431425395439','juridica, fisica','Jeanette Y Morris','4668','Hamburg','Hamburg','Turkey','PO Box 367, 4219 Bibendum St','21583061362499','vitae erat','(085) 73465629','ac@noncom','viverra Maecenas iaculis aliquet diam');"; ExecutarBancoDeDados(sql);

}
void teste_stress_produto ()
{
	// Teste de stress
	char *sql;
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1,'Oxycodone HCl','93.11',8,'Finances','Lavasoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (101,'Ibuprofen (Rx)','28.34',5,'Quality Assurance','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (201,'Premarin','9.75',5,'Media Relations','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (301,'Hydrocodone/APAP','64.67',9,'Customer Relations','Macromedia');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (401,'Penicillin VK','66.85',10,'Advertising','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (501,'Fluconazole','35.72',4,'Customer Relations','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (601,'Lorazepam','30.30',4,'Advertising','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (701,'Lyrica','34.08',7,'Finances','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (801,'Glipizide','6.43',10,'Quality Assurance','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (901,'Cephalexin','45.76',6,'Human Resources','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1001,'Penicillin VK','69.01',9,'Legal Department','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1101,'Gabapentin','50.32',1,'Customer Relations','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1201,'Losartan Potassium','51.02',5,'Quality Assurance','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1301,'Triamterene/Hydrochlorothiazide','37.46',3,'Public Relations','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1401,'Crestor','27.98',5,'Public Relations','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1501,'Lisinopril','41.02',9,'Quality Assurance','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1601,'Ranitidine HCl','35.30',10,'Advertising','Apple Systems');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1701,'Fluticasone Propionate','96.97',6,'Tech Support','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1801,'Levaquin','99.20',8,'Sales and Marketing','Apple Systems');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (1901,'Sertraline HCl','34.11',9,'Research and Development','Apple Systems');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2001,'Oxycontin','21.51',6,'Accounting','Borland');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2101,'Simvastatin','34.51',6,'Public Relations','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2201,'Diazepam','97.61',5,'Accounting','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2301,'Ciprofloxacin HCl','21.51',2,'Finances','Sibelius');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2401,'Enalapril Maleate','13.44',9,'Asset Management','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2501,'Levaquin','95.32',7,'Finances','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2601,'Furosemide','66.72',7,'Quality Assurance','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2701,'Vyvanse','9.33',9,'Legal Department','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2801,'Cyclobenzaprin HCl','15.06',6,'Asset Management','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (2901,'Digoxin','96.14',5,'Payroll','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3001,'Citalopram HBr','40.60',10,'Sales and Marketing','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3101,'Lyrica','6.63',2,'Human Resources','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3201,'Lisinopril','32.98',1,'Quality Assurance','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3301,'Spiriva Handihaler','92.62',3,'Sales and Marketing','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3401,'Ciprofloxacin HCl','22.59',7,'Tech Support','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3501,'Enalapril Maleate','23.87',2,'Sales and Marketing','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3601,'Gabapentin','58.98',3,'Advertising','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3701,'Atenolol','63.66',1,'Media Relations','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3801,'TriNessa','80.42',9,'Human Resources','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (3901,'Amoxicillin Trihydrate/Potassium Clavulanate','59.89',2,'Sales and Marketing','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4001,'Prednisone','52.95',6,'Public Relations','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4101,'Carvedilol','69.27',9,'Advertising','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4201,'Methylprednisolone','34.57',10,'Sales and Marketing','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4301,'Doxycycline Hyclate','98.60',8,'Advertising','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4401,'Hydrochlorothiazide','66.20',2,'Asset Management','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4501,'Lantus','55.03',6,'Public Relations','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4601,'Doxycycline Hyclate','55.43',4,'Research and Development','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4701,'Tricor','22.29',10,'Customer Service','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4801,'Lisinopril','73.76',5,'Public Relations','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (4901,'Simvastatin','18.05',9,'Asset Management','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5001,'Nexium','77.23',8,'Finances','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5101,'Methylprednisolone','85.25',3,'Finances','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5201,'Omeprazole (Rx)','39.08',6,'Accounting','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5301,'Atenolol','35.67',6,'Research and Development','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5401,'Lipitor','44.70',6,'Tech Support','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5501,'Metformin HCl','73.40',2,'Customer Relations','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5601,'Azithromycin','61.82',7,'Research and Development','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5701,'Triamcinolone Acetonide','4.09',6,'Payroll','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5801,'Carvedilol','75.31',6,'Advertising','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (5901,'Metoprolol Tartrate ','51.70',9,'Customer Relations','Apple Systems');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6001,'Hydrocodone/APAP','31.73',2,'Media Relations','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6101,'Lexapro','3.78',5,'Human Resources','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6201,'Metoprolol Tartrate ','58.02',3,'Tech Support','Borland');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6301,'Warfarin Sodium','81.00',6,'Customer Service','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6401,'Proair HFA','92.19',9,'Legal Department','Borland');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6501,'Metoprolol Succinate','30.37',4,'Media Relations','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6601,'Vytorin','89.54',1,'Customer Service','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6701,'Amlodipine Besylate','56.62',10,'Research and Development','Borland');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6801,'Spiriva Handihaler','29.30',8,'Quality Assurance','Lavasoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (6901,'Venlafaxine HCl ER','47.27',9,'Public Relations','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7001,'Fluticasone Propionate','37.79',5,'Human Resources','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7101,'Fluticasone Propionate','78.95',10,'Accounting','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7201,'Klor-Con M20','52.45',10,'Asset Management','Sibelius');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7301,'Seroquel','15.54',10,'Customer Relations','Altavista');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7401,'Loestrin 24 Fe','20.73',1,'Customer Relations','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7501,'Penicillin VK','19.40',1,'Research and Development','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7601,'Symbicort','90.23',1,'Human Resources','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7701,'Digoxin','54.54',9,'Research and Development','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7801,'Lipitor','1.65',3,'Public Relations','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (7901,'Furosemide','80.70',4,'Payroll','Google');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8001,'Ciprofloxacin HCl','68.06',8,'Legal Department','Borland');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8101,'Alendronate Sodium','12.39',8,'Accounting','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8201,'Simvastatin','79.11',7,'Tech Support','Macromedia');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8301,'Amoxicillin','14.46',2,'Legal Department','Macromedia');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8401,'Januvia','30.84',9,'Research and Development','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8501,'Metformin HCl','44.26',3,'Finances','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8601,'Penicillin VK','81.41',10,'Finances','Microsoft');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8701,'Furosemide','15.77',2,'Sales and Marketing','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8801,'Hydrochlorothiazide','65.75',4,'Public Relations','Lycos');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (8901,'Famotidine','7.36',7,'Payroll','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9001,'Cephalexin','34.94',7,'Asset Management','Yahoo');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9101,'Ranitidine HCl','12.67',7,'Customer Relations','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9201,'Meloxicam','48.60',4,'Legal Department','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9301,'Omeprazole (Rx)','60.16',5,'Sales and Marketing','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9401,'Niaspan','27.37',8,'Sales and Marketing','Finale');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9501,'Fluticasone Propionate','47.03',1,'Customer Relations','Adobe');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9601,'Hydrocodone/APAP','26.75',9,'Human Resources','Macromedia');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9701,'Atenolol','30.48',5,'Legal Department','Chami');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9801,'Levaquin','12.17',3,'Asset Management','Cakewalk');";ExecutarBancoDeDados(sql);
	sql = "INSERT INTO PRODUTOS (ID,NOME,VALOR,QUANTIDADE,CATEGORIA,DESCRICAO) VALUES (9901,'Levaquin','18.13',3,'Media Relations','Chami');";ExecutarBancoDeDados(sql);
	
}
// Testes // TODO REMOVER MAIS TARDE ------------------

void InicializarBancoDeDados()
{

	srand(time(NULL)); // inicializa o rand com uma seed fo tempo

	database_open();
	
	// TODO: tratar isso, quando a tabela ja exisitr, nem tentar criar.
	// ----- A ordem precisa ser esta pois existem tabelas associativas que referenciam chaves PK de outras tabelas, que precisam estar previamente definidas ----- 
	cria_tabela_clientes();
	cria_tabela_produtos();
	cria_tabela_vendas();
	cria_tabela_produtos_vendas();
	// ----- A ordem precisa ser esta pois existem tabelas associativas que referenciam chaves PK de outras tabelas, que precisam estar previamente definidas ----- 

	teste_stress_cliente();
	teste_stress_produto();
}





















// ---------------------------------- FUNÇÕES ESPECIAIS DO CORE PARA SELECIONAR PKS DE TABELAS, PARA INSTACIAR OBJETOS DO BANCO DE DADOS ---------------------------------- 
/*Auxiçiars função que permite descobrir todas as pks de uma tabela de forma automatica*/
int num_pks; // uso interno apenas pela funcao "get_pk_vector"
int *pk_vector; // uso interno apenas pela funcao "get_pk_vector"
int tmp_pk_vector_counter;
static int count_pk_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	char resultset[256] = {0}; // cria terminação nula, para zerar a string, e fazer o strcat funcionar direito
	for(i=0; i<argc; i++)
	{
		printf("PK: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		num_pks++;
	}
	printf("\n");
	return 0;
}
static int retrive_pk_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	char resultset[256] = {0}; // cria terminação nula, para zerar a string, e fazer o strcat funcionar direito
	for(i=0; i<argc; i++)
	{
		// printf("PK: %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		pk_vector[tmp_pk_vector_counter] = atoi(argv[i]);
		tmp_pk_vector_counter++;
	}
	printf("\n");
	return 0;
}
/*Função que permite descobrir todas as pks de uma tabela de forma automatica - NÃO SE ESQUECA DE LIBERAR O RETORNO DESTA FUNCAO DEPOIS DE USA-LA*/
int *get_pk_vector(char *pk_name, char *table_name, char *condition, int *table_size)
{
	char *zErrMsg = 0;
	int rc;
	char sql[512];
	const char* data = "Callback for detecting PKS function called";
	num_pks = 0;
	sprintf(sql, "SELECT %s from %s %s", pk_name, table_name, condition);
	
	// Execute SQL statement para contar o numero de pks
	rc = sqlite3_exec(db, sql, count_pk_callback, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}

	*table_size = num_pks; // retorna o valor por parametro
	tmp_pk_vector_counter = 0;
	// aloca vetor
	pk_vector = (int*)malloc(sizeof(int)*num_pks);
	// Execute SQL statement para pegar as pks
	rc = sqlite3_exec(db, sql, retrive_pk_callback, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}
	return pk_vector;
}
// ---------------------------------- FUNÇÕES ESPECIAIS DO CORE PARA SELECIONAR PKS DE TABELAS, PARA INSTACIAR OBJETOS DO BANCO DE DADOS ---------------------------------- 