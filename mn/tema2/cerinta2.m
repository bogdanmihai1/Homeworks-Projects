function cerinta2 ()
image = './in/images/image2.gif';
A = imread(image);
[m n] = size(A);
[U S V] = svd(A);

% primul grafic
for i = 1:min(m,n)
  s(i) = S(i, i);
endfor
figure(1);
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
  A_k = cerinta1(image, k);
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
  rata(k) = (m*k + n*k + k)/(m*n);
endfor

k = 1:19;
plot(k,rata);

endfunction
