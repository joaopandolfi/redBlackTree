#include "arvore.h"

#define FILE_TREE "data/tree.dat"

//cria arquivo
void createFile();
//Recupera no na posicao informada
Arvore* recuperaPosicao(long int pos);
//Adiciona o novo no
Arvore* salvaNo(Arvore* no);
//Atualiza dados de um no
void update(Arvore* no);
