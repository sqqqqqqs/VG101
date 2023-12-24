
A=input('');
if numel(A)<6
    disp('Invalid input');
else
   A(4:6)=[0 1 2];
    disp(A);
end

A=input('');
disp(A(2:5, 3:6));


n=input('');
A = reshape(1:n^2, n, n)';
disp(A);
