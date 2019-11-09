% Mihai Florian-Bogdan 311CA

function B = GramSchmidt(A)
	% Functia care calculeaza inversa matricii A folosind factorizari Gram-Schmidt
	% Am descompus matricea A in Q*R, unde Q este ortonormala, iar R este superior triunghiulara
  % Am inversat matricea R printr-un algoritm de inversare a matricelor superior triunghiulare
  % Am rezolvat sistemul Q*R*B=In cu solutia B = inv(R) * Q_transpus * In
  
  n = length(A);  
  R = zeros(n);
  Q = zeros(n);
  B = zeros(n);
  v = zeros(n,1);
  
  %aflu R superior triunghiulara si Q ortonormala astfel incat A=Q*R 
  for i = 1:n
    v = A(:,i);
    for (j = 1:i-1)
      R(j,i) = Q(:,j)'*A(:,i);
      v = v-R(j,i)*Q(:,j);
    endfor
    R(i,i) = norm(v);
    Q(:,i) = v/R(i,i);
  endfor
  
  %calculez inversa lui R
  R_inv=R;
  for j = n : -1 : 1
    R_inv(j, j) = 1 / R(j, j);
    for i = j - 1 : -1 : 1
        R_inv(i,j) = -R(i,i+1:j)*R_inv(i+1:j,j)/R(i,i);
    endfor
  endfor

  %rezolvarea sistemului Q*R*B=In
  for i=1:n
    B(:,i) = R_inv*Q'*eye(n)(:,i);
  endfor
  
endfunction
