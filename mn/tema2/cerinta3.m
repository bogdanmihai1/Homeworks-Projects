function [A_k S] = cerinta3 (image, k)

A = imread(image);
A = im2double(A);
A = A.* 255;
[m n] = size(A);
u = zeros(1, m);

for i = 1:m
  u(i) = sum(A(i,:));
  u(i) = u(i)./n;
endfor

for i = 1:m
  for j = 1:n
    A(i,j) = A(i,j) - u(i);
  endfor
endfor

Z = A' ./ sqrt(n-1);
[U S V] = svd(Z);
W = zeros(m, k);

for i = 1:m
  for j = 1:k
    W(i, j) = V(i, j);
  endfor
endfor

Y = W'*A;
A_k = W*Y .+ u';
endfunction
