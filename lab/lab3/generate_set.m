n=input('');
disp(generate_set([n]));

function result = generate_set(current_list)
    % Return the number of lists that ends with current_list.
    result = 1;
    if current_list(1)==1
        return;  % base case, recursion ends here
    end
    for i=1:floor(current_list(1)/2)
        %all positive integers i less than or equal to current_list(1)/2
        new_list=[i,current_list];
        result=generate_set(new_list)+result;
    end
end