
// ================= Constants ===================
#define DIVIDER 110127
#define RED 'v'
#define BLACK 'p'
#define VAZIO -2
#define RAIZ -1
#define HASH_SEED 3
#define MAX_LENGHT_WORD 200
#define TRUE 1
#define FALSE 0

//Estruturas
typedef struct arvore Arvore;
typedef struct buscaRetorno BuscaRetorno;

// =============== Controle da arvore =============
Arvore* novoNo(char* data);
Arvore* adiciona(Arvore* raiz, Arvore* filho);
BuscaRetorno* busca(Arvore* raiz,char data[]);

//Inicializa a arvore
Arvore* initializeTree();

//apaga o aquivo da arvore antiga
void resetActualTree();

// ================= Controle da busca ===============
short int encontrouNaBusca(BuscaRetorno* r);
long int profDaBusca(BuscaRetorno* r);
char* dadoDaBusca(BuscaRetorno* r);

// ======== Externalizacao dos dados da estrutura =====
Arvore* setPosition(Arvore* no, long int pos);
long int getDesloc(Arvore* no);


// ================ funcoes internas ==================
Arvore* getNextNode(long int desloc);
void atualizaNo(Arvore* no);
long int salvaFilho(Arvore* filho);
void salvaRaiz(Arvore* raiz);
void adicionaIntenal(Arvore* raiz,Arvore* pai, Arvore* filho);

// ==================== Rotacao ======================
Arvore* rotacaoDireita(Arvore* raiz, Arvore* filho);
Arvore* rotacaoEsquerda(Arvore* raiz, Arvore* filho);
