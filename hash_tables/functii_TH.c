/* ANA Elena-Diana - 311CB */
#include "TH.h"

// functia hash
int codHash(void* element) {
    Tinfo_lista2 *c = (Tinfo_lista2*) element;
    char initiala = c->cuvant[0];

    if (initiala >= 'A' && initiala <= 'Z')
        return initiala - 'A';
    else
        if (initiala >= 'a' && initiala <= 'z')
            return initiala - 'a';
    return -1;
}

// functie de initializare + alocare memorie pentru TH
TH* InitTH(size_t M, TFHash fh) {
    TH* h = (TH*) calloc(sizeof(TH), 1);
    if (!h) {
        printf("Eroare alocare Tabela Hash\n");
        return NULL;
    }

    h->v = (TLG*) calloc(M, sizeof(TLG));

    if (!h->v) {
        printf("Eroare alocare vector de pointeri TLG in Tabela Hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

void InsTH(TH* ah, void* ae) {
    int cod = ah->fh(ae);  // ah->v+cod e adresa de la care incepe lista cu lungimi
    if (cod == -1) 
        printf("Eroare generare cod hash");
    else
        InsL1(ah->v+cod, ae);
}

// functie de geneare a TH
TH* GenerareTH(TLG L_aux) {
    TH *h = NULL;
    TLG p;

    size_t M = ('Z' - 'A' + 1);
    h = (TH*) InitTH(M, codHash);
    if (h == NULL) 
        return NULL;

    //  L_cuvinte are info: cuvant, lungime, nr aparitii pt fiecare cuvant citit
    for (p = L_aux; p; p = p->urm) {
        Tinfo_citire* c = (Tinfo_citire*) p->info;
        InsTH(h, (void*) c);
    }

    return h;
}

// functie de afisare standard a TH
void afiseazaTH(TH* ah, TF2 afiEL) {
    TLG p, e;
    for (int i = 0; i < ah->M; i++) {
        p = ah->v[i];
        if(p) {
            printf("pos %d: ", i);
            for(e = p; e; e = e->urm) {
                printf("(");
                afiEL(e->info, afiseazaL2);
                printf(")");
            }
            printf("\n");
        }
    }
}

// functie de afisare elemente din TH care au o frecventa < frecventa_maxima
void afiseazaTH_caz1(TH* ah, TF3 afiEL, int f) {
    TLG p, e;
    for (int i = 0; i < ah->M; i++) {
        int ok_pos = 0;
        p = ah->v[i];
        for(e = p; e; e = e->urm) {
            afiEL(e->info, f, i, &ok_pos);
        }
        if(ok_pos == 1)
            printf("\n");
    } 
}


// functie de afisare elemente din TH care au o anumita initiala si o anumita lungime
void afiseazaTH_caz2(TH* ah, TF afiEL, int l, char c) {
    TLG p, e;
    int i = 0;
    if(c>='a' && c<='z')
        i = c-'a';
    if(c>='A' && c<='Z')
        i = c-'A';
        
    p = ah->v[i];  // lista cu lungimi aferenta initialei cerute
        
    if(p) {
        int ok_enter = 0;
        for(e = p; e; e = e->urm) {
            Tinfo_lista1 *l1 = (Tinfo_lista1*) e->info;
            if (l1->lungime == l) {
                printf("(%d:", l);
                TLG q = l1->cuvinte;
                for(; q; q = q->urm){
                    afiEL(q->info);
                    if(q->urm)
                        printf(", ");
                }
                printf(")");
                ok_enter = 1;
             }
         }
        if (ok_enter)
            printf("\n");
    }
}

void DistrugeTH(TH** ah, TF elibL1, TF elibL2) {
    TLG* p, el, aux;

    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        for (el = *p; el; ) {
            aux = el;
            el = el->urm;
            elibL1(aux->info);  // eliberare info din L1 (Tinfo_lista1)
            free(aux);  // eliberare celula din L1
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}