/* ANA Elena-Diana - 311CB */


Citesc din fisierul primit ca argument, linie cu linie. In variabila "instruct" retin primul cuvant de pe linie, care determina functionalitatea programului (insert/print).
- Functionalitatea de insert:
  Citesc cuvant cu cuvant de pe linie si stochez - cuvantul, lungimea si numarul de aparitii - intr-o lista auxiliara. Daca celula pentru cuvantul curent a fost creata anterior, ma deplasez cu un pointer la celula respectiva si incrementez numarul de aparitii. In caz contrar, adaug o noua celula si stochez informatia.

- Functionalitatea de print:
  Initial, generez TH cu elementele stocate anterior in lista auxiliara.
  -> Generarea TH
     Tabela va contine un vector cu un numar de elemente "M" (egal cu numarul de litere din alfabet), numarul "M" si (pointer la) functia care intoarce codul hash (corespunzator fiecarui element pe care vrem sa il inseram in TH). Generarea tabelei presupune: initializarea si alocarea de memorie pentru aceste elemente + inserarea fiecarui cuvant din lista auxiliara in TH. Aloc memorie pentru TH si pentru vectorul "v" din TH (care are dimensiunea a "M" liste generice).
     Pentru inserare, este parcursa lista auxiliara, fiecarui cuvant fiindu-i atribuita o valoare corespunzatoare codificarii hash (in acest caz, pozitia in alfabet a initialei cuvantului). Valoarea/codul hash reprezinta pozitia din vectorul "v" al TH la care se afla lista "L1", in care va fi inserata informatia despre element. Elementele aceastei liste "L1" vor contine 2 informatii: o lungime si o alta lista "L2", ale carei elemente retin cuvintele (de acea lungime) si numarul de aparitii ale acestora.
     Initial, informatia elementului curent (din lista auxiliara) este pasata functiei "InsL1". Daca exista deja o celula pentru lungimea cuvantului curent (CAZ 2), informatia este trimisa mai departe functiei "InsL2" - deoarece nu este necesara crearea unui element nou in lista "L1", ci doar inserarea cuvantului si a aparitiilor sale in lista "L2" a celulei respective. In caz contrar (atat pentru o lista initial nula - CAZ 1, cat si pentru una nenula - CAZ 3) aloc memorie pentru o noua celula "aux", si stochez informatia: lungimea cuvantului curent + cuvantul si aparitiile acestuia, pastrate in lista "L2". Atat inserarea in "L2" cat si cea in "L1" respecta ordinea elementelor descrisa in enunt.

  -> Printarea TH
    Urmatorul pas este sa verific daca printarea este conditionata - adica daca gasesc parametrii de printare pe linia cu instructiunea "print"
    Daca nu exista, se face printarea standard a TH care foloseste 2 functii specifice de printare element: una pentru "L1" ("afiseazaL1") - care afiseaza lungimea si lista de cuvinte "L2", si una pentru aceasta lista "L2" ("afiseazaL2") - care afiseaza cuvantul si numarul de aparitii.
    Daca exista un singur parametru, acesta este frecventa maxima a cuvintelor care vor fi afisate; pentru aceasta afisare parcurg elementele listei "L1" si apelez functia "afiseaza_caz1" care, la randul sau, parcurge lista de cuvinte "L2" si afiseaza doar elementele cu frecventa < frecventa maxima. Pentru afisarea corecta este nevoie, in primul rand, de un semafor "ok_pos" care determina daca trebuie sa afisam sau nu pozitia in vectorul "v" (pozitia se afiseaza doar in cazul in care am gasit un element care respecta conditia de frecventa); tot acest semafor determina daca este nevoie sa se printeze un enter (daca nu a fost printat nimic la pozitia curenta, nu trebuie sa afisam o linie libera). In al doilea rand, semaforul "ok_len" determina daca printam lungimea elementelor, parantezele si virgulele.
    Daca exista 2 parametrii, acestia sunt initiala si lungimea cuvintelor care vor fi afisate. Folosesc un pointer la lista "L1" de la pozitia data (de initiala) in "v", parcurg lista si daca gasesc elementul de lungime egala cu lungimea data, parcurg lista de cuvinte "L2" din interiorul acestuia si afisez cuvintele + aparitiile. (ok_enter este un semafor care determina daca avem nevoie de enter dupa afisare - doar daca am afisat elemente)

  -> Dezalocarea
    Dupa fiecare printare a tabelei, pentru a evita memory leaks, dezaloc memoria TH. Parcurg vectorul "v" si, pentru fiecare element de tip lista "L1", apelez functia "elibL1" pentru a dezaloca informatia din celula, apoi eliberez celula propriu-zisa a listei. 
    In functia "elibL1" eliberez in primul rand informatia celulei din lista "L1". Aceasta presupune dezalocarea listei de cuvinte "L2". Asadar, parcurg lista "L2" si ii dezaloc fiecare celula prin functia "elibL2" (se elibereaza intai memoria informatiei din celula - stringul alocat dinamic ce retine cuvantul - apoi intreaga structura de informatie). Eliberez ulterior celula propriu-zisa a listei "L2"
    Nu in ultimul rand, eliberez vectorul "v" si tabela hash (pe care o reinitializez cu NULL)
    La final, dezaloc si lista auxiliara folosita la citire; parcurg fiecare element al listei, eliberez informatia prin functia "elibL_aux" (care dezaloca stringul alocat dinamic pentru nume, apoi intreaga structura de informatie), eliberand ulterior intreaga celula a listei. 

