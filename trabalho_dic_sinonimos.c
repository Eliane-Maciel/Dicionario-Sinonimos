// Trabalho de Estrutura de dados - Dicionário de Sinônimos
// Desevolvedora : Eliane Isadora Faveron Maciel, Juciano Cardoso
// Dicioário de Sinônimos 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct hashletras HashLetras;
typedef struct palavras Palavras;
typedef struct sinonimo Sinonimo;

struct hashletras {
    char letra;
    Palavras *palavras;
    HashLetras *prox;
};

struct palavras {
    char nome[100];
    int num_consultas;
    Palavras *esq, *dir;
    Sinonimo *lista_sinonimo;
};

struct sinonimo {
    Palavras *palavra;
    Sinonimo *prox;
};

// Tira enter de string;
void TirarEnter(char str[100]){
    int j=0;
    while(str[j]!='\n'){
        j++;        
    }
    str[j]='\0';
}

//Transforma em maiusculo strings
void TransformaMaiusculo(char str[100]){
    int len, i=0;

    for(i=0; str[i]; i++){
       str[i] = toupper(str[i]);
    }
    str[i]= '\0';
}

//Busca Letra na lista da tabela Hash.
HashLetras *BuscaLetra (HashLetras *nodo, char l){
    if (nodo == NULL) return NULL;
    if (nodo->letra == l){
        return nodo;
    }
    return BuscaLetra(nodo->prox, l);
}

//Busca Palavra na árvore de palavras.
Palavras *BuscaPalavra (Palavras *nodo, char l[100]){
    if(nodo==NULL) return;
    if (strcmp(nodo->nome, l)==0){
        return nodo;
    }
    return BuscaPalavra(nodo->esq, l);
    return BuscaPalavra(nodo->dir, l);
}

Palavras *InserePalavra(Palavras **p_raiz, char palavra[100]){
    Palavras *palavra_aux=NULL;

    palavra_aux = BuscaPalavra(*p_raiz, palavra);
    if(palavra_aux == NULL){
        if (*p_raiz == NULL){
            *p_raiz = (Palavras *) malloc(sizeof(Palavras));
            (*p_raiz)->esq = NULL;
            (*p_raiz)->dir = NULL;
            strcpy((*p_raiz)->nome, palavra);
            return *p_raiz;
        }
        else if(strcmp(palavra, (*p_raiz)->nome) < 0)
            InserePalavra(&(*p_raiz)->esq, palavra);
        else
            InserePalavra(&(*p_raiz)->dir, palavra);
    }
    else{
        return palavra_aux;
    }
}

HashLetras *InsereLetra(HashLetras **letra_inicio, char l){
    HashLetras *busca_l=NULL, *ptaux=NULL, *ptaux2=NULL, *ptant=NULL;

    busca_l = BuscaLetra(*letra_inicio, l);
    if(busca_l == NULL){
        
        ptaux = (HashLetras *)malloc(sizeof(HashLetras));
        ptaux->letra = l; 
        if(*letra_inicio == NULL){
            ptaux->prox = NULL;
            *letra_inicio = ptaux;
            printf("Aqui\n");
            return ptaux;
        }
        ptaux2 = *letra_inicio;
        ptant = ptaux2;
        while ((ptaux2->prox != NULL) && (ptaux2->letra < l)){
            ptant = ptaux2;
            ptaux2=ptaux2->prox;
        }
        if(ptaux2->prox == NULL && (ptaux2->letra < l)){
            ptaux->prox = NULL;
            ptaux2->prox = ptaux;
            return ptaux;
        }
        else{
            ptaux->prox = ptant->prox;
            ptant->prox = ptaux;
            return ptaux;
        }
    }
    else {
        return busca_l;
    }
}

void InsereSinonimo(Sinonimo **sinonimo_inicio, Palavras *palavra){
    Sinonimo *aux2=NULL, *aux=NULL;

    aux = (Sinonimo *)malloc(sizeof(Sinonimo));
    aux->palavra = palavra;
    aux->prox = NULL;

    if (*sinonimo_inicio == NULL){
        *sinonimo_inicio = aux;
    }
    else{
        aux2 = *sinonimo_inicio;
        while (aux2->prox != NULL){
            aux2=aux2->prox;
        }
        aux2->prox = aux;
    }
}

// escreve livros - dados e autores do livro
void escreve_conteudo(HashLetras *hashletras){
    if(hashletras == NULL){
        printf("Não possui letra cadastrados.\n");
        return;
    }

    while(hashletras != NULL){
        printf("%c\n", hashletras->letra);
        hashletras = hashletras->prox;
    }
}

int main(){
    HashLetras *hashletras_inicio=NULL, *my_letra=NULL, *my_letra2=NULL;
    Palavras *palavra_aux=NULL, *palavra_aux2=NULL;
    char nome[100], nome2[100], letra, letra2;

    printf("Digite a Palavra que deseja Inserir:\n");
    fgets(nome, 100, stdin);
    TirarEnter(nome);
    TransformaMaiusculo(nome);
    letra = nome[0];
    my_letra = InsereLetra(&hashletras_inicio, letra);
    my_letra2 = InsereLetra(&hashletras_inicio, 'b');
    // printf("%c\n", my_letra->letra);
    // palavra_aux = InserePalavra(*my_letra)->palavras, nome);
    // printf("Digite o sinonimo da palavra:\n");
    // fgets(nome2, 100, stdin);
    // TirarEnter(nome2);
    // TransformaMaiusculo(nome2);
    // letra2 = nome2[0];
    // my_letra2 = InsereLetra((&hashletras_inicio), letra);
    // palavra_aux2 = InserePalavra(&(*my_letra2)->palavras), nome2);
    // InsereSinonimo(&(*palavra_aux)->lista_sinonimo, palavra_aux2);
    // InsereSinonimo(&(*palavra_aux2)->lista_sinonimo, palavra_aux);
    // printf("%c\n", my_letra->letra);
    // printf("%s\n", palavra_aux->nome);
    // printf("%c\n", my_letra2->letra);
    // printf("%s\n", palavra_aux2->nome);
    // escreve_conteudo(hashletras_inicio);

}