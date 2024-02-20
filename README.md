DOBRE EMILIA ILIANA 315CB

-citesc inputul intr-un string si construiesc un parser pentru a apela corect functiile

-am doua directoare esentiale, initializate ambele drept root, primul este chiar directorul root iar al doilea este cd_dir in  care se insereaza/sterge atunci cand s-a schimbat directorul, pana nu se schimba ramane root cel in care se efectueaza operatiile

-in cod ma voi folosi de 2 arbori auxiliari, unul de fisiere si unul de directori care retin fiecare toate fisiere respectiv directorii din ierarhie, acestia se folosesc la comanda find si se modifica la toate operatiile de inserare


---------TOUCH---------:
-se insereaza in campul de arbori de fisiere al lui root sau cd_dir dar si in all_files pentru a se tine pasul cu toate fisierele introduse

-se insereaza recursiv in arborele de fisiere, si se apeleaza functia de CreateLeaf prima data cand arborele e gol pentru a-l aloca si initializa cu parinte si nume

-inainte de a insera se verifica daca exista deja numele de introdus pentru un alt director sau fisier si se verifica prin Search pt fisier si director, fct recursiva


----------MKDIR----------:

-se insereaza intr-un arbore de directoare normal, stanga dreapta, asadar in functia de inserare se da ca parametru campul de subdirector al directorului curent, pointerii de stanga si dreapta din director raman neschimbati intrucat acestia arata doar copii directorului in care se insereaza, daca acesta face parte dintr-un subdirector (root are mereu stanga dreapta nule)

-se procedeaza la fel ca la touch


----------RM/RMDIR----------:

-functia de stergere pentru fisier si director sunt identice ca algoritm de stergere dintr-un arbore

-prima data caut cu functia Search ce element din arbore trebuie sa sterg

-aflu parintele elementului printr-o functie care parcurge arborele pana este NULL sau se opreste prin break atunci cand da de elementul al carui parinte trebuie sa il aflu
-inainte de break se retine arborele anterior care este de fapt parintele si se returneaza

-acum se trece la stergerea efectiva pe cazuri:
    1)elementul de sters este radacina si are parintele NULL, astfel
    daca este frunza arborele devine NULL, daca are un copil acesta devine noul root, pt 2 copii este la fel ca in cazul in care nu e radacina

    2)nu e radacina si e frunza:
    -se afla ce copil este elementul de sters pentru parinte, drept sau stang pentru a-l face nul

    3)nu e radacina si are un copil
    -se afla ca in cazul 2 ce copil este elementul de sters pentru parinte si astfel parintele nu mai pointeaza catre element ci catre copilul sau

    4)este sau nu radacina si are 2 copii
    -se afla arborele minim din subarborele drept pentru ca elementul de sters se va inlocui in arbore cu minimul acesta, minimul dintre cei mai mari pentru a asigura ca se indeplineste conditia arborelui binar de cautare in continuare
    -in acest moment minimul este duplicat pentru ca se afla inca in subarborele drept asa ca apelez functia de stergere pentru acest subarbore si minim


----------CD----------:

-atunci cand se introduce cd se cauta daca directorul exista in ierarhie si apoi se schimba cd_dir si astfel cand se va introduce orice alta comanda se va modifica cd_dir cu subarborii sai

----------PWD----------:
-functia recursiva afiseaza pana se ajunge la directorul parinte NULL adica root

----------FIND----------:
-aici se folosesc all_dir si all_files care contin toate fisiere si directoarele in arbori binari simpli de cautare
-prima data caut fisierul/directorul in all_files sau all_dir ca sa verific daca exista sau nu
-daca exista se apeleaza functia PWD pe parintele fisierului (find -f) sau director direct ( find -d)

