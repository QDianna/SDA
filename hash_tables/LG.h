/* ANA Elena-Diana - 311CB */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef void (*TF)(void*);

// lista generica
typedef struct celulag {
    void* info;
    struct celulag *urm;
}TCelulaG, *TLG;

// structura de informatie pentru listele de lungimi
typedef struct {
    int lungime;
    TLG cuvinte;
}Tinfo_lista1;

// structura de informatie pentru listele de cuvinte ale elementelor listelor de lungimi
typedef struct {
    char* cuvant;
    int aparitii;
}Tinfo_lista2;

// structura de informatie pentru lista auxiliara folosita la citire
typedef struct {
    char* cuvant;
    int lungime;
    int aparitii;
}Tinfo_citire;


TLG verifAparitie(TLG*, char* );
int citesteCuvinte(TLG*, char*);

int InsL_aux(TLG*, void*);
int InsL1(TLG* , void*);
int InsL2(TLG*, void*);

void afiseazaLG(TLG*, TF);
void afiseazaL_aux(void*);
void afiseazaL1(void*, TF);
void afiseazaL2(void*);

void afiseaza_caz1(void*, int, int, int*);

void elibL_aux(void*);
void DistrugeL_aux(TLG*, TF);
void elibL1(void*);
void elibL2(void*);

#endif