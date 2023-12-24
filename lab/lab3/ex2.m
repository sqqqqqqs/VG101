n=input('');
move_hanoi(n,1,2,3);

function move_hanoi(n, source_rod, aux_rod, target_rod)
    % Move n disks recursively from source_rod to target_rod.
    % (source_rod, aux_rod, target_rod) is a permutation of {1, 2, 3}.
    % Base case: n = 1.

    if n==1
     fprintf("%d -> %d\n",source_rod,target_rod);
     return
    end
    move_hanoi(n-1,source_rod, target_rod, aux_rod);
    
    fprintf("%d -> %d\n",source_rod,target_rod);
    
    move_hanoi(n-1,aux_rod,source_rod, target_rod);
end