
//Constants
#define DIVIDER 110127
#define RED 'v'
#define BLACK 'p'
#define VAZIO -2
#define RAIZ -1

typedef struct arvore Arvore;

//Controle da arvire
Arvore* novoNo(char* data);
Arvore* adiciona(Arvore* raiz, Arvore* filho);
Arvore* busca(Arvore* raiz,char data[]);
Arvore* initializeTree();

//Externalizacao dos dados da estrutura
Arvore* setPosition(Arvore* no, long int pos);
long int getDesloc(Arvore* no);

//funcoes internas
Arvore* getNextNode(long int desloc);
void atualizaNo(Arvore* no);
long int salvaFilho(Arvore* filho);
void salvaRaiz(Arvore* raiz);
void adicionaIntenal(Arvore* raiz,Arvore* pai, Arvore* filho);

//Rotacao
Arvore* rotacaoDireita(Arvore* raiz, Arvore* filho);
Arvore* rotacaoEsquerda(Arvore* raiz, Arvore* filho);

Arvore * left_rotate(Arvore * raiz, Arvore * avo);
Arvore * right_rotate(Arvore * raiz, Arvore * avo);
