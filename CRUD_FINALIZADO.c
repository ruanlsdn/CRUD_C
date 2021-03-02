#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

//DECLARAÇÃO DAS STRUCTS
struct ficha_produto {
	int cod;
	float valor;
	char descricao[100];
};

struct ficha_produto_backup {
	int codBack;
	char descrBack[100];
	float valBack;
};
//================================================================================================================

//DECLARAÇÃO DAS FUNÇÕES
int leValidaCod();
float leValidaValor();
void leValidaDescr (char *descr);
int apresentaValidaMenu ();
char leValidaOpcCase();
char leValidaOpcCase2();
void listarProduto (int cont, struct ficha_produto dadosCrud[]);
void atualizarProduto (int cont, struct ficha_produto dadosCrud[]);
void backupProduto (int cont, struct ficha_produto dadosCrud[], struct ficha_produto_backup dadosBack[]);
void restoreProduto (int cont, struct ficha_produto dadosCrud[], struct ficha_produto_backup dadosBack[]);
void excluirProduto (int cont, struct ficha_produto_backup dadosBack[]);
//================================================================================================================

//FUNÇÕES DE INSERÇÃO DE DADOS
int leValidaCod() {
	int cod;
	do {
		printf ("Digite o código do produto: ");
		scanf ("%d", &cod);
		if (cod<=0||cod>100) {
			printf ("Código inválido!\n");
		}
	} while (cod<=0||cod>100);
	return cod;
}

float leValidaValor() {
	float valor;
	do {
		printf ("Digite o valor do produto: ");
		scanf ("%f", &valor);
		if (valor<=0) {
			printf ("Valor inválido!\n");
		}
	} while (valor<=0);
	return valor;
}

void leValidaDescr (char *descr) {
	do {
		printf ("Digite a descrição do produto: ");
		fflush(stdin);
		gets (descr);
		if (strcmp (descr, "")==0) {
			printf ("Descrição inválida!\n");
		}
	} while (strcmp (descr, "")==0);
}
//===========================================================================================================

//MENU
int apresentaValidaMenu () {
	int opc;
	printf ("   MENU");
	printf ("\n1 - Create\n2 - Read\n3 - Update\n4 - Delete\n5 - Backup\n6 - Restore\n0 - Finalizar\n");
	do {
		printf ("Informe a opção desejada: ");
		scanf ("%d", &opc);
		if (opc<0||opc>6) {
			printf ("Opção inválida!\n");
		}
	} while (opc<0||opc>6);
	return opc;
}
//=========================================================================================================

//FUNÇÕES DAS OPÇÕES DENTRO DO CASE
char leValidaOpcCase() {
	char opc;
	do {
		printf ("Pressione 's' para continuar ou 'm' para voltar ao menu: ");
		opc = getche();
		opc = tolower (opc);
		if (opc!='s'&&opc!='m') {
			printf ("\nOpção inválida!\n");
		}
	} while (opc!='s'&&opc!='m');
	return opc;
}

char leValidaOpcCase2() {
	char opc;
	do {
		printf ("Pressione 'm' para voltar ao menu: ");
		opc = getche();
		opc = tolower (opc);
		if (opc!='m') {
			printf ("\nOpção inválida!\n");
		}
	} while (opc!='m');
	return opc;
}
//=================================================================================================================

//FUNÇÃO PARA LISTAR UM OU TODOS OS PRODUTOS
void listarProduto (int cont, struct ficha_produto dadosCrud[]) {
	int i, cod, flag=0;
	printf ("Digite o código do produto ou digite '0' para listar todos: ");
	scanf ("%d", &cod);
	for (i=0; i<cont; i++) {
		if (cod==dadosCrud[i].cod) {
			printf ("Código: %d\nDescrição: %s\nValor: R$ %.2f\n", dadosCrud[i].cod, dadosCrud[i].descricao, dadosCrud[i].valor);
			flag=1;
		} else if (cod==0&&dadosCrud[i].cod!=0) {
			printf ("Código: %d\nDescrição: %s\nValor: R$ %.2f\n", dadosCrud[i].cod, dadosCrud[i].descricao, dadosCrud[i].valor);
			flag=1;
		}
	}
	if (flag==0) {
		printf ("Produto não encontrado!\n");
	}
}
//======================================================================================================

//FUNÇÃO PARA ATUALIZAR PRODUTO
void atualizarProduto (int cont, struct ficha_produto dadosCrud[]) {
	int i, cod, flag=0;
	printf ("Digite o código do produto que deseja atualizar: ");
	scanf ("%d", &cod);
	for (i=0; i<cont; i++) {
		if (cod==dadosCrud[i].cod) {
			printf ("Digite o novo código do produto: ");
			scanf ("%d", &dadosCrud[i].cod);
			printf ("Digite a nova descrição do produto: ");
			fflush(stdin);
			gets (dadosCrud[i].descricao);
			printf ("Digite o novo valor do produto: ");
			scanf ("%f", &dadosCrud[i].valor);
			flag=1;
		}
	}
	if (flag==0) {
		printf ("Produto não encontrado!\n");
	}
}
//=====================================================================================================

//FUNÇÃO PARA EXCLUIR PRODUTO
void excluirProduto (int cont, struct ficha_produto_backup dadosBack[]) {
	int i, cod, flag=0, j, del;
	printf ("Digite o código do produto que deseja excluir: ");
	scanf ("%d", &cod);
	for (j=0; j<cont; j++) {
		if (cod==dadosBack[j].codBack) {
			del=j;
			flag=1;
		}
	}
	if (flag==1) {
		for(i=del; i<=cont; i++) {
			dadosBack[i].codBack = dadosBack[i+1].codBack;
			strcpy (dadosBack[i].descrBack, dadosBack[i+1].descrBack);
			dadosBack[i].valBack = dadosBack[i+1].valBack;
		}
		cont--;
	}
	if (flag==1){
		printf ("Produto excluído com sucesso!\n");
	}
	if (flag==0){
		printf ("Produto não encontrado!\n");
	}
}
//======================================================================================================

//FUNÇÕES DE BACKUP E RESTORE
void backupProduto (int cont, struct ficha_produto dadosCrud[], struct ficha_produto_backup dadosBack[]) {
	int i, flag=0;
	for (i=0; i<cont; i++) {
		dadosBack[i].codBack=dadosCrud[i].cod;
		strcpy (dadosBack[i].descrBack, dadosCrud[i].descricao);
		dadosBack[i].valBack=dadosCrud[i].valor;
	}
	/*for (i=0; i<cont; i++) {
		printf ("Código: %d\nDescrição: %s\nValor: R$ %.2f\n", dadosBack[i].codBack, dadosBack[i].descrBack, dadosBack[i].valBack);
	}*/
	printf ("Backup realizado com sucesso!\n");
}

void restoreProduto (int cont, struct ficha_produto dadosCrud[], struct ficha_produto_backup dadosBack[]) {
	int i, flag=0;
	for (i=0; i<cont; i++) {
		dadosCrud[i].cod=dadosBack[i].codBack;
		strcpy (dadosCrud[i].descricao, dadosBack[i].descrBack);
		dadosCrud[i].valor=dadosBack[i].valBack;
	}
	/*for (i=0; i<cont; i++) {
		printf ("Código: %d\nDescrição: %s\nValor: R$ %.2f\n", dadosBack[i].codBack, dadosBack[i].descrBack, dadosBack[i].valBack);
	}*/
	printf ("Restore realizado com sucesso!\n");
}
//=================================================================================================================

main () {
	setlocale (LC_ALL, "");

	struct ficha_produto prod[100];
	struct ficha_produto_backup prodBack[100];

	int opcMenu, cont=0;
	char opcCase;

	do {
		system ("cls");
		opcMenu = apresentaValidaMenu();
		switch (opcMenu) {
			case 1:
				do {
					system("cls");
					printf ("CREATE\n");
					prod[cont].cod=leValidaCod();
					leValidaDescr(prod[cont].descricao);
					prod[cont].valor=leValidaValor();
					opcCase = leValidaOpcCase();
					cont++;
				} while (cont<100&&opcCase=='s');
				break;
			case 2:
				do {
					system("cls");
					printf ("READ\n");
					listarProduto (cont, prod);
					opcCase = leValidaOpcCase();
				} while (opcCase=='s');
				break;
			case 3:
				do {
					system ("cls");
					printf ("UPDATE\n");
					atualizarProduto (cont, prod);
					opcCase = leValidaOpcCase();
				} while (opcCase=='s');
				break;
			case 4:
				do {
					system ("cls");
					printf ("DELETE\n");
					excluirProduto (cont, prodBack);
					opcCase = leValidaOpcCase();
				} while (opcCase=='s');
				break;
			case 5:
				system ("cls");
				printf ("BACKUP\n");
				backupProduto (cont, prod, prodBack);
				opcCase = leValidaOpcCase2();
				break;
			case 6:
				system ("cls");
				printf ("RESTORE\n");
				restoreProduto (cont, prod, prodBack);
				opcCase = leValidaOpcCase2();
				break;
		}
	} while (opcCase=='m'&&opcMenu!=0);
}
