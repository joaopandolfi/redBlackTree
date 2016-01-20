#include <stdlib.h>
#include <string.h>
#include "../Headers/arvore.h"
#include "../Headers/fileControl.h"

// ============= ESTRUTURA ==============

//Estrutura da arvore
typedef struct arvore {
	char data[MAX_LENGHT_WORD];
	char cor;
	unsigned long int hash;
	long int pai;
	long int pos;
	long int direita;
	long int esquerda;
} Arvore;

//Estrutura para retorno da busca
typedef struct buscaRetorno{
	char data[MAX_LENGHT_WORD];
	short int encontrou;
	long int prof;
} BuscaRetorno;

// ============ CONTROLE DO NO ==========

//Calcula hash
unsigned long int hash(char* key){
  int tam, inverso;
  //tam = strlen(key);
  long int hash = 0;
  inverso = MAX_LENGHT_WORD;
  tam = 0;

  while(key[tam] != '\0')
    hash += key[tam]*(1+ tam++) + (HASH_SEED*inverso--);

  hash = (hash*HASH_SEED)+(inverso-HASH_SEED);
  return hash%DIVIDER;
}

//Cria novo no
Arvore* novoNo(char* data){
	Arvore* novo = (Arvore*) malloc(sizeof(Arvore));
	strcpy_s(novo->data,strlen(data)+1,data);
	novo->cor = RED;
	novo->hash = hash(data);
	novo->pai = VAZIO;
	novo->direita = VAZIO;
	novo->esquerda = VAZIO;
	novo->pos = VAZIO;
	return novo;
}

//inicializa a arvore
Arvore* initializeTree(){
	return NULL;
}

//Deleta arquivo atual da arvore
void resetActualTree(){
	createFile();
}

//seta posicao no no
Arvore* setPosition(Arvore* no, long int pos){
	no->pos = pos;
	return no;
}

//retorna o deslocamento
long int getDesloc(Arvore* no){
	return no->pos;
}

// =============== CONTROLE DO NO DE BUSCA================

//Nova estrutura a ser retornada
BuscaRetorno* novoRetorno(short int encontrou, int profundidade, char* data){
	BuscaRetorno* r = (BuscaRetorno*) malloc(sizeof(BuscaRetorno));
	r->encontrou = encontrou;
	r->prof = profundidade;
	strcpy_s(r->data,MAX_LENGHT_WORD,data);
	return r;
}

//verifica se o elemento foi encontrado
short int encontrouNaBusca(BuscaRetorno* r){
	return r->encontrou;
}

//retorna profundidade da busca
long int profDaBusca(BuscaRetorno* r){
	return r->prof;
}

//Retorna o dado da busca
char* dadoDaBusca(BuscaRetorno* r){
	return r->data;
}

// ================= CONTROLE DA ARVORE ==================

// Corrige e balanceia a arvore
Arvore* balanceia(Arvore * raiz, Arvore * z) {
    Arvore* pai = getNextNode(z->pai);
    Arvore* avo = getNextNode(pai->pai);

    while (z->pos != raiz->pos &&  pai->cor == RED) {
        if (pai->pos == avo->esquerda) {
            Arvore * tio = getNextNode(avo->direita);
            if (tio->cor == RED) { //CASO 1
                pai->cor = BLACK;
                tio->cor = BLACK;
                avo->cor = RED;
                z = avo;
                atualizaNo(pai);
                atualizaNo(tio);
                atualizaNo(avo);
            } else {
                if (z->pos == pai->direita) { //CASO 2
                    z = pai;
                   raiz = rotacaoEsquerda(raiz, z);
                }
                //CASO 3
                pai->cor = BLACK;
                avo->cor = RED;
                atualizaNo(pai);
                atualizaNo(avo);
                raiz = rotacaoDireita(raiz, avo);
            }
        } else { //PARA DIREITA
                        	
            if (pai->pos == avo->direita) {
                Arvore * tio = getNextNode(avo->esquerda);
                if (tio->cor == RED) {
                    pai->cor = BLACK;
                    tio->cor = BLACK;
                    avo->cor = RED;
                    z = avo;
                    atualizaNo(pai);
                    atualizaNo(tio);
                    atualizaNo(avo);
                } else {   	
                    if (z->pos == pai->esquerda) {
                        z = pai;
                        raiz = rotacaoDireita(raiz, z); // OLHAR
                    }
                    pai->cor = BLACK;
                    avo->cor = RED;
                    atualizaNo(pai);
                    atualizaNo(avo);                    
                    raiz = rotacaoEsquerda(raiz,avo);
                }
            }
        }
    	//reloadRaiz
        raiz = getNextNode(raiz->pos);
	    pai = getNextNode(z->pai);
		avo = getNextNode(pai->pai);
    }
    raiz->cor = BLACK;
    atualizaNo(raiz);
    return raiz;
}

//Adiciona na arvore
Arvore* adicionaInternal(Arvore* raiz,Arvore* pai, Arvore* filho){
	if(raiz){
		if(filho->hash > pai->hash){
			if(pai->direita == VAZIO){
				filho->pai = pai->pos;
				pai->direita = salvaFilho(filho);
				atualizaNo(pai);
				raiz = balanceia(raiz,filho);
			}
			else
				raiz = adicionaInternal(raiz,getNextNode(pai->direita),filho);
		}
		else{
			if(pai->esquerda ==VAZIO){
				filho->pai = pai->pos;
				pai->esquerda = salvaFilho(filho);
				atualizaNo(pai);
			 	raiz =	balanceia(raiz,filho);
			}			
			else
				raiz = adicionaInternal(raiz,getNextNode(pai->esquerda),filho);
		}
	}
	else{
		salvaRaiz(filho);
		raiz = filho;
	}
	return raiz;
}

//Busca -- MELHORAR
char* buscaInternal(Arvore* raiz, Arvore* corrente, char data[], long int hash,int count){
	count++;
	if(raiz){
		if(hash == corrente->hash){
			if(strcmp(corrente->data, data) == 0){
				//printf("COR: %c POSICAO %d PAI: %d\n",corrente->cor,corrente->pos,corrente->pai);
				return novoRetorno(TRUE,count,corrente->data);
			}else if(corrente->esquerda != VAZIO)
					return buscaInternal(raiz,getNextNode(corrente->esquerda),data,hash,count);
				else 
				return novoRetorno(FALSE,count,data);
		}else if(hash < corrente->hash)
			if(corrente->esquerda != VAZIO)
				return buscaInternal(raiz,getNextNode(corrente->esquerda),data,hash,count);
			else
				return novoRetorno(FALSE,count,data);
		else 
			if(corrente->direita != VAZIO)
				return buscaInternal(raiz,getNextNode(corrente->direita),data,hash,count);
			else
				return novoRetorno(FALSE,count,data);
	}
	else
		return novoRetorno(FALSE,count,data);
}

//busca na arvora por fora
BuscaRetorno* busca(Arvore* raiz,char data[]){
	return buscaInternal(raiz, raiz,data,hash(data),0);
}

//Adiciona na arvore de fora
Arvore* adiciona(Arvore* raiz, Arvore* filho){
	return adicionaInternal(raiz,raiz,filho);
}

// ===================== ROTACOES ==================================

//faz rotacao a esquerda na arvore
Arvore * rotacaoEsquerda(Arvore * raiz, Arvore * avo) {
    Arvore * pai = getNextNode(avo->direita);
    Arvore* aux;
    avo->direita = pai->esquerda;

    if (pai->esquerda != VAZIO) {
        aux = getNextNode(pai->esquerda);
        aux->pai = avo->pos;
        atualizaNo(aux);
    }

    pai->pai = avo->pai;
    if (avo->pai == RAIZ) {
        raiz = pai;
    } else {
        aux = getNextNode(avo->pai);
        if (avo->pos == aux->esquerda) {
            aux->esquerda = pai->pos;
        } else {
            aux->direita = pai->pos;
        }
        atualizaNo(aux);
    }
    pai->esquerda = avo->pos;
    avo->pai = pai->pos;
    atualizaNo(pai);
    atualizaNo(avo);
    return raiz;
}
 
 //Faz rotacao a direita na arvore
Arvore * rotacaoDireita(Arvore * raiz, Arvore * atual) {
	Arvore * esquerda = atual->esquerda;
    Arvore* aux;
    atual->esquerda = esquerda->direita;
    if (esquerda->direita != VAZIO) {
        aux = getNextNode(esquerda->direita);
        aux->pai = atual->pos;
        atualizaNo(aux);
    }
    esquerda->pai = atual->pai;
    if (atual->pai == RAIZ) {
        raiz = esquerda; //raiz
    } else {
        aux = getNextNode(atual->pai);
        if (atual->pos == aux->direita) {
            aux->direita = esquerda->pos;
        } else {
            aux->esquerda = esquerda->pos;
            atualizaNo(aux);
        }
    }
    esquerda->direita = atual->pos;
    atual->pai = esquerda->pos;
    atualizaNo(esquerda);
    atualizaNo(atual);
    return raiz;
}

// ============== Manipulacao de arquivo ========================

// ==== LEITURA

//recupera o no no deslocamento apontado
Arvore* getNextNode(long int desloc){
	return recuperaPosicao(desloc);
}

// ==== ESCRITA

//Atualiza dados de um no
void atualizaNo(Arvore* no){
	update(no);
//	printf("ALTERADO: key %d cor %c POS: %d PAI: %d ESQUERDA: %d DIREITA: %d \n",no->hash,no->cor,no->pos,no->pai,no->esquerda,no->direita);
}

//salva filho no hd
long int salvaFilho(Arvore* filho){
	Arvore* novo = salvaNo(filho);
//	printf("ADICIONADO: Data: %s key %d cor %c POS: %d PAI: %d ESQUERDA: %d DIREITA: %d \n",filho->data,filho->hash,filho->cor,filho->pos,filho->pai,filho->esquerda,filho->direita);
	return novo->pos;
}

//salva raiz no hd
void salvaRaiz(Arvore* raiz){
	raiz->cor = BLACK; // raiz e sempre preta
	raiz->pai = RAIZ;
	//salva
	salvaNo(raiz);
//	printf("ADICIONADO RAIZ: key %d cor %c POS: %d PAI: %d ESQUERDA: %d DIREITA: %d \n",raiz->hash,raiz->cor,raiz->pos,raiz->pai,raiz->esquerda,raiz->direita);
}

//salva a raiz em um arquivo separado
void gravaRaiz(Arvore* raiz){
	
}

//recupera raiz do arquivo separado
Arvore* recuperaRaiz(){
	
}
