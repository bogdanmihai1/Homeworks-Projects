function A_k = cerinta1 (image, k)
A = imread(image);
[m n] = size(A);
A_k = zeros(m,n);
[U S V] = svd(A);
U_k = zeros(m, k);
S_k = zeros(k, k);
V_k = zeros(n, k);
for i = 1:m
  for j = 1:k
    U_k(i, j) = U(i, j);
  endfor
endfor
for i = 1:k
  for j = 1:k
    S_k(i, j) = S(i, j);
  endfor
endfor
for i = 1:n
  for j = 1:k
    V_k(i, j) = V(i, j);
  endfor
endfor
A_k = U_k*S_k*V_k';
endfunction
