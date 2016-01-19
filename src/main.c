#include <stdio.h>
#include <stdlib.h>
#include "../Headers/arvore.h"

int main(){
	Arvore* raiz = initializeTree();
	raiz = adiciona(raiz,novoNo("1"));
	raiz = adiciona(raiz,novoNo("2"));
	raiz = adiciona(raiz,novoNo("3"));
	raiz = adiciona(raiz,novoNo("4"));
	raiz = adiciona(raiz,novoNo("5"));
	
	busca(raiz,"3");
}
