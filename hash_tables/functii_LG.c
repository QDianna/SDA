/* ANA Elena-Diana - 311CB */
#include "LG.h"


/* functie de inserare element intr-o lista auxiliara, in care sunt retinute initial cuvintele la citire
   lista va retine: cuvantul, lungimea si nr aparitii ale acestuia */
int InsL_aux(TLG* aL_aux, void* ae) {
    TLG aux = calloc(sizeof(TCelulaG), 1);
    if (!aux)
        return 0;
    aux->info = ae;
    aux->urm = NULL;

    if (*aL_aux == NULL) {
        *aL_aux = aux;
        return 1;
    }
    else {
        aux->urm = *aL_aux;
        *aL_aux = aux;
        return 1;
    }
    return 0;
}


/* functie care verifica aparitia multipla a unui cuvant la citire
   functia va returna pointer la pozitia cuvantului, daca acesta exista deja in lista auxiliara
   sau valoarea NULL, in consecinta */
TLG verifAparitie(TLG* aL_aux, char* cuvant) {
    TLG p = *aL_aux;
    for (; p; p = p->urm) {
        Tinfo_citire *c = (Tinfo_citire*) p->info;
        if (strcmp(c->cuvant, cuvant) == 0)
            return p;
    }
    return NULL;
}


// functie care citeste cuvinte si le insereaza in lista auxiliara
int citesteCuvinte(TLG* aL_aux, char* line) {
    char* cuvant = strtok(line, " ");

    while (cuvant) {
        cuvant[strcspn(cuvant, "\n.,")] = '\0';

        if (strlen(cuvant) >= 3 && !strchr("0123456789", *cuvant)) {
            TLG p = verifAparitie(aL_aux, cuvant);  // pointer la lista auxiliara unde exista "cuvant"/NULL daca nu exista

            if (!p) {
                Tinfo_citire *c = (Tinfo_citire*) calloc(sizeof(Tinfo_citire), 1);
                if(c == NULL)
                    return 0;
                c->cuvant = calloc(sizeof(char*), strlen(cuvant));
                if (c->cuvant == NULL)
                    return 0;

                strcpy(c->cuvant, cuvant);
                c->lungime = strlen(cuvant);
                c->aparitii = 1;

                InsL_aux(aL_aux, (void*) c);
            }

            else {
                Tinfo_citire* c = (Tinfo_citire*) p->info;
                c->aparitii ++;
            }
        }

        cuvant = strtok(NULL, " ");
    }
    return 1;
}


// functie de inserare element in lista de cuvinte corespunzatoare lungimii cuvantului curent
int InsL2(TLG* aL_cuvinte, void* ae) {
    TLG p = *aL_cuvinte;
    Tinfo_citire* c = (Tinfo_citire*) ae;

    Tinfo_lista2* info_aux = calloc(sizeof(Tinfo_lista2), 1);
    if(info_aux == NULL)
        return 0;
    info_aux->cuvant = calloc(sizeof(char*), 100);
    if(info_aux->cuvant == NULL)
        return 0;
    TLG aux = calloc(sizeof(TCelulaG), 1);
    if(!aux)
        return 0;
    
    strcpy(info_aux->cuvant, c->cuvant);
    info_aux->aparitii = c->aparitii;

    aux->info = info_aux;
    aux->urm = NULL;

    if(p == NULL) {
        // inserare cand lista de cuvinte este goala
        *aL_cuvinte = aux;
        return 1;
    }

    else {
        /* inserarea in lista de cuvinte se face pastrand ordinea descrescatoare 
           dpdv al frecventei aparitiei cuvintelor */
        Tinfo_lista2* info_p = (Tinfo_lista2*) p->info;
        if(info_aux->aparitii > info_p->aparitii) {
            // inserare la inceputul listei
            aux->urm = *aL_cuvinte;
            *aL_cuvinte = aux;
            return 1;
        }

        else {
            TLG ant = NULL;
            for(; p; ant = p, p = p->urm) {
                Tinfo_lista2* info_p = (Tinfo_lista2*) p->info;
                if (info_aux->aparitii > info_p->aparitii) {
                    // inserare inainte de p
                    aux->urm = p;
                    ant->urm = aux;
                    return 1;
                }

                /* daca frecventa cuvantului curent este aceeasi cu a altor cuvinte din lista
                    inserarea va pastra ordinea lexicografica a cuvintelor */
                if (info_aux->aparitii == info_p->aparitii) {
                    if (strcmp(info_p->cuvant, info_aux->cuvant) > 0) {
                        /* inserare inainte de p
                           p poate fi inceputul listei, asadar ant poate fi NULL */
                        if(ant == NULL) {
                            // inserare la inceputul listei
                            aux->urm = *aL_cuvinte;
                            *aL_cuvinte = aux;
                            return 1;
                        }
                        // inserare inainte de p
                        aux->urm = p;
                        ant->urm = aux;
                        return 1;
                    }
                }
            }
            // daca se ajunge aici, inseamna ca inserarea se face la sfarsitul listei
            ant->urm = aux;
            aux->urm = NULL;
            return 1;
        }
    }
    return 0;
}


// functie de inseare element in lista de lungimi corespunzatoare initialei cuvantului curent 
int InsL1(TLG* aL_lungimi, void* ae) {
    TLG p = *aL_lungimi;
    Tinfo_citire* c = (Tinfo_citire*) ae;

    // CAZ 1 - lista de lungimi a cuvantului curent este nula
    if (p == NULL) {
        TLG aux = calloc(sizeof(TCelulaG), 1);
        if (!aux)
            return 0;
        Tinfo_lista1* info_aux = calloc(sizeof(Tinfo_lista1), 1);  // mem leak
        if (info_aux == NULL)
            return 0;

        info_aux->lungime = c->lungime;
        info_aux->cuvinte = NULL;
        
        TLG* aL_cuvinte = &info_aux->cuvinte;

        InsL2(aL_cuvinte, c);  // inserare in lista de cuvinte a elementului din lista de lungimi

        aux->info = info_aux;
        aux->urm = NULL;

        *aL_lungimi = aux;

        return 1;
    }
    
    // CAZ 2 - verificam daca exista elementul corespunzator lungimii cuvantului curent in lista de lungimi
    int ok = 0;
    for (; p; p = p->urm) {
        Tinfo_lista1* info_p = (Tinfo_lista1*)p->info;
        if (info_p->lungime == c->lungime) {
            ok = 1;
            TLG *aL_cuvinte = &info_p->cuvinte;
            InsL2(aL_cuvinte, c);  // inserare in lista de cuvinte a elementului din lista de lungimi
        }
    }

    if (ok)  // exista -^-
        return 1;

    else {  // nu exista -^-
        // CAZ 3 - cream un nou element pentru lungimea cuvantului curent
        p = *aL_lungimi;  // resetam pointerul la valoarea initiala - inceputul listei de lungimi
        TLG aux = calloc(sizeof(TCelulaG), 1);
        if (!aux)
            return 0;
        Tinfo_lista1* info_aux = calloc(sizeof(Tinfo_lista1), 1);  // mem leak
        if (info_aux == NULL)
            return 0;

        info_aux->cuvinte = NULL;
        info_aux->lungime = c->lungime;

        TLG* aL_cuvinte = &info_aux->cuvinte;
        InsL2(aL_cuvinte, c);  // inserare in lista de cuvinte a elementului din lista de lungimi

        aux->info = info_aux;
        aux->urm = NULL;

        // inserarea noului element se va face pastrand ordinea crescatoare a lungimii cuvintelor
        Tinfo_lista1 *info_p = (Tinfo_lista1*) p->info;
        if (info_aux->lungime <= info_p->lungime) {
            // inserare la inceputul listei de lungimi
            aux->urm = *aL_lungimi;
            *aL_lungimi = aux;
            return 1;
        }

        else {
            TLG ant = NULL;
            for (; p; ant = p, p = p->urm) {
                Tinfo_lista1 *info_p = (Tinfo_lista1*) p->info;
                if (info_aux->lungime <= info_p->lungime) {
                    // inserare inainte de p
                    aux->urm = p;
                    ant->urm = aux;
                    return 1;
                }
            }
            // daca se ajunge aici, inseamna ca inserarea se face la sfarsitul listei 
            ant->urm = aux;
            aux->urm = NULL;
            return 1;
        }
    }
    return 0;
}


// functie de afisare a elementelor din lista auxiliara in care sunt retinute initial cuvintele - debugg
void afiseazaL_aux(void* e) {
    Tinfo_citire *c = (Tinfo_citire*) e;
    printf("%s - %d - %d\n", c->cuvant, c->lungime, c->aparitii);
}


// functie de afisare standard a elementelor din lista de lungimi (din vectorul v al TH)
void afiseazaL1(void* e, TF afiEL) {
    Tinfo_lista1 *l1 = (Tinfo_lista1*) e;
    TLG p = l1->cuvinte;
    printf("%d:", l1->lungime);
    for (; p; p = p->urm){
        afiEL(p->info);
        if (p->urm)
            printf(", ");
    }
}


// functie de afisare standard a elementelor din lista de cuvinte a unui element din lista de lungimi
void afiseazaL2(void* e) {
    Tinfo_lista2 *l2 = (Tinfo_lista2*) e;
    printf("%s/%d", l2->cuvant, l2->aparitii);
}


// functie de afisare a elementelor din TH care au frecventa < frecventa_maxima 
void afiseaza_caz1(void* e, int frecv_max, int pos, int* ok_pos) {
    Tinfo_lista1 *l1 = (Tinfo_lista1*) e;
    TLG p = l1->cuvinte;
    int ok_len = 0;

    for (; p; p = p->urm) {
        Tinfo_lista2 *l2 = (Tinfo_lista2*) p->info;
        if (l2->aparitii <= frecv_max) {
            if (*ok_pos == 0) {
                printf("pos%d: ", pos);
                *ok_pos = 1;
            }
            if (ok_len == 1) {
                printf(", ");
            }
            if (ok_len == 0) {
                printf("(%d: ", l1->lungime);
                ok_len = 1;
            }
            printf("%s/%d", l2->cuvant, l2->aparitii);
        }
    }
    if(ok_len == 1)
        printf(")");   
}

void elibL_aux(void* info) {
    Tinfo_citire *c;
    c = (Tinfo_citire*) info;
    free(c->cuvant);  // eliberare char* din structura Tinfo_citire
    free(c);  // eliberare structura Tinfo_citire
    return;
}

void DistrugeL_aux(TLG* aL_aux, TF elibL_aux) {
    while (*aL_aux != NULL) {
        TLG L = *aL_aux;
        if (!L)
            return;
        elibL_aux(L->info);  // eliberare info din L_aux (Tinfo_citire)
        *aL_aux = L->urm;
        free(L);  // eliberare celula din L_aux
    }
}

void elibL1(void* info) {
    Tinfo_lista1 *l1;
    l1 = (Tinfo_lista1*) info;
    
    TLG* p = &l1->cuvinte;
    TLG el, aux;

    for(el = *p; el; ){ 
        aux = el;
        el = el->urm;
        elibL2(aux->info);  // eliberare info din L2 (Tinfo_lista2)
        free(aux);  // eliberare celula din L2
    }

    free(l1);  // eliberare structura Tinfo_lista1
    return;
}

void elibL2(void* info) {
    Tinfo_lista2 *l2;
    l2 = (Tinfo_lista2*) info;
    free(l2->cuvant);  //  eliberare char* din structura Tinfo_lista2
    free(l2);  // eliberare structura Tinfo_lista2
    return;
}