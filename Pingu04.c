/*
INTEGRANTES:
Ana Julia de Oliveira Bellini           RA 111.774
Natalia Araujo dos Reis                 RA 112.247
*/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX_PAGINAS 1023
#define tau 10



/*IMPLEMENTAÇÃO DA LISTA DE PÁGINAS (CIRCULAR)*/
struct pagina {
    float time;     //tempo de uso
    int R;
    int M;
    long id_pagina;
    struct pagina *paginaAnterior;
    struct pagina *proximaPagina;
};
typedef struct pagina Pagina;

struct lista {
	Pagina *primeiraPagina;
	Pagina *ultimaPagina;
	int numPaginas;
};
typedef struct lista listaPaginas;

/*INCIALIZAÇÃO DA LISTA DE PÁGINAS*/
void inicListaPaginas(listaPaginas *novaLista) {
    novaLista->primeiraPagina = NULL;
    novaLista->numPaginas = 0;
}

/*INSERÇÃO NA LISTA DE PÁGINAS*/
int inserirPagina(listaPaginas *listaPag, float tempoRef, int R, int M, long idPagina) {
    if (listaPag->numPaginas == MAX_PAGINAS) // lista já está com o máximo possível de páginas, então não adiciona
        return 0;
    else {
        Pagina *novaPagina = (Pagina*)malloc(sizeof(Pagina)); // alocação de memória pra página nova

        novaPagina->time = tempoRef; // adicionar tempo do último uso
        novaPagina->R = R; // adicionar bit R
        novaPagina->M = M; // adicionar bit M
        novaPagina->id_pagina = idPagina; // adicionar número da página

        // primeira página da lista
        if (listaPag->numPaginas == 0) {
            novaPagina->proximaPagina = novaPagina; // sua próxima página é ela mesma
            novaPagina->paginaAnterior = novaPagina; // sua página anterior é ela mesma
            listaPag->primeiraPagina = novaPagina; // ela é a primeira página
            listaPag->ultimaPagina = novaPagina;    //ela é a ultima prova
        }

        // lista já possui outras páginas
        else {
            novaPagina->proximaPagina = listaPag->primeiraPagina; // página entra no final, então sua próxima página é a primeira da lista
            novaPagina->paginaAnterior = listaPag->primeiraPagina->paginaAnterior; // sua anterior será a anterior da primeira página
            listaPag->primeiraPagina->paginaAnterior->proximaPagina = novaPagina; // próxima página depois da ex-última é a nova
            listaPag->primeiraPagina->paginaAnterior = novaPagina; // a anterior da primeira é a nova
        }

        listaPag->numPaginas++; // incrementa número de páginas (usadas na execução do programa)
        return 1;
    }
}

/*IMPRESSÃO DA LISTA DE PÁGINAS*/
void imprimirPaginas(listaPaginas *listaPag) {
    Pagina *auxPagina = listaPag->primeiraPagina; // auxiliar para impressão começa na primeira página
    int i;

    for (i = 0; i < listaPag->numPaginas; i++) {
        printf("Tempo = %f\n", auxPagina->time); // imprimir tempo de último uso
        printf("R = %d\n", auxPagina->R); // imprimir bit R
        printf("M = %d\n\n", auxPagina->M); // imprimir bit M
        printf("Número da Página = %ld", auxPagina->id_pagina); // adicionar número da página
        auxPagina = auxPagina->proximaPagina;
    }
}

/*IMPLEMENTAÇÃO DA LISTA DA MEMÓRIA*/
struct celulaMemoria {
    long id_pagina;
    struct celulaMemoria *proximaMemoria;
};
typedef struct celulaMemoria Memoria;

/*INICIALIZAÇÃO DA LISTA DA MEMÓRIA*/
Memoria* criarListaMemoria(void) {
    return NULL;
}

/*INSERÇÃO NA LISTA DA MEMÓRIA*/
Memoria* inserirMemoria(Memoria* listaMemoria, long idPagina) {
    Memoria* novaMemoria; // declaração da nova célula de memória
    Memoria* memoriaAnterior = NULL; // auxiliar para percorrer a lista
    Memoria* auxLista = listaMemoria; // auxiliar que recebe a lista de memória

    // encontrar posição de inserção da memória
    while (auxLista != NULL) {
        memoriaAnterior = auxLista;
        auxLista = auxLista->proximaMemoria;
    }

    // alocação e inserção da memória
    novaMemoria = (Memoria*)malloc(sizeof(Memoria));
    novaMemoria->id_pagina = idPagina;

    // encadeamento da nova memória
    if (memoriaAnterior == NULL) { // lista vazia, memória será o início
        novaMemoria->proximaMemoria = listaMemoria;
        listaMemoria = novaMemoria;
    } else { // já existe coisa na lista, entra no final
        novaMemoria->proximaMemoria = memoriaAnterior->proximaMemoria;
        memoriaAnterior->proximaMemoria = novaMemoria;
    }

    return listaMemoria;
}

/*IMPRESSÃO DA LISTA DA MEMÓRIA*/
void imprimirMemorias(Memoria* listaMemoria) {
    Memoria* memoriaAux;

    for(memoriaAux = listaMemoria; memoriaAux != NULL; memoriaAux = memoriaAux->proximaMemoria)
        printf("Número da Página em Memória = %ld", memoriaAux->id_pagina);
}

/*IMPLEMENTAÇÃO DA LISTA DO DISCO*/
struct celulaDisco {
    long id_pagina;
    struct celulaDisco *proximoDisco;
};
typedef struct celulaDisco Disco;

/*INICIALIZAÇÃO DA LISTA DO DISCO*/
Disco* criarListaDisco(void) {
    return NULL;
}

/*INSERÇÃO NA LISTA DO DISCO*/
Disco* inserirDisco(Disco* listaDisco, long idPagina) {
    Disco* novoDisco; // declaração da nova célula de disco
    Disco* discoAnterior = NULL; // auxiliar para percorrer a lista
    Disco* auxLista = listaDisco; // auxiliar que recebe a lista de disco

    // encontrar posição de inserção de disco
    while (auxLista != NULL) {
        discoAnterior = auxLista;
        auxLista = auxLista->proximoDisco;
    }

    // alocação e inserção de disco
    novoDisco = (Disco*)malloc(sizeof(Disco));
    novoDisco->id_pagina = idPagina;

    // encadeamento do novo disco
    if (discoAnterior == NULL) { // lista vazia, disco será o início
        novoDisco->proximoDisco = listaDisco;
        listaDisco = novoDisco;
    } else { // já existe coisa na lista, entra no final
        novoDisco->proximoDisco = discoAnterior->proximoDisco;
        discoAnterior->proximoDisco = novoDisco;
    }

    return listaDisco;
}

/*IMPRESSÃO DA LISTA DO DISCO*/
void imprimirDisco(Disco* listaDisco) {
    Disco* discoAux;

    for(discoAux = listaDisco; discoAux != NULL; discoAux = discoAux->proximoDisco)
        printf("Número da Página em Disco = %ld", discoAux->id_pagina);
}

/*FUNÇÃO PRINCIPAL*/
int main(int argc, char const *argv[]) {

    // declaração de variáveis
    int tempo = 100;
    int idade, contador = 1;
    int alocou = 0;
    int substituiu = 0;
    listaPaginas listaPag;
    Memoria* listaMemoria;
    Disco* listaDisco;
    int R1 = listaPag.primeiraPagina->R;
    Pagina *novo;

    // inicialização das listas
    inicListaPaginas(&listaPag);
    listaMemoria = criarListaMemoria();
    listaDisco = criarListaDisco();

    while(contador){
        if(R1 == 1){
            R1 = __TIME__;
            printf("Pagina esta em uso\n");
            listaPag.primeiraPagina->proximaPagina;
            //listaPag->primeiraPagina.proximaPagina;
            continue;
        }

        else if(R1 == 0){
        printf("Pagina nao referenciada\n");
        idade = tempo - listaPag.primeiraPagina->time;

            if(idade > tau && listaPag.primeiraPagina->M == 0){   //não está no working set (idade > tau) e uma copia valida existe no disco (M ==0)
                //Criando uma nova página
                listaPag.primeiraPagina->M = novo->M;
                listaPag.primeiraPagina->R = novo->R;
                listaPag.primeiraPagina->time = novo->time;
                listaPag.primeiraPagina = listaPag.primeiraPagina->proximaPagina;
            }

            else if(listaPag.primeiraPagina->M == 1){           //tem uma cópia válida no disco! (M == 1)
                listaPag.primeiraPagina->proximaPagina;
            }
        }

        if(listaPag.primeiraPagina == listaPag.primeiraPagina->paginaAnterior){
            Pagina *aux;
            while(aux != NULL){
                if(aux->M == 0){        //não tem cópia válida
                    aux->M = novo->M;
                    aux->R = novo->R;
                    aux->time = novo->time;
                    substituiu++;
                    break;
                }
                aux = aux->proximaPagina;
            }
            if(substituiu == 0){    //se não substituiu, substitui qualquer pagina
                listaPag.primeiraPagina->M = novo->M;
                listaPag.primeiraPagina->R = novo->R;
                listaPag.primeiraPagina->time = novo->time;
            }
        }
        tempo++;
        contador--;
    }

    printf("terminei o codigo\n");
    imprimirPaginas(&listaPag);



    return 0;
}
