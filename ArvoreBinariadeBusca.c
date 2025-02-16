#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"

// Implementação das funções
void inicializar(PONT* raiz) {
    *raiz = NULL;
}

// Função para criar um nó com o valor fornecido
PONT criarNo(int valor) {
    PONT novo = (PONT) malloc(sizeof(NO)); // Aloca memória para um novo nó
    if(novo) {
        novo->chave = valor;       // Define o valor do nó
        novo->contador = 1;        // Inicializa o contador como 1
        novo->esq = NULL;          // Define o ponteiro esquerdo como NULL
        novo->dir = NULL;          // Define o ponteiro direito como NULL
    }
    return novo;                   // Retorna o novo nó criado
}

// Função para buscar um nó com o valor fornecido na árvore
PONT buscar(PONT raiz, int valor) {
    if (raiz == NULL) return NULL; // Se a árvore estiver vazia, retorna NULL
    if (raiz->chave == valor) return raiz; // Se encontrou o valor, retorna o nó
    if (valor < raiz->chave) return buscar(raiz->esq, valor); // Busca na subárvore esquerda
    return buscar(raiz->dir, valor); // Busca na subárvore direita
}

// Função para inserir um valor na árvore
PONT inserir(PONT raiz, int valor) {
    if (raiz == NULL) return criarNo(valor); // Se a árvore estiver vazia, cria um novo nó
    if (valor < raiz->chave) raiz->esq = inserir(raiz->esq, valor); // Insere na subárvore esquerda
    else if (valor > raiz->chave) raiz->dir = inserir(raiz->dir, valor); // Insere na subárvore direita
    else raiz->contador++; // Se o valor já existe, incrementa o contador
    return raiz; // Retorna a raiz da árvore
}

// Função para remover uma ocorrência de um valor na árvore
PONT removerUmaOcorrencia(PONT raiz, int valor) {
    if (raiz == NULL) return raiz; // Se a árvore estiver vazia, retorna NULL
    if (valor < raiz->chave) raiz->esq = removerUmaOcorrencia(raiz->esq, valor); // Busca na subárvore esquerda
    else if (valor > raiz->chave) raiz->dir = removerUmaOcorrencia(raiz->dir, valor); // Busca na subárvore direita
    else { // Encontrou o nó com a chave
        if (raiz->contador > 1) {
            raiz->contador--; // Decrementa o contador
        } else { // Se for a última ocorrência
            if (raiz->esq == NULL) {
                PONT temp = raiz->dir; // Guarda a subárvore direita
                free(raiz); // Libera o nó
                return temp; // Retorna a subárvore direita
            } else if (raiz->dir == NULL) {
                PONT temp = raiz->esq; // Guarda a subárvore esquerda
                free(raiz); // Libera o nó
                return temp; // Retorna a subárvore esquerda
            }
            // Nó com dois filhos: obtém o sucessor em ordem (menor na subárvore direita)
            PONT temp = raiz->dir;
            while (temp && temp->esq != NULL) temp = temp->esq;
            raiz->chave = temp->chave;
            raiz->contador = temp->contador;
            raiz->dir = removerUmaOcorrencia(raiz->dir, temp->chave);
        }
    }
    return raiz; // Retorna a raiz da árvore
}

// Função para remover todas as ocorrências de um valor na árvore
PONT removerTodasOcorrencias(PONT raiz, int valor) {
    if (raiz == NULL) return raiz; // Se a árvore estiver vazia, retorna NULL
    if (valor < raiz->chave) raiz->esq = removerTodasOcorrencias(raiz->esq, valor); // Busca na subárvore esquerda
    else if (valor > raiz->chave) raiz->dir = removerTodasOcorrencias(raiz->dir, valor); // Busca na subárvore direita
    else { // Encontrou o nó com a chave
        if (raiz->esq == NULL) {
            PONT temp = raiz->dir; // Guarda a subárvore direita
            free(raiz); // Libera o nó
            return temp; // Retorna a subárvore direita
        } else if (raiz->dir == NULL) {
            PONT temp = raiz->esq; // Guarda a subárvore esquerda
            free(raiz); // Libera o nó
            return temp; // Retorna a subárvore esquerda
        }
        // Nó com dois filhos: obtém o sucessor em ordem (menor na subárvore direita)
        PONT temp = raiz->dir;
        while (temp && temp->esq != NULL) temp = temp->esq;
        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        raiz->dir = removerTodasOcorrencias(raiz->dir, temp->chave);
    }
    return raiz; // Retorna a raiz da árvore
}

// Função para exibir os elementos da árvore em ordem
void exibirInOrder(PONT raiz) {
    if (raiz != NULL) {
        exibirInOrder(raiz->esq); // Exibe a subárvore esquerda
        for (int i = 0; i < raiz->contador; i++) {
            printf("%d ", raiz->chave); // Exibe a chave do nó
        }
        exibirInOrder(raiz->dir); // Exibe a subárvore direita
    }
}

// Função para contar o número de nós distintos na árvore
int contarNos(PONT raiz) {
    if (raiz == NULL) return 0; // Se a árvore estiver vazia, retorna 0
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir); // Conta o nó atual e os nós das subárvores
}

// Função para contar o total de elementos na árvore (somando os contadores)
int contarTotalElementos(PONT raiz) {
    if (raiz == NULL) return 0; // Se a árvore estiver vazia, retorna 0
    return raiz->contador + contarTotalElementos(raiz->esq) + contarTotalElementos(raiz->dir); // Conta os elementos do nó atual e das subárvores
}

// Função para encontrar o k-ésimo menor elemento na árvore
int kEsimoMenor(PONT raiz, int k) {
    if (raiz == NULL) return -1; // Se a árvore estiver vazia, retorna -1

    int esqCount = contarTotalElementos(raiz->esq); // Conta os elementos na subárvore esquerda

    if (k <= esqCount) return kEsimoMenor(raiz->esq, k); // O k-ésimo menor está na subárvore esquerda
    if (k <= esqCount + raiz->contador) return raiz->chave; // O k-ésimo menor é a chave do nó atual
    return kEsimoMenor(raiz->dir, k - esqCount - raiz->contador); // O k-ésimo menor está na subárvore direita
}

// Função para imprimir os elementos da árvore dentro de um intervalo
void imprimirIntervalo(PONT raiz, int min, int max) {
    if (raiz == NULL) return; // Se a árvore estiver vazia, não faz nada
    if (raiz->chave > min) imprimirIntervalo(raiz->esq, min, max); // Imprime a subárvore esquerda se a chave for maior que o mínimo
    if (raiz->chave >= min && raiz->chave <= max) { // Imprime a chave do nó se estiver dentro do intervalo
        for (int i = 0; i < raiz->contador; i++) {
            printf("%d ", raiz->chave);
        }
    }
    if (raiz->chave < max) imprimirIntervalo(raiz->dir, min, max); // Imprime a subárvore direita se a chave for menor que o máximo
}

// Função para encontrar o ancestral comum mais baixo de dois valores
PONT lowestCommonAncestor(PONT raiz, int val1, int val2) {
    if (raiz == NULL) return NULL; // Se a árvore estiver vazia, retorna NULL
    if (val1 < raiz->chave && val2 < raiz->chave) return lowestCommonAncestor(raiz->esq, val1, val2); // Busca na subárvore esquerda
    if (val1 > raiz->chave && val2 > raiz->chave) return lowestCommonAncestor(raiz->dir, val1, val2); // Busca na subárvore direita
    return raiz; // Retorna o nó atual como o ancestral comum mais baixo
}


int main() {
    PONT raiz;
    inicializar(&raiz);

    // Testes conforme fornecido
    inserir(raiz, 10);
    inserir(raiz, 5);
    inserir(raiz, 15);
    inserir(raiz, 10);
    inserir(raiz, 5);
    inserir(raiz, 5);
    inserir(raiz, 18);

    printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
    printf("InOrder esperado: 5 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz); 
    printf("\n");

    PONT node5 = buscar(raiz, 5);
    if(node5) {
        printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
    } else {
        printf("\nBuscar(5): não encontrado (inesperado)\n");
    }

    PONT nodeX = buscar(raiz, 999);
    if(!nodeX) {
        printf("Buscar(999): não encontrado (esperado)\n");
    } else {
        printf("Buscar(999): encontrado??? (inesperado)\n");
    }

    removerUmaOcorrencia(raiz, 5);

    printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
    printf("Esperado InOrder: 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    node5 = buscar(raiz, 5);
    if(node5) {
        printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
    }

    removerTodasOcorrencias(raiz, 10);

    printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
    printf("Esperado InOrder: 5 5 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
    printf("contarTotalElementos => %d (esperado=4)\n", totalElem);

    printf("\n--- Teste k-ésimo menor ---\n");
    printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz,1));
    printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz,2));
    printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz,3));
    printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz,4));
    printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz,5));

    printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
    printf("Esperado: 15 18\nObtido:   ");
    imprimirIntervalo(raiz, 6, 18);
    printf("\n");

    inserir(raiz, 12);
    inserir(raiz, 16);
    inserir(raiz, 3);

    printf("\n--- Árvore após inserir(12,16,3) ---\n");
    printf("InOrder esperado: 3 5 5 12 15 16 18\n");
    printf("Obtido:          ");
    exibirInOrder(raiz);
    printf("\n");

    PONT nLCA;

    nLCA = lowestCommonAncestor(raiz, 3, 5);
    if(nLCA) {
        printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 3, 12);
    if(nLCA) {
        printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 16, 18);
    if(nLCA) {
        printf("LCA(16,18) => chave=%d (esperado=15)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 5, 18);
    if(nLCA) {
        printf("LCA(5,18) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 100, 3);
    if(!nLCA) {
        printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");

    return 0;
}