a=input('','s');
b=input('','s');

a=reverse(a)-'0';
b=reverse(b)-'0';

a_cnt=1;b_cnt=1;res_cnt=1;
carry=0;
res=zeros(1,max(length(a),length(b)));

while a_cnt<= length(a)&& b_cnt<=length(b)
    res(res_cnt)=mod(a(a_cnt)+b(b_cnt)+carry,10);
    carry=floor((a(a_cnt)+b(b_cnt)+carry) / 10);
    a_cnt=a_cnt+1;
    b_cnt=b_cnt+1;
    res_cnt=res_cnt+1;
end

while a_cnt <=length(a)
    res(res_cnt)=mod(a(a_cnt)+carry,10);
    carry=floor((a(a_cnt)+carry)/10);
    a_cnt=a_cnt+1;
    res_cnt=res_cnt+1;
end

while b_cnt <=length(b)
    res(res_cnt)=mod(b(b_cnt)+carry,10);
    carry=floor((b(b_cnt)+carry)/10);
    b_cnt=b_cnt+1;
    res_cnt=res_cnt+1;
end
if carry==1
    res(res_cnt)=1;
end

fprintf('%d',flip(res));
fprintf('\n');


