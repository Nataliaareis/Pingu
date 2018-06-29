/*
 INTEGRANTES:
 Ana Julia de Oliveira Bellini           RA 111.774
 Natalia Araujo dos Reis                 RA 112.247
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include<time.h>
-
 #define MAX_PAGINAS 1023
+#define tau 10
+
+
 
 /*IMPLEMENTAÇÃO DA LISTA DE PÁGINAS (CIRCULAR)*/
 struct pagina {
-    float time;
+    float time;     //tempo de uso
     int R;
     int M;
     long id_pagina;
@@ -23,6 +25,7 @@ typedef struct pagina Pagina;
 
 struct lista {
 	Pagina *primeiraPagina;
+	Pagina *ultimaPagina;
 	int numPaginas;
 };
 typedef struct lista listaPaginas;
@@ -50,6 +53,7 @@ int inserirPagina(listaPaginas *listaPag, float tempoRef, int R, int M, long idP
             novaPagina->proximaPagina = novaPagina; // sua próxima página é ela mesma
             novaPagina->paginaAnterior = novaPagina; // sua página anterior é ela mesma
             listaPag->primeiraPagina = novaPagina; // ela é a primeira página
+            listaPag->ultimaPagina - novaPagina;    //ela é a ultima prova
         }
 
         // lista já possui outras páginas
@@ -68,8 +72,9 @@ int inserirPagina(listaPaginas *listaPag, float tempoRef, int R, int M, long idP
 /*IMPRESSÃO DA LISTA DE PÁGINAS*/
 void imprimirPaginas(listaPaginas *listaPag) {
     Pagina *auxPagina = listaPag->primeiraPagina; // auxiliar para impressão começa na primeira página
+    int i;
 
-    for (int i = 0; i < listaPag->numPaginas; i++) {
+    for (i = 0; i < listaPag->numPaginas; i++) {
         printf("Tempo = %f\n", auxPagina->time); // imprimir tempo de último uso
         printf("R = %d\n", auxPagina->R); // imprimir bit R
         printf("M = %d\n\n", auxPagina->M); // imprimir bit M
@@ -176,34 +181,75 @@ void imprimirDisco(Disco* listaDisco) {
 
 /*FUNÇÃO PRINCIPAL*/
 int main(int argc, char const *argv[]) {
-    printf("OI\n");
+
     // declaração de variáveis
+    int tempo = 100;
+    int idade, contador = 1;
+    int alocou = 0;
+    int substituiu = 0;
     listaPaginas listaPag;
     Memoria* listaMemoria;
     Disco* listaDisco;
+    int R1 = listaPag.primeiraPagina->R;
+    Pagina *novo;
 
     // inicialização das listas
     inicListaPaginas(&listaPag);
     listaMemoria = criarListaMemoria();
     listaDisco = criarListaDisco();
 
-    if(pagina.R == 1){
-        pagina.R = __TIME__;
-        printf("Pagina estava em uso\n");
-    }
+    while(contador){
+        if(R1 == 1){
+            R1 = __TIME__;
+            printf("Pagina esta em uso\n");
+            listaPag.primeiraPagina->proximaPagina;
+            //listaPag->primeiraPagina.proximaPagina;
+            continue;
+        }
 
-    else if(R == 0){
-        printf("Pagina nao referenciada\n")
+        else if(R1 == 0){
+        printf("Pagina nao referenciada\n");
+        idade = tempo - listaPag.primeiraPagina->time;
+
+            if(idade > tau && listaPag.primeiraPagina->M == 0){   //não está no working set (idade > tau) e uma copia valida existe no disco (M ==0)
+                //Criando uma nova página
+                listaPag.primeiraPagina->M = novo->M;
+                listaPag.primeiraPagina->R = novo->R;
+                listaPag.primeiraPagina->time = novo->time;
+                listaPag.primeiraPagina = listaPag.primeiraPagina->proximaPagina;
+            }
+
+            else if(listaPag.primeiraPagina->M == 1){           //tem uma cópia válida no disco! (M == 1)
+                listaPag.primeiraPagina->proximaPagina;
+            }
+        }
+
+        if(listaPag.primeiraPagina == listaPag.primeiraPagina->paginaAnterior){
+            Pagina *aux;
+            while(aux != NULL){
+                if(aux->M == 0){        //não tem cópia válida
+                    aux->M = novo->M;
+                    aux->R = novo->R;
+                    aux->time = novo->time;
+                    substituiu++;
+                    break;
+                }
+                aux = aux->proximaPagina;
+            }
+            if(substituiu == 0){    //se não substituiu, substitui qualquer pagina
+                listaPag.primeiraPagina->M = novo->M;
+                listaPag.primeiraPagina->R = novo->R;
+                listaPag.primeiraPagina->time = novo->time;
+            }
+        }
+        tempo++;
+        contador--;
     }
 
-    // inserção das páginas, memórias e discos
-        // inserirPagina(&listaPag, 1, 0, 0, 1234);
-        // imprimirPaginas(&listaPag);
-        // inserirMemoria
-        // imprimirMemorias
-        // inserirDisco
-        // imprimirDisco
+    printf("terminei o codigo\n");
+    imprimirPaginas(&listaPag);
+
+
 
     return 0;
 }
