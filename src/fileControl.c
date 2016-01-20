#include <stdio.h>
#include <stdlib.h>
#include "../Headers/fileControl.h"
#include "../Headers/arvore.h"

//Estrutura da arvore
struct arvore {
	char data[MAX_LENGHT_WORD];
	char cor;
	unsigned long int hash;
	long int pai;
	long int pos;
	long int direita;
	long int esquerda;
};

//Apaga arvore anterior
void createFile(){
	FILE* f;
	f = fopen(FILE_TREE,"w");
	fclose(f);
}

//Recupera no na posicao informada
Arvore* recuperaPosicao(long int pos){
	FILE* f;
	Arvore* no = (Arvore*)malloc(sizeof(Arvore));
	f = fopen(FILE_TREE,"r+b");
	fseek(f,pos*sizeof(Arvore),SEEK_SET);
	fread(no,sizeof(Arvore),1,f);
	fclose(f);
	return no;
}

//Adiciona o novo no
Arvore* salvaNo(Arvore* no){
	FILE* f;
	f = fopen(FILE_TREE,"r+b");
	fseek(f,0,SEEK_END);
	no = setPosition(no,(ftell(f)/sizeof(Arvore)));
	fwrite(no,sizeof(Arvore),1,f);
	fclose(f);
	return no;
}

//Atualiza dados de um no
void update(Arvore* no){
	FILE* f;
	f = fopen(FILE_TREE,"r+b");
	fseek(f,(getDesloc(no)*sizeof(Arvore)),SEEK_SET);
	fwrite(no,sizeof(Arvore),1,f);
	fclose(f);
}
