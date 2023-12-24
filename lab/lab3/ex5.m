arr = input('');
fprintf('%d\t', mergesort(arr));
fprintf('\n');

function sorted = mergesort(arr)
    % sort vector arr into ascending order
    if length(arr) <= 1
        sorted = arr;
    else
        mid = floor(length(arr)/2);
        front = mergesort(arr(1:mid));
        back = mergesort(arr(mid + 1:end));
        % ==============
        %   breakpoint
        % ==============
        sorted = merge(front, back);
    end
end

function res = merge(a, b)
    % Given sorted vectors a and b,
    % return sort([a b])
    n = length(a) + length(b);
    res = zeros(1, n);
    a = [a inf]; b = [b inf];
    ia = 1; ib = 1;
    for i = 1:n
        if a(ia) <= b(ib)
            res(i) = a(ia);
            ia = ia + 1;
        else
            res(i) = b(ib);
            ib = ib + 1;
        end
    end
end