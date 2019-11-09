% Mihai Florian-Bogdan 311CA

function y = Apartenenta(x, val1, val2)
	% Functia care primeste ca parametrii x, val1, val2 si care calculeaza valoarea functiei membru in punctul x.
	% Stim ca 0 <= x <= 1
  
  %a*val1+b = 0;
  %a*val2+b = 1;
  %a(val2-val1) = 1;
  
  a = 1/(val2-val1);
  b = -a*val1;
  
  if (x < val1)
    y=0;
  endif
  
    if (x >=val1 && x <= val2)
    y = a*x+b;
  endif
  
  if (x > val2)
    y=1;
  endif

endfunction