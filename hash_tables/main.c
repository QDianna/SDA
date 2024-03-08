/* ANA Elena-Diana - 311CB */
#include "LG.h"
#include "TH.h"

int main(int argc, char* argv[]) {
    FILE* f;
    char* line = NULL;
    size_t len = 0;
    f = fopen(argv[1], "r");
    if (f == NULL)
        return 0;

    TH* h = NULL;
    TLG L_aux = NULL;  // lista auxiliara in care retin initial cuvintele + lungimea si aparitiile acestora

    while (getline(&line, &len, f) != -1) {
        char *instruct = strtok(line, " \n");

        if (strcmp(instruct, "insert") == 0) {
            citesteCuvinte(&L_aux, line+7);
            if (L_aux == NULL)
                printf("Lista de cuvinte nu a putut fi generata\n");
        }

        if (strcmp(instruct, "print") == 0) {
            h = GenerareTH(L_aux);  // generez TH cu elementele din L_aux citite pana in acest punct
            if (h == NULL)
                printf("Tabela Hash nu a putut fi generata\n");

            else {
                char* param_print = strtok(NULL, "\n");  // determin daca am printare conditionata

                if (param_print) {
                    if (strlen(param_print) == 1) {  // printare elemente din TH care au frecventa < frecventa_maxima 
                        int frecv_max = atoi(param_print); 
                        afiseazaTH_caz1(h, afiseaza_caz1, frecv_max);
                    }

                    if (strlen(param_print) == 3) {  // printare elemente din TH care initiala si lungimea ceruta
                        char initiala = param_print[0];
                        int lungimea = param_print[2]-'0';
                        afiseazaTH_caz2(h, afiseazaL2, lungimea, initiala);
                    }
                }

                else
                    afiseazaTH(h, afiseazaL1);  // afisare standard a TH
            }
            DistrugeTH(&h, elibL1, elibL2);
        }
    }

    fclose(f);
    free(line);
    
    DistrugeL_aux(&L_aux, elibL_aux);
    
    return 0;
}