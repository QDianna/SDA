/* ANA Elena-Diana - 311CB */

-- main --
Creez folderul root.
Citesc linie cu linie informatia din input files. Din fiecare linie preiau primul cuvant
care reprezinta instructiunea si eventual un al doilea cuvant cu numele fisierului/directorului.

-- touch -- 
Functia primeste: adresa directorului parinte curent, adresa arborelui de fisiere si numele noului fisier.
Initial, verific daca numele noului fisier exista printre numele de subdirectoare;
daca da, afisez mesaj corespunzator si ies din functie, daca nu, trec mai departe.
Daca nu exista niciun alt fisier in arbore, creez un nou nod radacina cu functia construct_file.
	-- construct_file --
	Iau o variabila auxiliara de tipul structurii arborelui de fisiere (Tarbfile), copiez numele
	dorit in campul "name" si initializez cu NULL campurile "left" si "right".
Pun in campul "parent" adresa directorului parinte (cea data ca parametru functiei).
Daca exista deja noduri in arbore, gasesc pozitia pe care trebuie sa pun noul fisier, comparand
numele sau cu numele celorlalte fisiere (pe baza regulilor intr-un arbore binar de cautare, parcurg
nodurile plecand din radacina arborelui, merg la stanga daca numele este mai mic sau
la dreapta daca numele este mai mare decat nodul curent). Totodata, daca gasesc deja un fisier cu acelasi nume,
afisez mesajul corespunzator si ies din functie.

-- mkdir --
Functia este asemanatoare celei precedente (touch). Aceasta insa, primeste ca parametrii:
adresa directorului parinte, adresa arborelui de subfoldere si numele noului director.
Asemanator, verific daca exista fisiere cu acelasi nume, creez, dupa caz, fie un nod radacina
fie inserez un nou nod in arbore. Campurile structurii arborelui de directoare difera,
fiind nevoie sa initializez in plus campurile "subfolders_root" si "files_root" cu NULL la crearea unui
nod de tip Tarbfld (cu ajutorul functiei construct_folder).

-- ls --
Functia ls primeste ca parametrii arborele de subfoldere si arborele de files al directorului curent.
Printr-o parcurgere in-order (SRD) afisez informatia din cei doi arbori (cu functiie: SRD_files si SRD_folders).

-- rm --
Functia primeste adresa arborelui de fisiere al directorului curent si numele fisierului care trebuie sters.
Functia returneaza adresa noii radacini a arborelui (pentru cazul in care fix radacina trebuie stearsa,
sa fie posibila actualizarea adreseii din arbfld->files_root).
Initial, caut numele fisierului in arbore, si daca nu il gasesc / daca arborele este NULL afisez mesajul
corespunzator si ies din functie.
Localizez nodul pe care trebuie sa il sterg. Determin cate frunze are acesta si impart in 3 cazuri:
Daca are doar copilul drept, acesta devine parintele si nodul parinte este eliberat. Asemenea, pentru cazul in care are doar copilul stang.
Daca are ambii copii, caut nodul minim din subarborele dreapt al arborelui (partea cu noduri mai mari decat
nodul "radacina" de la care pornesc). Acesta devine parintele arborelui, informatia sa (numele) fiind copiata 
in nodul parinte, iar apoi functia este reapelata cu numele acestui nod gasit, pentru a fi sters.

-- rmdir --
Functia are aceeasi functionalitate ca cea anterioara - rm - diferenta fiind ca functia primeste
arborele de subfoldere al directorului curent, de unde se va sterge directorul specificat.

-- cd --
Functia primeste adresa directorului curent, si numele directorului in care se doreste "mutarea".
Daca numele este "..", functia returneaza adresa directorului parinte, din campul "parent"
al folderului curent.
Daca nu, caut numele directorului in arborele de subfoldere (cu functia findfolder); daca nu il gasesc
afisez un mesaj si ies din functie, iar daca il gasesc, apelez functia returnfolder.
Aceasta are o functionalitate asemanatoare functiei findfolder, doar ca intoarce adresa folderului cautat.
(da, putea fi o singura functie)

-- pwd --
Functia se reapeleaza recursiv, accesand campul "parent" al folderului curent, pana ajunge la
directorul root. Apoi, va afisa in ordine inversa numele directoarelor prin care a trecut.
