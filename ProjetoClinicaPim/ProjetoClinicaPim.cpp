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
	End endereco;

}Pct;
Pct aux;

//Estrutura da tabela Exames
typedef struct {
	int codigo;
	char nome[50];
	char nomeMedico[50];
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
	int diaMarcado;
	int mesMarcado;
	int anoMarcado;
	int qtd;
	Pct pacienteQuePediu;
	Exm examePedido;
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
Pct cadastrarPaciente(Pct*, int*, int);
void listarPaciente(Pct*, int);
void buscarPaciente(Pct*, int);
void AtualizarPaciente(Pct*, int, int);
void imprimirPaciente(Pct);

//Declaração da função que gerencia os Exame
void gerenciaDeExame(Exm*, int*, FILE*);
Exm cadastrarExame(Exm*, int*, int);
void listarExame(Exm*, int);
void buscarExame(Exm*, int);
void AtualizarExame(Exm*, int, int);
void imprimirExame(Exm);

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
	Exm* exame; //Declarando um ponteiro para estrutura exame
	Agd* agendamento; //Declarando um ponteiro para estrutura agendamento
	Uni* unidade; //Declarando um ponteiro para estrutura de uniadades hospitalares
	User* usuario; //Declarando um ponteiro para estrutura agendamento

	int contPaciente = 3, contExame = 3, contAgendamento = 1, contUnidade = 2; //Inicilizando os contadores
	arquivo = calloc(100, sizeof(FILE));
	paciente = calloc(100, sizeof(Pct));
	exame = calloc(100, sizeof(Exm));;
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
		strcpy(exame[i].nomeMedico, "");
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

	strcpy(usuario[3].usuario, "julia");
	strcpy(usuario[3].senha, "123");
	strcpy(usuario[3].unidade, "2");


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
	strcpy(exame[0].nomeMedico, "Rodolfo");
	strcpy(exame[0].nome, "Urologista");
	exame[0].valor = 500.0;

	//Inclui dados do Exame 2
	exame[1].codigo = 2;
	strcpy(exame[1].nomeMedico, "Marcelo");
	strcpy(exame[1].nome, "Pediatra");
	exame[1].valor = 300.0;

	//Inclui dados do Clinica 1
	unidade[0].codigo = 1;
	strcpy(unidade[0].nome, "Hospital LeForte");
	//Inclui dados do Clinica 2
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
	printf("	3 - Gerencia de Agendamentos\n");
	printf("	0 - Sair\n");
	printf("Digite um comando para prosseguir: ");
	scanf(" %d", &op);
	system("cls");
}



// Codigo da função que gerencia os pacientes
void gerenciaDePaciente(Pct* paciente, int* contPaciente, FILE* arquivo) {
	int opcao;
	int identificador = 0;
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
			cadastrarPaciente(paciente, *contPaciente, identificador);
			*contPaciente += 1;
			break;
		case 2:
			listarPaciente(paciente, *contPaciente);
			break;
		case 3:
			buscarPaciente(paciente, *contPaciente);
			break;
		case 4:
			AtualizarPaciente(paciente, *contPaciente, identificador);
			break;
		default:
			printf("		!!OPCAO INVALIDA\n	Digite novamente outra opcao\n");
			system("pause");
			system("cls");
		}
		break;
	} while (1);
}

//Função que cadastra paciente
Pct cadastrarPaciente(Pct* paciente, int* contPaciente, int identificador) {
	char aux[50];
	printf("\n____________________________________________\n");
	printf("|         Cadastro de Pacientes	           |");
	printf("\n|__________________________________________|\n");

	for (int i = 0; i < contPaciente; i++)
	{
		if (paciente[i].codigo == 0)
		{
			printf("\n	Proximo Codigo de Paciente eh : %d\n", i + 1);
			paciente[i].codigo = i + 1;
			printf("	Digite o nome do Paciente: ");
			scanf(" %[^\n]s", &aux);
			strcpy(paciente[i].nome, aux);
			printf("	Sexo [M/F]:  ");
			scanf(" %[^\n]s", &aux);
			strcpy(paciente[i].sexo, aux);

			do
			{
				printf("	Rg: ");
				scanf(" %10s", aux);

				paciente[i].rg = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
				if (identificador == 0)
				{
					if (paciente[i].rg == 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
						system("pause");
						system("cls");
						printf("\n____________________________________________\n");
						printf("|         Cadastro de Pacientes	           |");
						printf("\n|__________________________________________|\n");
						continue;
					}
				}
				else
				{
					if (paciente[i].rg == 0 && strlen(aux) > 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
						printf("\n____________________________________________\n");
						printf("|         Cadastro de Pacientes	           |");
						printf("\n|__________________________________________|\n");
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
				scanf(" %10s", aux);

				paciente[i].telefone = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
				if (identificador == 0)
				{
					if (paciente[i].telefone == 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
						system("pause");
						system("cls");
						printf("\n____________________________________________\n");
						printf("|         Cadastro de Pacientes	           |");
						printf("\n|__________________________________________|\n");
						continue;
					}
				}
				else
				{
					if (paciente[i].telefone == 0 && strlen(aux) > 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
						printf("\n____________________________________________\n");
						printf("|         Cadastro de Pacientes	           |");
						printf("\n|__________________________________________|\n");
						system("pause");
						system("cls");
						continue;
					}
				}
				break;
			} while (1);

			printf("	Logradouro: ");
			scanf(" %[^\n]s", &aux);
			strcpy(paciente[i].endereco.logradouro, aux);
			printf("	Complemento: ");
			scanf(" %[^\n]s", &aux);
			strcpy(paciente[i].endereco.complemento, aux);

			do
			{
				printf("	CEP :");
				scanf(" %10s", aux);

				paciente[i].endereco.cep = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
				if (identificador == 0)
				{
					if (paciente[i].endereco.cep == 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
						system("pause");
						system("cls");
						printf("\n____________________________________________\n");
						printf("|         Cadastro de Pacientes	           |");
						printf("\n|__________________________________________|\n");
						continue;
					}
				}
				else
				{
					if (paciente[i].endereco.cep == 0 && strlen(aux) > 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
						printf("\n____________________________________________\n");
						printf("|         Cadastro de Pacientes	           |");
						printf("\n|__________________________________________|\n");
						system("pause");
						system("cls");
						continue;
					}
				}
				break;
			} while (1);
			printf("	Bairro: ");
			scanf(" %[^\n]s", &aux);
			strcpy(paciente[i].endereco.bairro, aux);
			printf("	Cidade: ");
			scanf(" %[^\n]s", &aux);
			strcpy(paciente[i].endereco.cidade, aux);

			printf("	Cadastro Realizado com sucesso\n");
			system("pause");
			system("cls");
		}
	}
	return;
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
	printf("\n	LISTA DE PACIENTES CADASTRADOS\n\n");
	for (i = 0; i < contPaciente; i++) {
		if (paciente[i].codigo != 0)
		{
			imprimirPaciente(paciente[i]);
		}
	}
	system("pause");
	system("cls");
}

void imprimirPaciente(Pct paciente) {
	printf("\n	Codigo: %d\n", paciente.codigo);
	printf("	Nome: %s\n", paciente.nome);
	printf("	Sexo: %s\n", paciente.sexo);
	printf("	RG: %.0f\n", paciente.rg);
	printf("	Telefone: %.0f\n", paciente.telefone);
	printf("	Endereco: %s / Complemento %s\n", paciente.endereco.logradouro, paciente.endereco.complemento);
	printf("	CEP:  %.0f\n", paciente.endereco.cep);
	printf("	Bairro: %s\n", paciente.endereco.bairro);
	printf("	Cidade: %s\n", paciente.endereco.cidade);

}

void buscarPaciente(Pct* paciente, int contPaciente) {
	printf("\n____________________________________________\n");
	printf("|         busca de Pacientes	           |");
	printf("\n|__________________________________________|\n");
	int i, marcador = 0;
	int rgPaciente;
	char nomePaciente[50];

	printf("	Digite o nome ou o rg do paciente que deseja buscar: ");
	scanf(" %[^\n]s", nomePaciente);
	printf("\n");
	rgPaciente = strtol(nomePaciente, NULL, 10);

	for (i = 0; i < contPaciente; i++)
	{
		if (paciente[i].rg == rgPaciente || strcmp(paciente[i].nome, nomePaciente) == 0)
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

void AtualizarPaciente(Pct* paciente, int contPaciente, int identificador) {
	int codigo, i,codigoPaciente, marcador = 0;
	char aux[50];
	char rgPaciente[10];

	do
	{
		printf("RG do paciente que deseja atualizar: ");
		scanf(" %s", rgPaciente);

		codigo = strtol(rgPaciente, NULL, 10);
		if (codigo == 0)
		{
			printf("\n		!!ERRO!!\n	Apenas numeros para o codigo\n");
			system("pause");
			system("cls");
			continue;
		}break;

	} while (1);
	for (i = 0; i < contPaciente; i++)
	{
		if (paciente[i].rg == codigo)
		{
			codigoPaciente = paciente[i].codigo;
			marcador = 1;
			break;
		}
	}
	if (!marcador)
		printf("\n		!!ERRO!!\n	PACIENTE NAO CADASTRADO\n");
	else
	{
		printf("\n	ENTRE COM OS DADOS ATUALIZADOS\n");
		printf("	Digite o nome do Paciente: ");
		scanf(" %[^\n]s", &aux);
		strcpy(paciente[codigoPaciente - 1].nome, aux);
		printf("	Sexo [M/F]:  ");
		scanf(" %[^\n]s", &aux);
		strcpy(paciente[codigoPaciente - 1].sexo, aux);

		do
		{
			printf("	Rg: ");
			scanf(" %10s", aux);

			paciente[codigoPaciente - 1].rg = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
			if (identificador == 0)
			{
				if (paciente[codigoPaciente - 1].rg == 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
					system("pause");
					system("cls");
					printf("\n____________________________________________\n");
					printf("|         Cadastro de Pacientes	           |");
					printf("\n|__________________________________________|\n");
					continue;
				}
			}
			else
			{
				if (paciente[codigoPaciente - 1].rg == 0 && strlen(aux) > 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
					printf("\n____________________________________________\n");
					printf("|         Cadastro de Pacientes	           |");
					printf("\n|__________________________________________|\n");
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
			scanf(" %10s", aux);

			paciente[codigoPaciente - 1].telefone = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
			if (identificador == 0)
			{
				if (paciente[codigoPaciente - 1].telefone == 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
					system("pause");
					system("cls");
					printf("\n____________________________________________\n");
					printf("|         Cadastro de Pacientes	           |");
					printf("\n|__________________________________________|\n");
					continue;
				}
			}
			else
			{
				if (paciente[codigoPaciente - 1].telefone == 0 && strlen(aux) > 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
					printf("\n____________________________________________\n");
					printf("|         Cadastro de Pacientes	           |");
					printf("\n|__________________________________________|\n");
					system("pause");
					system("cls");
					continue;
				}
			}
			break;
		} while (1);

		printf("	Logradouro: ");
		scanf(" %[^\n]s", &aux);
		strcpy(paciente[codigoPaciente - 1].endereco.logradouro, aux);
		printf("	Complemento: ");
		scanf(" %[^\n]s", &aux);
		strcpy(paciente[codigoPaciente - 1].endereco.complemento, aux);

		do
		{
			printf("	CEP :");
			scanf(" %10s", aux);

			paciente[codigoPaciente - 1].endereco.cep = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
			if (identificador == 0)
			{
				if (paciente[codigoPaciente - 1].endereco.cep == 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
					system("pause");
					system("cls");
					printf("\n____________________________________________\n");
					printf("|         Cadastro de Pacientes	           |");
					printf("\n|__________________________________________|\n");
					continue;
				}
			}
			else
			{
				if (paciente[codigoPaciente - 1].endereco.cep == 0 && strlen(aux) > 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o codigo\n");
					printf("\n____________________________________________\n");
					printf("|         Cadastro de Pacientes	           |");
					printf("\n|__________________________________________|\n");
					system("pause");
					system("cls");
					continue;
				}
			}
			break;
		} while (1);

		printf("	Bairro: ");
		scanf(" %[^\n]s", &aux);
		strcpy(paciente[codigoPaciente - 1].endereco.bairro, aux);
		printf("	Cidade: ");
		scanf(" %[^\n]s", &aux);
		strcpy(paciente[codigoPaciente - 1].endereco.cidade, aux);

		printf("\n	PACIENTE ATUALIZADO COM SUCESSO\n");
	}
	system("pause");
	system("cls");
}

// Codigo da função que gerencia os exames
void gerenciaDeExame(Exm* exame, int* contExame, FILE* arquivo) {
	int opcao;
	int i = 0;
	int identificador = 0;

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
			cadastrarExame(exame, *contExame, identificador);
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
			AtualizarExame(exame, *contExame, identificador);
			break;
			fclose(arquivo);
			break;
		default:
			printf("		!!OPCAO INVALIDA\n	Digite novamente outra opcao\n");
			system("pause");
			system("cls");
		}
		break;
	} while (1);
}

//Função que cadastra exame
Exm cadastrarExame(Exm* exame, int* contExame, int identificador) {
	char aux[50];
	printf("\n____________________________________________\n");
	printf("|         Cadastro de Exames	           |");
	printf("\n|__________________________________________|\n");

	for (int i = 0; i < contExame; i++)
	{
		if (exame[i].codigo == 0)
		{
			printf("\n	Proximo Codigo de Exame eh : %d\n", i + 1);
			exame[i].codigo = i + 1;
			printf("	Digite o nome do exame: ");
			scanf(" %[^\n]s", &aux);
			strcpy(exame[i].nome, aux);
			printf("	Digite o nome do Medico: ");
			scanf(" %[^\n]s", &aux);
			strcpy(exame[i].nomeMedico, aux);
			do
			{
				printf("	Valor do exame:R$ ");
				scanf("%10s", aux);
				exame[i].valor = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
				if (identificador == 0)
				{
					if (exame[i].valor == 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o valor\n");
						system("pause");
						system("cls");
						printf("\n	======= Cadastro de Exames =======\n");
						continue;
					}
				}
				else
				{
					if (exame[i].valor == 0 && strlen(aux) > 0)
					{
						printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o valor\n");
						system("pause");
						system("cls");
						continue;
					}
				}
				break;
			} while (1);
			printf("	Cadastro Realizado com sucesso\n");
			system("pause");
			system("cls");
		}
	}
	return;
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
	printf("\n	LISTA DE EXAMES CADASTRADOS\n");
	for (i = 0; i < contExame; i++) {
		if (exame[i].codigo != 0)
		{
			imprimirExame(exame[i]);
		}
	}
	system("pause");
	system("cls");
}

void imprimirExame(Exm exame) {
	printf("\n	Codigo: %d\n", exame.codigo);
	printf("	Medico: %s\n", exame.nomeMedico);
	printf("	Exame: %s\n", exame.nome);
	printf("	Valor:R$ %.2f\n", exame.valor);
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
void AtualizarExame(Exm* exame, int contExame, int identificador) {
	int codigo, i, marcador = 0;
	char aux[50];
	char codigoExame[10];

	printf("\n____________________________________________\n");
	printf("|         Atualizar de Exame	           |");
	printf("\n|__________________________________________|\n");

	do
	{
		printf("\n	Codigo do exame que deseja atualizar: ");
		scanf(" %s", codigoExame);

		codigo = strtol(codigoExame, NULL, 10);
		if (codigo == 0)
		{
			printf("\n	!!ERRO!!\n	Apenas numeros para o codigo\n");
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
		printf("	Digite o nome do exame: ");
		scanf(" %[^\n]s", &aux);
		strcpy(exame[codigo - 1].nome, aux);
		printf("	Digite o nome do Medico: ");
		scanf(" %[^\n]s", &aux);
		strcpy(exame[codigo - 1].nomeMedico, aux);
		do
		{
			printf("	Valor do exame:R$ ");
			scanf("%10s", aux);
			exame[codigo - 1].valor = strtol(aux, NULL, 10); //Faz a conversão de alfabetico para inteiro
			if (identificador == 0)
			{
				if (exame[codigo - 1].valor == 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o valor\n");
					system("pause");
					system("cls");
					printf("\n	======= Cadastro de Exames =======\n");
					continue;
				}
			}
			else
			{
				if (exame[codigo - 1].valor == 0 && strlen(aux) > 0)
				{
					printf("\n		!!OPCAO INVALIDA\n	Apenas numeros para o valor\n");
					system("pause");
					system("cls");
					continue;
				}
			}
			break;
		} while (1);
		printf("\	nEXAME ATUALIZADO COM SUCESSO\n");
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
		printf("|         Gerencia de Agendamentos	         |");
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
	int codigoPaciente, unidadeParaCadastro = 0, marcador = 0;
	int codigoExameParaCadastro;
	int qtdExame;
	int i, j, dia, mes, ano, auxIndice = 0;
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
	do
	{
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
		if (!marcador)
		{
			printf("\n		!!ERRO\n	UNIDADE NAO ENCONTRADA\n");
			system("pause");
			system("cls");
			continue;
		}
		break;
	} while (1);

	printf("Digite a quantidade de exames que deseja agendar: ");
	scanf(" %d", &agendamento[*contAgendamento].qtd);

	//agendamento[*contAgendamento].examePedido = malloc(agendamento[*contAgendamento].qtd * sizeof(Agd));

	do
	{
		marcador = 0;
		for (i = auxIndice; i < agendamento[*contAgendamento].qtd; i++)
		{
			printf("Digite o codigo do exame para agendar: ");
			scanf(" %d", &codigoExameParaCadastro);
			for (j = 0; j < contExame; j++)
			{
				if (exame[j].codigo == codigoExameParaCadastro)
				{
					agendamento[*contAgendamento].examePedido = exame[j];
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
		marcador = 0;
		printf("Informe o periodo  DD/MM/YY: ");
		scanf(" %d", &dia);
		for (j = 0; j < contExame; j++)
		{

			if (codigoExameParaCadastro == exame[j].codigo)
			{
				agendamento[*contAgendamento].diaMarcado = dia;
				marcador = 1;
				break;
			}
			else
			{
				printf("\n		!!ERRO\n	Dia indispinivel\n");
				system("pause");
				system("cls");
				continue;
			}
		}

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
		printf("\nExame: %s\n", agendamento.examePedido.nome);
		printf("Data: %d/%d/%d", agendamento.dia, agendamento.mes, agendamento.ano);
		printf("Dia Marcado: %d", agendamento.diaMarcado);
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
		printf("\n		!!NEM UM AGENDAMENTO CADASTRO NESSE DIA!!\n");
		system("pause");
		system("cls");
	}
	system("cls");
	menu();
}