function cerinta5()

image = './in/images/image2.gif';
A = imread(image);
A = im2double(A);
A = A.* 255;
[m n] = size(A);

% primul grafic
figure(1);

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
s = diag(S);
plot(s);

% al doilea grafic
figure(2);
s_2 = sum(s);

for k = 1:19
  k_2 = 0;
  for i = 1:k
    k_2 = k_2 + s(i);
  endfor
  info_k(k) = k_2 / s_2;
endfor

k = 1:19;
plot(k, info_k);

% al treilea grafic
figure(3);

for k = 1:19
  [A_k S] = cerinta3(image, k);
  app_error = zeros(1, k);
  
  for i = 1:m
    for j = 1:n
      app_error(k) = app_error(k) + (A(i, j) - A_k(i, j))^2;
    endfor
  endfor
  
  app_error(k) = app_error(k) / (m*n);
endfor

k = 1:19;
plot(k, app_error);

% al patrulea grafic
figure(4);

for k = 1:19
  rata(k) = (2*k + 1)/n;
endfor

k = 1:19;
plot(k,rata);

endfunction
