/* ANA Elena-Diana - 311CB */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "LG.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFHash)(void*);
typedef void (*TF)(void*);
typedef void (*TF2)(void*, TF);
typedef void (*TF3)(void*, int, int, int*);

typedef struct {
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

TH* InitTH(size_t, TFHash);

int codHash(void*);
void InsTH(TH*, void*);
TH* GenerareTH(TLG);

void afiseazaTH(TH*, TF2);

void afiseazaTH_caz1(TH*, TF3, int);
void afiseazaTH_caz2(TH*, TF, int, char);

void DistrugeTH(TH** ah, TF elibL1, TF elibL2);
#endif