#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <locale.h>


typedef struct cadastroItem {
	
	int codigo;
	int quantidade;
	double precoUnitario;
	
	int dias;
	int mes;
	int ano;
}cadItem, *pCadItem, **ppCadItem;




ppCadItem cadastrar_vendas(int tamanho, ppCadItem vendas, int dia, int mes, int ano){
	
	if(vendas == 0){
	vendas = (ppCadItem) malloc (sizeof(pCadItem));
	}
	else{
		vendas = (ppCadItem) realloc(vendas, (tamanho+1) * sizeof (pCadItem));
	}
	
	vendas[tamanho] = malloc(sizeof (cadItem));
	
	vendas[tamanho]->dias = dia;
	vendas[tamanho]->mes = mes;
	vendas[tamanho]->ano = ano;
	
	printf("Digite o codigo do produto: ");
	scanf("%d", &vendas[tamanho]->codigo);
	    while (getchar() != '\n');
	printf("Digite a quantidade do produto: ");
	scanf("%d", &vendas[tamanho]->quantidade);
	    while (getchar() != '\n');
	printf("Digite o preco do produto: ");
	scanf("%lf", &vendas[tamanho]->precoUnitario);
	    while (getchar() != '\n');
	
	return vendas;
	}
	
	
faturamento_bruto (int tamanho, ppCadItem vendas, double faturamento){
	int i;
	
	for(i = 0; i < tamanho; i++){
	faturamento += vendas[i]->precoUnitario;
	}
	
	return faturamento;
}
	
	

void imprimir_vendas(int tamanho ,ppCadItem vendas){
	int i = 0;
	int j = 0;
	
	pCadItem temp;
	for(i; i < tamanho ; i++){
		for (j = i + 1; j < tamanho; j++) {
		 if (vendas[i]->precoUnitario < vendas[j]->precoUnitario){
		 	temp = vendas[i];
		 	vendas[i] = vendas[j];
		 	vendas[j] = temp;
		 	
		 }
		 
	}
		printf("Data da Venda: %d/%d/%d\n", vendas[i]->dias, vendas[i]->mes, vendas[i]->ano );
		printf("Codigo do produto: %d \n",vendas[i]->codigo );
		printf("Quantidade do produto: %d \n",vendas[i]->quantidade );
		printf("Preco do produto: R$%.2lf \n", vendas[i]->precoUnitario );
		printf("=====================================\n");
}
	
}

int contar_vendas_por_data(int tamanho, ppCadItem vendas, int dia_busca, int mes_busca, int ano_busca) {
    int contador = 0;
    int i;
    for (i = 0; i < tamanho; i++) {
        if (vendas[i]->dias == dia_busca && vendas[i]->mes == mes_busca && vendas[i]->ano == ano_busca) {
            contador++;
        }
    }
    return contador;
}




int main (){
	setlocale(LC_ALL, "pt_BR.UTF-8");
	ppCadItem vet = NULL;
	int opcao;
	int sim = 1;
	int tamanho = 0;
	double faturamento;
	int totalVendas;
	int dia;
	int mes;
	int ano;
	
	do{
	system("cls");
	printf("Escolha uma opcao abaixo:\n");
	
	printf("1: Cadastrar venda\n");
	printf("2: Listar vendas do dia em ordem decrescente de valor (informar data)\n");
	printf("3: Faturamento bruto diario (informar data)\n");
	printf("4: Quantidade de clientes que realizaram compras (informar data)\n");
	printf("5: Item mais vendido (informar data)\n");
	printf("6: Item menos vendido (informar data)\n");
	printf("7: Sair\n");
	
	
	opcao = getch();
	
	
	system("cls");
	switch(opcao){
	
	case '1':
		
		printf("Informe a data do dia de trabalho (DD MM AAAA): ");
		scanf("%d %d %d", &dia, &mes, &ano);
		    while (getchar() != '\n');
			
		while(sim == 1){
			vet = cadastrar_vendas(tamanho, vet, dia, mes, ano);
			tamanho++;
			printf("\nDeseja cadastrar nova venda? (s = 1 /n = 0) -> ");
			scanf("%d", &sim);
			    while (getchar() != '\n');
			printf("\n");
		}
		sim = 1;
		break;
		
	case '2':
		imprimir_vendas(tamanho, vet);
		getch();
		break;
	
	case '3':
		faturamento = faturamento_bruto ( tamanho, vet, faturamento);
		printf("Faturamento Bruto do dia: R$%.2lf", faturamento);
		getch();
		break;
	
	case '4':
		printf("Informe a data para verificar as vendas (DD MM AAAA): ");
		scanf("%d %d %d", &dia, &mes, &ano);
		totalVendas = contar_vendas_por_data(tamanho, vet, dia, mes, ano);
		printf("Total de vendas na data %d/%d/%d: %d\n", dia, mes, ano, totalVendas);
		getch();
		break;
		
	case '5':
		printf("5\n");
		getch();
		break;
		
	case '6':
		printf("6\n");
		getch();
		break;
	
	case '7':
		printf("Saindo...\n");
		sleep(1);
		break;
		
	default:
		printf("Opcao invalida\n");
		getch();
		break;
	}
		
		
	}while(opcao != '7');


}
