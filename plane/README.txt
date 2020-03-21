Florian-Bogdan MIHAI
331CA
Tema 2 EGC

Cum se joaca:
	- Miscarea avionului: - avionul se va deplasa catre ultima pozitie inregistrata a mouse-ului
	- Acceleratie: - SPACEBAR
	- Schimbarea perspectivei: - tasta F
	- Jocul se termina daca jucatorul ramane fara vieti sau fara comustibil

Obiectele ce alcatuiesc jocul:
	- Avionul principal: - este alcatuit din doua obiecte (avionul propriu-zis si elicea)
	                              - este format din 20 de cuburi distorsionate
	                              - contine si pilotul, fara parul acestuia care este animat in shader
	                              - se va roti in functie de sensul in care se indreapta
	- Fumul: - este alcatuit din trei cuburi de culoare gri
	               - apare cand avionul accelereaza
	- Norii:  - sunt alcatuiti din 4 cuburi de culoare alb-gri
	            - primul si ultimul cub vor avea aceeasi animatie, iar cele doua cuburi din centru vor avea
	              dimensiuni si animatii putin diferite
	            - mereu vor fi cate doi nori pe ecran
	- Marea: - are forma cilindrica si se roteste continuu
	              - este deformata in shader pentru a creea valuri
	              - este alcatuita din doua cercuri simetrice (reprezentate de cate 9 puncte fiecare)
	                si puncte aleatoare intre cele doua cercuri, care vor reprezenta valurile 
	- Obstacole: - obstacolele sunt reprezentate de avioane de culoare rosie, cu pilot (fara par)
	                     - la coliziunea cu obstacolele, acestea se vor prabusi in mare
	                     - va exista cate un singur obstacol la un moment dat
	                     - viteza obstacolelor va fi proportionala cu dificultatea
	                     - obstacolele au animatia de rotatie, iar in momentul coliziunii aceasta devine mai rapida
	- Combustibil: - este reprezentat in joc de piramide de culoare turcoaz ce se rotesc continuu
	                        - apar mai rar decat obstacolele
	                        - sunt in grupuri de cate 5, avand traiectoria in forma unei elipse

Interfata:
	- Vietile: - sunt reprezentate de avioane albastre, precum cel al jucatorului, dar fara pilot
	              - apar in coltul din stanga sus al ecranului
	              - se rotesc continuu, in jurul fiecarei axe
	- Combustibilul: - este alcatuit din trei dreptunghiuri suprapuse:
	                          - un dreptunghi negru ce reprezinta conturul
	                          - un dreptunghi alb ce reprezinta combustibilul consumat
	                          - un dreptunghi turcoaz ce reprezinta combustibilul avionului
	                          - este situat in coltul din dreapta sus al ecranului

Detalii legate de implementare:
	- jocul contine 14 mesh-uri diferite, dintre care doua folosesc un shader special pentru animatie
	  (marea si parul pilotului)
	- pentru cele doua am implementat o functie noua de render (RenderSeaMesh), care trimite catre
	  shader si timpul, pentru animatii fluide
	- acceleratia se realizeaza prin dublarea parametrului deltaTimeSeconds, in functie de care se fac
	  toate animatiile, mai putin deplasarea obiectelor de tip combustibil (pentru a nu se abuza acceleratia)
	- pentru a obtine pozitia corecta a cursorului, am normalizat rezolutia ecranul (pe axa OY) la dimensiunea
	  jocului
	- combustibilul maxim este 96 (pentru scalarea combustibilului curent din interfata), iar fiecare obiect de tip
	  combustibil va adauga la combustibilul curent 15, cat timp nu depaseste limita superioara
	- elipsa pe care se deplaseaza combustibilul are raza pe OX egala cu 600, iar pe OY egala cu 250,
	  iar coordonatele centrului sunt (500 x,  [100-300] y)
	- coliziunile se fac prin incadrarea intr-un dreptunghi a fiecarui obiect (nu se verifica si axa OZ) si verificarea
	  conditiei de suprapunere
	- la schimbarea perspectivei, obiectele ce alcatuiesc interfata sunt rotite si translatate corespunzator
	- cand un obiect iese din scena, va aparea din nou din dreapta ecranului (mai putin avionul jucatorului)
	- scorul se afiseaza periodic in consola, iar scorul final in momentul in care jucatorul a pierdut
	- animatia din shader va modifica obiectele pe axele ox si oy cu o diferenta de maxim 10% din valorile initiale
	- pentru camera first person am implementat o functie noua in camera (SetFirstPerson)

Bonusuri implementate:
	- Avion realist
	- Pilot
	- Cresterea dificultatii
	- Avionul scoate fum cand accelereaza
	- In momentul coliziunii, obstacolele se prabusesc
