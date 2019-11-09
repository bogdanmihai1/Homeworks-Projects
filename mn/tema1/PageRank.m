% Mihai Florian-Bogdan 311CA

function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out
  
  %citire date
  n = dlmread (nume)(1,1);
  val1=dlmread (nume)(n+2,1);
  val2=dlmread (nume)(n+3,1);
  
  %crearea fisierului de iesire
	name_out = strcat(nume,'.out');
  file = fopen(name_out,'w');
  
  fprintf(file, '%d\n', n);
  
  %afisare task1 si task2
  task1=Iterative(nume, d, eps);
  task2=Algebraic(nume,d);
  fprintf(file, '%.6f\n', task1);
  fprintf(file, '\n');
  fprintf(file, '%.6f\n', task2);
  fprintf(file, '\n');
  
  [PR1,I]=sort(task2,'descend');
  
  %sort nu inversa la graf1 doua valori egale, iar in graf1.ref erau inversate
  for i = 1:n-1
    if (abs(PR1(i) - PR1(i+1)) < 0.0000001)
      [I(i+1) I(i)] = deal(I(i),I(i+1));
    endif
  endfor
  
  %afisare task3
  for i = 1:n
    ap = Apartenenta(PR1(i), val1, val2);
    fprintf(file, '%d %d %.6f\n', i, I(i), ap);
  endfor
  
  %valorile de iesire ale functiei
  R1 = task1;
  R2 = task2;
  
  fclose(name_out);
  
endfunction