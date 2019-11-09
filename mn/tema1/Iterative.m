% Mihai Florian-Bogdan 311CA

function R = Iterative(nume, d, eps)
	% Functia care calculeaza matricea R folosind algoritmul iterativ.
	% Intrari:
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
	%	-> eps: eroarea care apare in algoritm.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.
	%data=load('-ascii','graf1');
  
  %maxiter este numarul maxim de iteratii dupa care se opreste functia
  maxiter = 10000;
  n = dlmread (nume)(1,1);
  %data retine datele de intrare: pe prima coloana nodul; pe a doua numarul de legaturi
  %pe urmatoarele linii legaturile
  data = dlmread (nume)(2:n+1,:);
  A = zeros(n);
  
  %matrice de adiacenta
  for i = 1:n
     j = data(i,2);
     for k = 3:j+2
       A(i,data(i,k)) = 1;
     endfor
  endfor
  
  %verific daca nodul i are link catre el insusi si sterg linkul din A
  for i = 1:n
    if (A(i,i) == 1)
        A(i,i) = 0;
        data(i,2)--;
    endif
  endfor
  
  R = zeros(n,1); 
  
  %R la pasul 0
  for i = 1:n
    R(i) = 1/n;
  endfor
  
  %R1 = R la pasul urmator
  R1 = R;
  unu = ones(n,1);
  M = zeros(n,n);
  
  %calculul matricei M
  for k = 1:n
    for i = 1:n
      if (A(k,i) == 1)
        M(i,k) = 1/data(k,2);
      endif
    endfor
  endfor
  
  while (maxiter > 0)  
    maxiter--;
    %aplic formula  
    R1 = d*M*R+(1-d)/n*unu;
    
    %verific conditia de oprire    
    if (max(abs(R1-R)) < eps)
      break;
    endif
    
    R = R1;
    
  endwhile
  
endfunction