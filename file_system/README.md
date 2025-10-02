# Tema 1 – File System

Proiect realizat pentru cursul **Structuri de Date și Algoritmi**.  
Scopul este implementarea unui sistem de fișiere simplificat, bazat pe arbori binari de căutare, care permite operații de tip UNIX (`touch`, `mkdir`, `ls`, `rm`, `rmdir`, `cd`, `pwd`).  

## Descriere generală
- Directorul `root` este creat la inițializare.  
- Fiecare linie din fișierul de input reprezintă o comandă (instructiune + argumente).  
- Se păstrează o structură pe doi arbori binari pentru fiecare director: unul pentru fișiere și unul pentru subfoldere.  

## Funcționalități implementate

### `touch`
- Creează un nou fișier în directorul curent.  
- Verifică dacă numele există deja printre subdirectoare sau fișiere.  
- Dacă nu există, inserează fișierul într-un arbore binar de fișiere.  
- Folosește `construct_file` pentru a inițializa nodul.  

### `mkdir`
- Creează un nou subdirector.  
- Similar cu `touch`, dar inserează într-un arbore de foldere.  
- La inițializare setează `subfolders_root = NULL` și `files_root = NULL`.  

### `ls`
- Afișează conținutul directorului curent.  
- Parcurgere **in-order** a arborilor de subfoldere și fișiere.  

### `rm`
- Șterge un fișier din directorul curent.  
- Caută nodul după nume; dacă nu există, afișează mesaj de eroare.  
- Gestionează cele 3 cazuri: nod fără copii, cu un copil, sau cu doi copii (înlocuit cu minimul din subarborele drept).  

### `rmdir`
- Identică cu `rm`, dar aplicată pe arborele de directoare.  

### `cd`
- Schimbă directorul curent.  
- `cd ..` revine la directorul părinte.  
- `cd <nume>` caută directorul cu `findfolder`; dacă este găsit, întoarce adresa lui.  

### `pwd`
- Afișează calea completă până la directorul curent.  
- Implementat recursiv, urcând prin câmpul `parent` până la `root`.  

## Tehnologii și concepte
- **C** pentru implementare.  
- **Arbori binari de căutare** pentru gestionarea fișierelor și folderelor.  
- **Funcții recursive** pentru căutare și afișare.  

## Concluzie
Proiectul implementează un **mini-sistem de fișiere** care reproduce comportamentul comenzilor de bază din UNIX folosind structuri de date clasice. Este un exemplu de aplicare a arborilor binari de căutare și a funcțiilor recursive în managementul datelor ierarhice.  
