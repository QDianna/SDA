# Tema 2 – Hash Tables

Proiect realizat pentru cursul **Structuri de Date și Algoritmi**.  
Scopul este implementarea unei **tabele hash** care stochează cuvinte și permite inserarea și afișarea lor în funcție de diferite criterii.  

## Descriere generală
- Programul citește instrucțiuni dintr-un fișier de input.  
- Fiecare linie conține o comandă (`insert`, `print`) și eventual parametri suplimentari.  
- Se folosește o **listă auxiliară** pentru stocarea inițială a cuvintelor, apoi acestea sunt introduse în tabela hash.  

## Funcționalități implementate

### Insert
- Se citesc cuvintele de pe linia de input.  
- Pentru fiecare cuvânt se salvează:
  - valoarea stringului,  
  - lungimea,  
  - numărul de apariții.  
- Dacă cuvântul există deja, se incrementează numărul de apariții.  
- Dacă nu există, se creează o celulă nouă.  

### Generarea tabelei hash
- Tabela conține:  
  - un vector de `M` elemente (unde `M = numărul de litere din alfabet`),  
  - numărul `M`,  
  - pointer la funcția de hash.  
- Inserarea:  
  - Hash-ul este determinat de inițiala cuvântului.  
  - În vectorul `v`, fiecare poziție corespunde unei liste `L1`.  
  - Lista `L1` conține elemente grupate după **lungimea cuvintelor**.  
  - Fiecare element din `L1` are o listă `L2`, ce stochează efectiv cuvintele și numărul lor de apariții.  
- Funcții folosite:  
  - `InsL1` – inserează în lista de lungimi,  
  - `InsL2` – inserează cuvântul în lista de cuvinte cu aceeași lungime.  

### Print
- Dacă nu există parametri → printare standard (toată tabela).  
- Dacă există **1 parametru** (frecvența maximă):  
  - se afișează doar cuvintele cu frecvență `< frecvența dată`.  
- Dacă există **2 parametri** (inițială + lungime):  
  - se afișează doar cuvintele corespunzătoare.  
- Afișarea folosește funcții dedicate:  
  - `afiseazaL1` pentru lista de lungimi,  
  - `afiseazaL2` pentru lista de cuvinte.  
- Se folosesc semafoare logice (`ok_pos`, `ok_len`, `ok_enter`) pentru a controla formatul afișării.  

### Dezalocarea memoriei
- După fiecare printare tabela hash este eliberată pentru a evita memory leaks.  
- Etape:  
  - parcurgerea vectorului `v`,  
  - eliberarea listelor `L1` și `L2` cu funcțiile `elibL1` și `elibL2`,  
  - eliberarea vectorului `v` și a structurii tabelei,  
  - eliberarea listei auxiliare de la citire.  

## Tehnologii și concepte
- **C** pentru implementare.  
- **Hashing** cu funcție simplă (inițiala cuvântului).  
- **Liste generice** pentru gestionarea coliziunilor.  
- **Grupare pe criterii** (lungime, apariții).  
- **Gestionarea memoriei** (alocare/dezalocare).  

## Concluzie
Tema demonstrează implementarea unei structuri **Hash Table cu liste de adiacență**, care permite:  
- inserarea rapidă a cuvintelor,  
- afișarea condiționată după frecvență, inițială sau lungime,  
- eliberarea completă a memoriei.  
