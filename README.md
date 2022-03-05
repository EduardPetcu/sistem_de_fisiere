Eduard Petcu

=============================

1. touch
Timp aproximativ de implementare: 1-2 h.
Functia primeste ca parametru numele fisierului si verifica daca acesta
se regaseste in lista de fisiere a directorului curent, caz in care afiseaza
un mesaj corespunzator. In caz contraar, se insereaza fisierul creat la
finalul listei de fisiere si i se aloca memorie prin intermediul functiei
initFile.

2. mkdir
Timp aproximativ de implementare : 35 min
Asemenea ca pentru functia touch, functia mkdir primeste ca parametru numele
directorului si verifica daca acesta se regaseste in lista de directoare
a directorului parent, caz in care programul afiseaza un mesaj corespunzator.
In caz contraar, se creeaza directorul la finalul listei de directoare si i
se aloca memorie prin intermediul functiei initDir.

3. ls
Timp aproximativ de implementare : 25 min
Functia nu primeste niciun parametru de la tastatura. 
Se parcurg listele de directoare si fisiere ale directorului parent
si se afiseaza numele acestora.

4. rm
Timp aproximativ de implementare : 1 h
Functia primeste ca parametru numele fisierului.
Se verifica daca exista fisierul dat in lista de fisiere, si in cazul
in care este gasit se elimina legaturile cu vecinii acestuia si se 
elibereaza memoria alocata. In caz contraar , se afiseaza in consola
un mesaj corespunzator. 

5. rmdir
Timp aproximativ de implementare : 2 h
Functia primeste ca parametru numele directorului.
Se verifica daca exista directorul dat in lista de directoare. Daca
se gaseste, se elimina legaturile cu vecinii acestuia si se elibereaza
memoria alocata prin intermediul functiei freeDir. In caz contraar, se
afiseaza un mesaj corespunzator. 
Functia freeDir elibereaza memoria in mod recursiv in toate subdirectoarele
directorului parinte.

6. cd
Timp aproximativ de implementare : 30 min
Functia primeste ca parametru numele directorului nou.
Daca numele directorului dat este ".." , directorul curent devine
directorul parinte. Altfel, cauta in lista de directoare si se schimba
cu directorul respectiv. In cazul in care nu este gasit, se afiseaza un
mesaj corespunzator.

7. tree
Timp aproximativ de implementare : 40 min
Functia nu primeste parametri de la tastatura, insa este apelata
in main cu parametrii "tree(dirCurent,0)" unde dirCurent este directorul
in care vrem sa vedem interiorul acestuia sub o forma arborescenta, iar 0
este level-ul initial de la care porneste functia. Functia se apeleaza 
recursiv pentru fiecare director gasit cu level-ul incrementat pentru a
sti numarul de spatii necesare de inserat. Aceste spatii se afiseaza prin
intermediul functiei "afisareSpatii".

8. pwd
Timp aproximativ de implementare : 2 h
Functia nu primeste parametri de la tastatura. Pentru aceasta functie
am implementat o stiva in care am retinut numele tuturor directoarelor
parcurse din parinte in parinte. 
Am alocat memorie atat pentru stiva cat si pentru calea creata. 
Am concatenat toate numele directoarelor si am returnat calea.

9. stop
Functia stop elibereaza memoria din directorul radacina in mod recursiv
folosind functia freeDir si iese din while-ul de comenzi.

10. mv
Timp aproximativ de implementare : 16 h
Functia primeste ca parametri numele vechiului director/fisier si numele nou.
In cazul in care se gaseste directorul/fisierul cu acelasi nume ca si 
primul parametru dat functiei si nu exista un alt director/fisier cu 
acelasi nume ca si noul nume (newname) atunci se creeaza un nou
fisier/director cu noul nume si se sterge vechiul fisier/director. 
In cazul in care schimbam numele unui director, se vor reconstrui legaturile 
cu fiii vechiului director inainte de stergerea acestuia. 
Daca numele noului fisier/director exista deja in lista de fisiere/directoare
sau daca vechiul nume nu exista se va afisa un mesaj corespunzator.

