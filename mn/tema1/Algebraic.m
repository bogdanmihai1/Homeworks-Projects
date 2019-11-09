% Mihai Florian-Bogdan 311CA

function R = Algebraic(nume, d)
	% Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
	% Intrari: 
	%	-> nume: numele fisierului in care se scrie;
	%	-> d: probabilitatea ca un anumit utilizator sa continue navigarea la o pagina urmatoare.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.

  n = dlmread (nume)(1,1);
  %data retine datele de intrare: pe prima coloana nodul; pe a doua numarul de legaturi
  %pe urmatoarele linii legaturile
  data = dlmread (nume)(2:n+1,:);

  %matrice de adiacenta
  A = zeros(n);
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
  
  %calculul matricei M
  M = zeros(n,n);
  for i = 1:n
    for j = 1:n
      if (A(i,j) == 1)
        M(j,i) = 1/data(i,2);
      endif
    endfor
  endfor
  
  %aplic formula pentru R
  R = GramSchmidt(eye(n) - d.*M)*(1-d)*(1/n)*ones(n,1);
  
endfunction