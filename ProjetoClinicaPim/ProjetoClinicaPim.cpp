#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <io.h>
#include <time.h>

int op;
//Estrutura da tabela endereço
typedef struct {
	char logradouro[50];
	char complemento[20];
	float cep;
	char bairro[20];
	char cidade[20];
}End;

//Estrutura da tabela paciente
typedef struct {
	int codigo;
	char nome[50];
	char sexo[2];
	float rg;
	float telefone;
	char email;
	End endereco;
}Pct;
Pct aux;

typedef struct {
	int codigo;
	char nome[50];
	char especialidade[50];
}Mdc;


//Estrutura da tabela Exames
typedef struct {
	int codigo;
	char nome[50];
	float valor;
}Exm;

typedef struct {
	int codigo;
	char nome[50];
}Uni;

typedef struct {
	int codigo;
	int dia;
	int mes;
	int ano;
	Pct pacienteQuePediu;
	Exm* examePedido;
	int qtd;
	Uni UnidadeParaAgendar;
}Agd;

typedef struct {
	char usuario[20];
	char senha[20];
	char unidade[2];
}User;



//Declaração da função que de Menu
void menu();

//Declaração da função que gerencia os Paciente
void gerenciaDePaciente(Pct*, int*, FILE*);
Pct cadastrarPaciente(Pct, int);
void listarPaciente(Pct*, int);
void buscarPaciente(Pct*, int);
void AtualizarPaciente(Pct*, int);
void imprimirPaciente(Pct);

//Declaração da função que gerencia os Exame
void gerenciaDeExame(Exm*, int*, FILE*);
Exm cadastrarExame(Exm, int);
void listarExame(Exm*, int);
void buscarExame(Exm*, int);
void AtualizarExame(Exm*, int);
void imprimirExame(Exm);

//Declaração da função que gerencia os Exame
void gerenciaDeMedico(Mdc*, int*, FILE*);
Mdc cadastrarMedico(Mdc, int);
void listarMedico(Mdc*, int);
void buscarMedico(Mdc*, int);
void AtualizarMedico(Mdc*, int);
void imprimirMedico(Mdc);

//Declaração da função que gerencia os Agendamento
void gerenciaDeAgendamento(Agd*, Pct*, Exm*, Uni*, int*, int, int, int);
void cadastrarAgendamento(Agd*, Pct*, Exm*, Uni*, int*, int, int, int);
void obterData(Agd*);
void listarAgendamentoDeUmPaciente(Agd*, int);
void ListarAgendamentoDeUmDia(Agd*, int);
void AtualizarAgendamento(Agd*, int);
void imprimirAgendamento(Agd);



//Função Principal
int main() {



	FILE* arquivo; //Declarando um arquivo
	Pct* paciente; //Declarando um ponteiro para estrutura paciente
	Mdc* medico; //Declarando um ponteiro para estrutura paciente
	Exm* exame; //Declarando um ponteiro para estrutura exame
	Agd* agendamento; //Declarando um ponteiro para estrutura agendamento
	Uni* unidade; //Declarando um ponteiro para estrutura de uniadades hospitalares
	User* usuario; //Declarando um ponteiro para estrutura agendamento

	int contPaciente = 2, contExame = 2, contMedico = 0, contAgendamento = 0, contUnidade = 2; //Inicilizando os contadores
	arquivo = calloc(100, sizeof(FILE));
	paciente = calloc(100, sizeof(Pct));
	exame = calloc(100, sizeof(Exm));
	medico = calloc(100, sizeof(Mdc));
	agendamento = calloc(100, sizeof(Agd));
	usuario = calloc(50, sizeof(User));
	unidade = calloc(50, sizeof(Uni));

	// inicializa Pacientes e exmes
	for (int i = 0; i < 50; i++) {
		paciente[i].codigo = 0;
		strcpy(paciente[i].nome, "");
		strcpy(paciente[i].sexo, "");
		paciente[i].rg = 0;
		paciente[i].telefone = 0;
		strcpy(paciente[i].endereco.logradouro, "");
		strcpy(paciente[i].endereco.complemento, "");
		paciente[i].endereco.cep = 0;
		strcpy(paciente[i].endereco.bairro, "");
		strcpy(paciente[i].endereco.cidade, "");

		exame[i].codigo = 0;
		strcpy(exame[i].nome, "");
		exame[i].valor = 0.0;

		unidade[i].codigo = 0;
		strcpy(unidade[i].nome, "");
	}

	//Inclui dados dos usuarios
	strcpy(usuario[0].usuario, "junior");
	strcpy(usuario[0].senha, "123");
	strcpy(usuario[0].unidade, "1");

	strcpy(usuario[1].usuario, "lydia");
	strcpy(usuario[1].senha, "123");
	strcpy(usuario[1].unidade, "1");

	strcpy(usuario[2].usuario, "joao");
	strcpy(usuario[2].senha, "123");
	strcpy(usuario[2].unidade, "2");

	//Inclui dados do Paciente 1
	paciente[0].codigo = 1;
	strcpy(paciente[0].nome, "Lydia");
	strcpy(paciente[0].sexo, "f");
	paciente[0].rg = 1234;
	paciente[0].telefone = 11940633029;
	strcpy(paciente[0].endereco.logradouro, "Naosei");
	strcpy(paciente[0].endereco.complemento, "ntem");
	paciente[0].endereco.cep = 051615203;
	strcpy(paciente[0].endereco.bairro, "Naofacodeia");
	strcpy(paciente[0].endereco.cidade, "ola");

	//Inclui dados do Paciente 2
	paciente[1].codigo = 2;
	strcpy(paciente[1].nome, "Junior");
	strcpy(paciente[1].sexo, "m");
	paciente[1].rg = 12313;
	paciente[1].telefone = 1137268225;
	strcpy(paciente[1].endereco.logradouro, "Avenida trona");
	strcpy(paciente[1].endereco.complemento, "Ola amigios");
	paciente[1].endereco.cep = 05516020;
	strcpy(paciente[1].endereco.bairro, "Caxingui");
	strcpy(paciente[1].endereco.cidade, "SP");

	//Inclui dados do Exame 1
	exame[0].codigo = 1;
	strcpy(exame[0].nome, "Urologista");
	exame[0].valor = 500.0;

	//Inclui dados do Exame 2
	exame[1].codigo = 2;
	strcpy(exame[1].nome, "Pediatra");
	exame[1].valor = 300.0;


	unidade[0].codigo = 1;
	strcpy(unidade[0].nome, "Hospital LeForte");

	unidade[1].codigo = 2;
	strcpy(unidade[1].nome, "Hospital Albert");

	/*
	char login[20];
	char psw[20];
	char uni[2];
	int acesso = 0;
	//Estrutura de login
	do
	{

		printf("\n____________________________________________\n");
		printf("|         Clinica NoMercy	           |");
		printf("\n|__________________________________________|\n\n");
		printf("         BEM VINDO       \n");
		printf("         Usuario: ");
		scanf(" %[^\n]s", &login);
		printf("         Senha: ");
		scanf(" %[^\n]s", &psw);
		printf("         Unidade: ");
		scanf(" %[^\n]s", &uni);

		for (int i = 0; i < 5; i++)
		{
			if (strcmp(usuario[i].usuario, login) == 0 && strcmp(usuario[i].senha, psw) == 0 && strcmp(usuario[i].unidade, uni) == 0)
			{
				printf("Entrada de %s autorizada com sucesso!\n\n", usuario[i].usuario);
				system("pause");
				system("cls");
				acesso = 1;
			}
		}
	} while (acesso == 0);
	*/
	menu();
	do {//Ciclo que controlara o funcionamento do programa
		switch (op)
		{
		case 0:printf("Obrigado, Volte Logo!");
			exit(1);
			break;
		case 1:
			gerenciaDePaciente(paciente, &contPaciente, arquivo);
			break;
		case 2:
			gerenciaDeExame(exame, &contExame, arquivo);
			break;
		case 3:
			gerenciaDeMedico(medico, &contMedico, arquivo);
			break;
		case 4:
			gerenciaDeAgendamento(agendamento, paciente, exame, unidade, &contAgendamento, contPaciente, contExame, contUnidade);
			break;
		default:
			printf("	!!COMANDO INVALIDO!!\n	Entre com o comando novamente\n");
			system("pause");
			system("cls");
			menu();
		}
	} while (1);

	return 0;
}//fim da função principal


void menu() {
	printf("\n____________________________________________\n");
	printf("|         Clinica NoMercy	           |");
	printf("\n|__________________________________________|\n\n");
	printf("	1 - Gerencia de Pacientes\n");
	printf("	2 - Gerencia de Exame\n");
	printf("	3 - Gerencia de Medico\n");
	printf("	4 - Gerencia de Agendamentos\n");
	printf("	0 - Sair\n");
	printf("Digite um comando para prosseguir: ");
	scanf(" %d", &op);
	system("cls");
}



// Codigo da função que gerencia os pacientes
void gerenciaDePaciente(Pct* paciente, int* contPaciente, FILE* arquivo) {
	int opcao;

	do
	{

		printf("\n____________________________________________\n");
		printf("|         Gerencia de Pacientes	           |");
		printf("\n|__________________________________________|\n\n");
		printf("	1 - Cadastro de Pacientes\n");
		printf("	2 - Listar Pacientes Cadastrado\n");
		printf("	3 - Buscar Pacientes Cadastrado\n");
		printf("	4 - Atualizar Pacientes Cadastrado\n");
		printf("	0 - Voltar ao menu principal\n");
		printf("Digite um comando para prosseguir: ");
		scanf(" %d", &opcao);
		system("cls");

		switch (opcao)
		{
		case 0:
			menu();
			break;
		case 1:
			arquivo = fopen("pacientes.txt", "a+");
			if (arquivo == NULL) {
				printf("Nao foi possivel abrir o arquivo.");
				return;
			}
			printf("\n____________________________________________\n");
			printf("|         Cadastro de Pacientes	           |");
			printf("\n|__________________________________________|\n");
			paciente[*contPaciente] = cadastrarPaciente(paciente[*contPaciente], 0);

			fprintf(arquivo, "%d;%s;%s;%.0f;%.0f;%s;%s;%.0f;%s;%s\n", paciente[*contPaciente].codigo, paciente[*contPaciente].nome, paciente[*contPaciente].sexo, paciente[*contPaciente].rg,
				paciente[*contPaciente].telefone, paciente[*contPaciente].endereco.logradouro, paciente[*contPaciente].endereco.complemento, paciente[*contPaciente].endereco.cep,
				paciente[*contPaciente].endereco.bairro, paciente[*contPaciente].endereco.cidade);
			fclose(arquivo);

			*contPaciente += 1;
			if (*contPaciente == 10)
				paciente = realloc(paciente, (*contPaciente + 1) * sizeof(Pct));
			break;
		case 2:
			listarPaciente(paciente, *contPaciente);
			break;
		case 3:
			buscarPaciente(paciente, *contPaciente);
			break;
		case 4:
			AtualizarPaciente(paciente, *contPaciente);
			break;
		case 5:
			arquivo = fopen("pacientes.txt", "rb");
			printf("__________Abrindo o banco de dados____________\n");

			while (fgets(paciente, 20, arquivo) != NULL)
				printf("%s", paciente);

			fclose(arquivo);
			break;
		default:
			printf("	!!OPCAO INVALIDA\n	Digite novamente outra opcao\n");
			system("pause");
			system("cls");
		}
		break;
	} while (1);
}

//Função que cadastra paciente
Pct cadastrarPaciente(Pct paciente, int identificador) {
	char aux[15];

	do
	{
		printf("	Codigo do paciente: ");
		scanf("%s", aux);

		paciente.codigo = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (paciente.codigo == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Pacientes =======\n");
				continue;
			}
		}
		else
		{
			if (paciente.codigo == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);

	printf("	Nome do paciente: ");
	scanf(" %[a-z A-Z]s", paciente.nome);
	printf("	Sexo do paciente [m/f]: ");
	scanf(" %[^\n]s", paciente.sexo);
	do
	{
		printf("	Rg: ");
		scanf("%10s", aux);

		paciente.rg = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (paciente.rg == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Pacientes =======\n");
				continue;
			}
		}
		else
		{
			if (paciente.rg == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);
	do
	{
		printf("	Telefone: ");
		scanf("%10s", aux);

		paciente.telefone = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (paciente.telefone == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Pacientes =======\n");
				continue;
			}
		}
		else
		{
			if (paciente.telefone == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);
	printf("	Logradouro: ");
	scanf("		%[^\n]s", paciente.endereco.logradouro);
	printf("	Complemento: ");
	scanf(" %[^\n]s", paciente.endereco.complemento);
	do
	{
		printf("	CEP: ");
		scanf("%10s", aux);

		paciente.endereco.cep = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (paciente.endereco.cep == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Pacientes =======\n");
				continue;
			}
		}
		else
		{
			if (paciente.endereco.cep == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);
	printf("	Bairro: ");
	scanf(" %[^\n]s", paciente.endereco.bairro);
	printf("	Cidade: ");
	scanf(" %[^\n]s", paciente.endereco.cidade);

	if (identificador == 0) {
		printf("Cadastro Realizado com sucesso\n");
		system("pause");
		system("cls");
	}
	return paciente;
}

//Função que lista um paciente selecionado;
void listarPaciente(Pct* paciente, int contPaciente) {
	printf("\n____________________________________________\n");
	printf("|         lista de Pacientes	           |");
	printf("\n|__________________________________________|\n");
	int i;
	if (contPaciente == 0)
	{
		printf("		!!ERRO\n	NUM UM PACIENTE CADASTRADO\n");
		system("pause");
		system("cls");
		return;
	}
	printf("LISTA DE PACIENTES CADASTRADOS\n\n");
	for (i = 0; i < contPaciente; i++)
		imprimirPaciente(paciente[i]);

	system("pause");
	system("cls");
}

void imprimirPaciente(Pct paciente) {
	printf("\nCodigo: %d\n", paciente.codigo);
	printf("Nome: %s\n", paciente.nome);
	printf("Sexo: %s\n", paciente.sexo);
	printf("RG: %.0f\n", paciente.rg);
	printf("Telefone: %.0f\n", paciente.telefone);
	printf("Endereco: %s / Complemento %s\n", paciente.endereco.logradouro, paciente.endereco.complemento);
	printf("CEP:  %.0f\n", paciente.endereco.cep);
	printf("Bairro: %s\n", paciente.endereco.bairro);
	printf("Cidade: %s\n", paciente.endereco.cidade);

}

void buscarPaciente(Pct* paciente, int contPaciente) {
	printf("\n____________________________________________\n");
	printf("|         busca de Pacientes	           |");
	printf("\n|__________________________________________|\n");
	int i, marcador = 0;
	int codigoPaciente;
	char nomePaciente[50];

	printf("Digite o nome ou o codigo do paciente que deseja buscar: ");
	scanf(" %[^\n]s", nomePaciente);
	printf("\n");
	codigoPaciente = strtol(nomePaciente, NULL, 10);

	for (i = 0; i < contPaciente; i++)
	{
		if (paciente[i].codigo == codigoPaciente || strcmp(paciente[i].nome, nomePaciente) == 0)
		{
			imprimirPaciente(paciente[i]);
			marcador = 1;
			break;
		}
	}
	if (!marcador)
	{
		printf("		!!ERRO!!\n	PACIENTE NAO CADASTRADO\n");
	}
	system("pause");
	system("cls");
}


void AtualizarPaciente(Pct* paciente, int contPaciente) {
	int codigo, i, marcador = 0;

	char codigoPaciente[10];

	do
	{
		printf("Codigo do paciente que deseja atualizar: ");
		scanf(" %s", codigoPaciente);

		codigo = strtol(codigoPaciente, NULL, 10);
		if (codigo == 0)
		{
			printf("\n			!!ERRO!!\n	Apenas numeros para o codigo\n");
			system("pause");
			system("cls");
			continue;
		}break;

	} while (1);
	for (i = 0; i < contPaciente; i++)
	{
		if (paciente[i].codigo == codigo)
		{
			marcador = 1;
			break;
		}
	}
	if (!marcador)
		printf("\n		!!ERRO!!\n	PACIENTE NAO CADASTRADO\n");
	else
	{
		printf("	\nENTRE COM OS DADOS ATUALIZADOS\n");
		//inicializa todas as naves como disponiveis
		aux = cadastrarPaciente(aux, -1);

		if (aux.codigo > 0)
			paciente[i].codigo = aux.codigo;
		if (strlen(aux.nome) > 0)
			strcpy(paciente[i].nome, aux.nome);
		if (aux.rg > 0);
		paciente[i].rg = aux.rg;
		if (aux.telefone > 0);
		paciente[i].telefone = aux.telefone;
		if (strlen(aux.endereco.logradouro) > 0)
			strcpy(paciente[i].endereco.logradouro, aux.endereco.logradouro);
		if (strlen(aux.endereco.complemento) > 0)
			strcpy(paciente[i].endereco.complemento, aux.endereco.complemento);
		if (aux.endereco.cep > 0)
			paciente[i].endereco.cep = aux.endereco.cep;
		if (strlen(aux.endereco.bairro) > 0)
			strcpy(paciente[i].endereco.bairro, aux.endereco.bairro);
		if (strlen(aux.endereco.cidade) > 0)
			strcpy(paciente[i].endereco.cidade, aux.endereco.cidade);

		printf("	\nPACIENTE ATUALIZADO COM SUCESSO\n");
	}
	system("pause");
	system("cls");
}

// Codigo da função que gerencia os exames
void gerenciaDeExame(Exm* exame, int* contExame, FILE* arquivo) {
	int opcao;
	int i = 0;

	do
	{
		printf("\n____________________________________________\n");
		printf("|         Gerencia de Exames	           |");
		printf("\n|__________________________________________|\n\n");
		printf("	1 - Cadastro de Exames\n");
		printf("	2 - Listar Exames Cadastrado\n");
		printf("	3 - Buscar Exames Cadastrado\n");
		printf("	4 - Atualizar Exames Cadastrado\n");
		printf("	0 - Voltar ao menu principal\n");
		printf("Digite um comando para prosseguir: ");
		scanf("%d", &opcao);
		system("cls");

		switch (opcao)
		{
		case 0:

			menu();
			break;
		case 1:
			arquivo = fopen("exames.txt", "a+");
			if (arquivo == NULL) {
				printf("Nao foi possivel abrir o arquivo.");
				return;
			}
			printf("\n____________________________________________\n");
			printf("|         Cadastro de Exames	           |");
			printf("\n|__________________________________________|\n");
			exame[*contExame] = cadastrarExame(exame[*contExame], 0);

			fprintf(arquivo, "%d;%s;%.2f;\n", exame[*contExame].codigo, exame[*contExame].nome, exame[*contExame].valor);
			fclose(arquivo);

			*contExame += 1;
			if (*contExame == 10)
				exame = realloc(exame, (*contExame + 1) * sizeof(Exm));
			break;
		case 2:
			listarExame(exame, *contExame);
			break;
		case 3:
			buscarExame(exame, *contExame);
			break;
		case 4:
			AtualizarExame(exame, *contExame);
			break;
		case 5:
			arquivo = fopen("exames.txt", "rb");
			printf("__________Abrindo o banco de dados____________\n");

			while (fgets(exame, 20, arquivo) != NULL)
				printf("%s", exame);

			fclose(arquivo);
			break;
		default:
			printf("	!!OPCAO INVALIDA\n	Digite novamente outra opcao\n");
			system("pause");
			system("cls");
		}
		break;
	} while (1);
}

//Função que cadastra exame
Exm cadastrarExame(Exm exame, int identificador) {
	char aux[15];

	do
	{
		printf("	Codigo do exame: ");
		scanf("%10s", aux);

		exame.codigo = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (exame.codigo == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Exames =======\n");
				continue;
			}
		}
		else
		{
			if (exame.codigo == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);

	printf("	Nome do exame: ");
	scanf(" %[a-z A-Z]s", exame.nome);
	do
	{
		printf("	Valor do exame:R$ ");
		scanf("%10s", aux);
		exame.valor = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (exame.valor == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o valor\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Exames =======\n");
				continue;
			}
		}
		else
		{
			if (exame.valor == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o valor\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);

	if (identificador == 0) {
		printf("Cadastro Realizado com sucesso\n");
		system("pause");
		system("cls");

	}
	return exame;
}

//Função que lista um exame selecionado;
void listarExame(Exm* exame, int contExame) {
	printf("\n____________________________________________\n");
	printf("|         lista de Exames	           |");
	printf("\n|__________________________________________|\n");
	int i;
	if (contExame == 0)
	{
		printf("		!!ERRO\n	NUM UM EXAME CADASTRADO\n");
		system("pause");
		system("cls");
		return;
	}
	printf("LISTA DE EXAMES CADASTRADOS\n\n");
	for (i = 0; i < contExame; i++)
		imprimirExame(exame[i]);

	system("pause");
	system("cls");
}

void imprimirExame(Exm exame) {
	printf("\nCodigo: %d\n", exame.codigo);
	printf("Nome: %s\n", exame.nome);
	printf("Valor:R$ %.2f\n", exame.valor);

}

void buscarExame(Exm* exame, int contExame) {
	printf("\n____________________________________________\n");
	printf("|         busca de Exames	           |");
	printf("\n|__________________________________________|\n");
	int i, marcador = 0;
	int codigoExame;
	char nomeExame[50];

	printf("Digite o nome ou o codigo do exame que deseja buscar: ");
	scanf(" %[^\n]s", nomeExame);
	printf("\n");
	codigoExame = strtol(nomeExame, NULL, 10);

	for (i = 0; i < contExame; i++)
	{
		if (exame[i].codigo == codigoExame || strcmp(exame[i].nome, nomeExame) == 0)
		{
			imprimirExame(exame[i]);
			marcador = 1;
			break;
		}
	}
	if (!marcador)
	{
		printf("		!!ERRO!!\n	EXAME NAO CADASTRADO\n");
	}
	system("pause");
	system("cls");
}

Exm auxs;
void AtualizarExame(Exm* exame, int contExame) {
	int codigo, i, marcador = 0;
	char codigoExame[10];

	do
	{
		printf("Codigo do exame que deseja atualizar: ");
		scanf(" %s", codigoExame);

		codigo = strtol(codigoExame, NULL, 10);
		if (codigo == 0)
		{
			printf("\n			!!ERRO!!\n	Apenas numeros para o codigo\n");
			system("pause");
			system("cls");
			continue;
		}break;

	} while (1);
	for (i = 0; i < contExame; i++)
	{
		if (exame[i].codigo == codigo)
		{
			marcador = 1;
			break;
		}
	}
	if (!marcador)
		printf("\n		!!ERRO!!\n	EXAME NAO CADASTRADO\n");
	else
	{
		printf("	\nENTRE COM OS DADOS ATUALIZADOS\n");
		//inicializa todas as naves como disponiveis
		auxs = cadastrarExame(auxs, -1);

		if (auxs.codigo > 0)
			exame[i].codigo = auxs.codigo;
		if (strlen(aux.nome) > 0)
			strcpy(exame[i].nome, auxs.nome);
		if (auxs.valor > 0)
			exame[i].valor = auxs.valor;


		printf("	\nEXAME ATUALIZADO COM SUCESSO\n");
	}
	system("pause");
	system("cls");
}

// Codigo da função que gerencia os medicos
void gerenciaDeMedico(Mdc* medico, int* contMedico, FILE* arquivo) {
	int opcao;
	do
	{

		printf("\n____________________________________________\n");
		printf("|         Gerencia de Medicos	           |");
		printf("\n|__________________________________________|\n\n");
		printf("	1 - Cadastro de Medicos\n");
		printf("	2 - Listar Medicos Cadastrado\n");
		printf("	3 - Buscar Medicos Cadastrado\n");
		printf("	4 - Atualizar Medicos Cadastrado\n");
		printf("	0 - Voltar ao menu principal\n");
		printf("Digite um comando para prosseguir: ");
		scanf("%d", &opcao);
		system("cls");

		switch (opcao)
		{
		case 0:menu();
			break;
		case 1:
			arquivo = fopen("medicos.txt", "a+");
			if (arquivo == NULL) {
				printf("Nao foi possivel abrir o arquivo.");
				return;
			}
			printf("\n____________________________________________\n");
			printf("|         Cadastro de Medicos	           |");
			printf("\n|__________________________________________|\n");
			medico[*contMedico] = cadastrarMedico(medico[*contMedico], 0);

			fprintf(arquivo, "%d;%s;%s;\n", medico[*contMedico].codigo, medico[*contMedico].nome, medico[*contMedico].especialidade);
			fclose(arquivo);

			*contMedico += 1;
			if (*contMedico == 10)
				medico = realloc(medico, (*contMedico + 1) * sizeof(Mdc));
			break;
		case 2:
			listarMedico(medico, *contMedico);
			break;
		case 3:
			buscarMedico(medico, *contMedico);
			break;
		case 4:
			AtualizarMedico(medico, *contMedico);
			break;
		case 5:
			arquivo = fopen("medicos.txt", "rb");
			printf("__________Abrindo o banco de dados____________\n");

			while (fgets(medico, 20, arquivo) != NULL)
				printf("%s", medico);

			fclose(arquivo);
			break;
		default:
			printf("	!!OPCAO INVALIDA\n	Digite novamente outra opcao\n");
			system("pause");
			system("cls");
		}
		break;
	} while (1);
}

//Função que cadastra medico
Mdc cadastrarMedico(Mdc medico, int identificador) {
	char aux[15];

	do
	{
		printf("	Codigo do medico: ");
		scanf("%s", aux);

		medico.codigo = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
		if (identificador == 0)
		{
			if (medico.codigo == 0)
			{
				printf("\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				printf("	\n======= Cadastro de Medicos =======\n");
				continue;
			}
		}
		else
		{
			if (medico.codigo == 0 && strlen(aux) > 0)
			{
				printf("		\n!!OPCAO INVALIDA\nApenas numeros para o codigo\n");
				system("pause");
				system("cls");
				continue;
			}
		}
		break;
	} while (1);

	printf("	Nome do medico: ");
	scanf(" %[a-z A-Z]s", medico.nome);
	printf("	Especialidade: ");
	scanf(" %[^\n]s", medico.especialidade);

	if (identificador == 0) {
		printf("Cadastro Realizado com sucesso\n");
		system("pause");
		system("cls");
	}
	return medico;
}

//Função que lista um medico selecionado;
void listarMedico(Mdc* medico, int contMedico) {
	printf("\n____________________________________________\n");
	printf("|         lista de Medicos	           |");
	printf("\n|__________________________________________|\n");
	int i;
	if (contMedico == 0)
	{
		printf("		!!ERRO\n	NUM UM MEDICO CADASTRADO\n");
		system("pause");
		system("cls");
		return;
	}
	printf("LISTA DE MEDICOS CADASTRADOS\n\n");
	for (i = 0; i < contMedico; i++)
		imprimirMedico(medico[i]);

	system("pause");
	system("cls");
}

void imprimirMedico(Mdc medico) {
	printf("\nCodigo: %d\n", medico.codigo);
	printf("Nome: %s\n", medico.nome);
	printf("Sexo: %s\n", medico.especialidade);
}

void buscarMedico(Mdc* medico, int contMedico) {
	printf("\n____________________________________________\n");
	printf("|         busca de Medicos	           |");
	printf("\n|__________________________________________|\n");
	int i, marcador = 0;
	int codigoMedico;
	char nomeMedico[50];

	printf("Digite o nome ou o codigo do medico que deseja buscar: ");
	scanf(" %[^\n]s", nomeMedico);
	printf("\n");
	codigoMedico = strtol(nomeMedico, NULL, 10);

	for (i = 0; i < contMedico; i++)
	{
		if (medico[i].codigo == codigoMedico || strcmp(medico[i].nome, nomeMedico) == 0)
		{
			imprimirMedico(medico[i]);
			marcador = 1;
			break;
		}
	}
	if (!marcador)
	{
		printf("		!!ERRO!!\n	MEDICO NAO CADASTRADO\n");
	}
	system("pause");
	system("cls");
}

Mdc auxMedico;
void AtualizarMedico(Mdc* medico, int contMedico) {
	int codigo, i, marcador = 0;

	char codigoMedico[10];

	do
	{
		printf("Codigo do medico que deseja atualizar: ");
		scanf(" %s", codigoMedico);

		codigo = strtol(codigoMedico, NULL, 10);
		if (codigo == 0)
		{
			printf("\n			!!ERRO!!\n	Apenas numeros para o codigo\n");
			system("pause");
			system("cls");
			continue;
		}break;

	} while (1);
	for (i = 0; i < contMedico; i++)
	{
		if (medico[i].codigo == codigo)
		{
			marcador = 1;
			break;
		}
	}
	if (!marcador)
		printf("\n		!!ERRO!!\n	MEDICO NAO CADASTRADO\n");
	else
	{
		printf("	\nENTRE COM OS DADOS ATUALIZADOS\n");
		//inicializa todas as naves como disponiveis
		auxMedico = cadastrarMedico(auxMedico, -1);

		if (auxMedico.codigo > 0)
			medico[i].codigo = auxMedico.codigo;
		if (strlen(auxMedico.nome) > 0)
			strcpy(medico[i].nome, auxMedico.nome);
		if (strlen(auxMedico.especialidade) > 0)
			strcpy(medico[i].especialidade, auxMedico.especialidade);

		printf("	\nMEDICO ATUALIZADO COM SUCESSO\n");
	}
	system("pause");
	system("cls");
}

void  gerenciaDeAgendamento(Agd* agendamento, Pct* paciente, Exm* exame, Uni* unidade, int* contAgendamento, int contPaciente, int contExame, int contUnidade) {
	int opcao;
	int i = 0;

	do
	{

		printf("\n____________________________________________\n");
		printf("|         Gerencia de Agendamentos	           |");
		printf("\n|__________________________________________|\n\n");
		printf("	1 - Cadastro de Agendamento\n");
		printf("	2 - Listar todos os agendamentos de um paciente\n");
		printf("	3 - Listar todos os pedidos de um dia especifico\n");
		printf("	4 - Atualizar Pacientes Cadastrado\n");
		printf("	0 - Voltar ao menu principal\n");
		printf("Digite um comando para prosseguir: ");
		scanf("%d", &opcao);
		system("cls");

		switch (opcao)
		{
		case 0:
			system("cls");
			menu();
			break;
		case 1:cadastrarAgendamento(agendamento, paciente, exame, unidade, contAgendamento, contPaciente, contExame, contUnidade);
			break;
		case 2:
			listarAgendamentoDeUmPaciente(agendamento, *contAgendamento);
			break;
		case 3:
			ListarAgendamentoDeUmDia(agendamento, *contAgendamento);
			break;
			/*case 4:
				AtualizarAgendamento(paciente, *contAgendamento);
				break;*/
		default:
			printf("	!!OPCAO INVALIDA\nDigite novamente outra opcao\n");
			system("pause");
			system("cls");
		}
		break;
	} while (1);
}

void cadastrarAgendamento(Agd* agendamento, Pct* paciente, Exm* exame, Uni* unidade, int* contAgendamento, int contPaciente, int contExame, int contUnidade) {
	char nomePaciente[50];
	int codigoPaciente, unidadeParaCadastro = 0 , marcador = 0;
	int codigoExameParaCadastro;
	int qtdExame;
	int i, j, auxIndice = 0;
	char opcao = "";

	printf("\n____________________________________________\n");
	printf("|         Cadastro de Agendamento	         |");
	printf("\n|__________________________________________|\n\n");
	printf("Digite o codigo ou o nome do paciente que esta fazendo o agendamento: ");
	scanf(" %[^\n]s", nomePaciente);

	codigoPaciente = strtol(nomePaciente, NULL, 10); //Faz a conversão de alfabetico para inteiro

	for (i = 0; i < contPaciente; i++)
	{
		if (codigoPaciente == paciente[i].codigo || strcmp(paciente[i].nome, nomePaciente) == 0)
		{
			agendamento[*contAgendamento].pacienteQuePediu = paciente[i];
			marcador = 1;
			break;
		}
	}
	if (!marcador && strlen(nomePaciente) != 0)
	{
		printf("\n		!!ERRO\n	PACIENTE NAO ENCONTRADO\n");
		system("pause");
		system("cls");
		menu();
		return;
	}

	marcador = 0;
	printf("Digite o codigo da unidade para agendamento: ");
	scanf(" %d", &unidadeParaCadastro);
	for (i = 0; i < contUnidade; i++)
	{
		if (unidadeParaCadastro == unidade[i].codigo)
		{
			agendamento[*contAgendamento].UnidadeParaAgendar = unidade[i];
			marcador = 1;
			break;
		}
	}
	if (!marcador )
	{
		printf("\n		!!ERRO\n	UNIDADE NAO ENCONTRADA\n");
		system("pause");
		system("cls");
		menu();
		return;
	}

	printf("Digite a quantidade de exames que deseja agendar: ");
	scanf(" %d", &agendamento[*contAgendamento].qtd);

	agendamento[*contAgendamento].examePedido = malloc(agendamento[*contAgendamento].qtd * sizeof(Agd));

	do
	{
		marcador = 0;
		for (i = auxIndice; i < agendamento[*contAgendamento].qtd; i++)
		{
			printf("Digite o codigo do exame para agendar: ");
			scanf(" %d", &codigoExameParaCadastro);
			for (j = 0; j < contExame; j++)
			{
				if (exame[j].codigo == codigoExameParaCadastro && unidade[j].codigo == codigoExameParaCadastro)
				{
					agendamento[*contAgendamento].examePedido[i] = exame[j];
					marcador = 1;
					opcao = "";
					break;
				}
			}
			if (!marcador)
			{
				printf("\n		!!ERRO\n	EXAME NAO ENCONTRADO\n");
				printf("O agendamento será descartado; ou deseja novamente outro codigo de exame [S/N]:  ");
				scanf(" %c", &opcao);
				auxIndice = i;
				system("cls");
				break;
			}
		}
	} while (opcao == 'S' || opcao == 's');

	if (opcao == 'N' || opcao == 'n')
	{
		printf("AGENDAMENTO NAO CADASTRADO\n");
		system("pause");
	}
	else
	{
		obterData(&agendamento[*contAgendamento]);
		*contAgendamento += 1;
		if (*contAgendamento == 10)
			agendamento = realloc(agendamento, (*contAgendamento + 1) * sizeof(Agd));

		printf("\n		AGENDAMENTO CADASTRADO SUCESSO\n");
		system("pause");
	}

	system("cls");
	menu();
}

void obterData(Agd* agendamento) {
	time_t t = time(NULL);

	struct tm data = *localtime(&t);

	agendamento->ano = data.tm_year + 1900;
	agendamento->mes = data.tm_mon + 1;
	agendamento->dia = data.tm_mday;
}

void listarAgendamentoDeUmPaciente(Agd* agendamento, int contAgendamento) {
	char nomePaciente[50];
	int codigoPaciente;
	int i, marcador = 0;

	printf("Digite o codigo ou nome do paciente para visualizar seus agendamentos: ");
	scanf(" %[^\n]s", nomePaciente);
	system("cls");

	codigoPaciente = strtol(nomePaciente, NULL, 10); //Faz a conversão de alfabetico para alfabetico
	for (i = 0; i < contAgendamento; i++)
	{
		if (agendamento[i].pacienteQuePediu.codigo == codigoPaciente || strcmp(agendamento[i].pacienteQuePediu.nome, nomePaciente) == 0)
		{
			imprimirAgendamento(agendamento[i]);
			marcador = 1;
			break;
		}
	}
	if (!marcador)
	{
		printf("		\n!!ERRO\n	NEM UM AGENDAMENTO CADASTRADO PARA ESSE PACIENTE\n");
		system("pause");
	}
	system("cls");
	menu();
}

void imprimirAgendamento(Agd agendamento) {
	int i;

	printf("\nNome do paciente: %s\nPEDIDOS", agendamento.pacienteQuePediu.nome);
	for (i = 0; i < agendamento.qtd; i++)
	{
		printf("\nExame: %s\n", agendamento.examePedido[i].nome);
		printf("Data: %d/%d/%d", agendamento.dia, agendamento.mes, agendamento.ano);
		printf("\nHospital: %s", agendamento.UnidadeParaAgendar.nome);
	}
	printf("\n===============================\n");
	system("pause");
}

void ListarAgendamentoDeUmDia(Agd* agendamento, int contAgendamento) {
	int i, dia, mes, ano, marcador = 0;
	char d[3];
	char m[3];
	char a[5];

	printf("Para visualizar todos os pedidos de um determinado dia entre com a data OBS:(apenas numeros) \n");
	printf("Dia: ");
	scanf(" %s", d);
	printf("Mes: ");
	scanf(" %s", m);
	printf("Ano: ");
	scanf(" %s", a);

	system("cls");

	dia = strtol(d, NULL, 10); //Faz a conversão de alfabetico para inteiro
	mes = strtol(m, NULL, 10); //Faz a conversão de alfabetico para inteiro
	ano = strtol(a, NULL, 10); //Faz a conversão de alfabetico para inteiro

	for (i = 0; i < contAgendamento; i++)
	{
		if (agendamento[i].ano == ano && agendamento[i].mes == mes && agendamento[i].dia == dia)
		{
			imprimirAgendamento(agendamento[i]);
			marcador = 1;
		}
	}
	if (!marcador)
	{
		printf("\n		!!NEM UM PEDIDO CADASTRO NESSE DIA!!\n");
		system("cls");
	}
	system("cls");
	menu();
}