Task 1
-------
	
	Pentru memorarea unei imagini, am folosit mai multe structuri:
- pixel: contine 3 unsigned char, respectiv intensitatile B, G, R;
- bmp_fileheader: contine file header-ul bmp-ului;
- bmp_infoheader: contine info header-ul bmp-ului;
- bmp_image: contine numele imaginii, file header, info header, pointer catre
	o matrice de pixeli.

	Atunci cand citesc bitmap-ul, il citesc direct invers pentru a avea o reprezentare
corecta in memorie.

	Pentru realizarea task-ului 1, fac o copie imaginii originale dupa care ii schimb
toti pixelii care nu sunt albi (255, 255, 255) in culoarea vruta.

Task 2
-------

	In fisierul utils.c am definit cate o matrice de int de 7x7 pentru fiecare cifra in
parte. Astfel, parcurg bitmap-ul sus->jos, stanga->dreapta si ma folosesc de aceste
matrici pentru a face un match pe o cifra. Un match inseamna ca toti cei 49 de pixeli
din zona scanata arata la fel ca in matricea unei cifre.
	In momentul in care am gasit un match salvez cifra gasita si coordonatele sale
(pixelul din stanga sus) in cate un vector (util la task-ul 3).

Task 3
-------

	Fac o copie imaginii originale si ma folosesc de coordonatele salvate la task-ul 2
pentru a sterge cifrele nedorite din imagine. Fac o copie vectorului de coordonate si
scot cifrele nedorite din vectorul de cifre gasite si din vectorul initial de 
coordonate. Astfel, am ramas cu un vector cu cifrele ramase, un vector cu vechiile 
coordonate si un vector cu noile coordonate. Ma folosesc de acesti vectori pentru a
copia cifrele la noile coordonate astfel: pentu fiecare cifra din vectorul de cifre,
copiez zona de la coordonatele din vectorul de coordonate intiale la coordonatele din
vectorul de coordonate noi dupa care sterg vechea zona.

Task 4
-------

	Am folosit algoritmul de la task-ul 2 dar am introdus si un partial match
(48 de pixeli din zona scanata arata la fel ca in matricea unei cifre).
