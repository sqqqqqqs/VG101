n=input('');
pascal_=zeros(n,n);
for i=1:n
       pascal_(i,1)=1;
       pascal_(i,i)=1;
       for j=2:i-1
           pascal_(i,j)=pascal_(i-1,j-1)+pascal_(i-1,j);
       end
end

for i=1:n
    for j=1:i
        fprintf('%8d',pascal_(i,j));
    end
    fprintf('\n');
end