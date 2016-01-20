#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Headers/arvore.h"

int main(int argc, char *argv[]){
	//Estruturas
	BuscaRetorno* r;
	Arvore* raiz;
	
	//Inicializacao da arvore
	resetActualTree();
	raiz = initializeTree();

	
	//Parametros
	char* nameEntrada = argv[1];
	char* nameBusca = argv[2];
	char* nameSaida = argv[3];

	//Arquivo
	FILE *arq;
	FILE *write;
 	char info[MAX_LENGHT_WORD];


// ==================== INSERINDO =========================
 
 	printf("Inserindo na arvore\n");
 	
	fopen_s(&arq,nameEntrada,"r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fgets(info, sizeof(info), arq))!=NULL )
			raiz = adiciona(raiz,novoNo(info));
	
	fclose(arq);
	//raiz = adiciona(raiz,novoNo("1"));
	
// ==================== BUSCANDO =========================
	
	printf("\nBUSCANDO\n");
	fopen_s(&arq,nameBusca,"r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo de leitura\n");
	else{
		fopen_s(&write,nameSaida,"w");
		if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo de escrita\n");
		else
			while( (fgets(info, sizeof(info), arq))!=NULL ){
				r = busca(raiz,info);
				info[strlen(info)-1] = '\0'; 
				if(encontrouNaBusca(r))
					fprintf(write,"%s presente %d\n",info,profDaBusca(r));
				else
					fprintf(write,"%s ausente %d\n",info,profDaBusca(r));
			}
	}
	fclose(arq);
	fclose(write);
}
