a=input('');
if a>=0
disp(4*pi*a^2);
disp((4/3)*pi*a^3);
else
   disp('Invalid input');
end

num=input('');
if num<0|| num>=1000||int64(num)~=num
    disp('Invalid input');
else
    s=mod(num,10);
    num=floor(num/10);
    s=s+mod(num,10);
    num=floor(num/10);
    s=s+mod(num,10);
    disp (s);
end


params=input('');
if params(1)< 0
    params=-params;
end
a=params(1);
b=params(2);
c=params(3);
delta=b^2-4 * a * c;
x1 =(-b-sqrt(delta))/(2*a);
x2 =(-b+sqrt(delta))/(2*a);
disp(x1);
disp(x2);



