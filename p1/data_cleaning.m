%This is the program to delete data with zero core and zero memory
%consumption
OriginTable=readtable("google-cluster-data-1.csv");
length=size(OriginTable);
i=1;
NumOfZero=[];
matOriginTable=table2array(OriginTable);

for i=1:length(1)
    if matOriginTable(i,5)==0&&matOriginTable(i,6)==0%detct the row which meet the requirement of deletion.
           NumOfZero=[NumOfZero i];
    end
end

matOriginTable(NumOfZero,:)=[];%delete the corresponding lines

%Then we output the filtered table, and we renamed each colomn
Time=matOriginTable(:,1);%column1
ParentID=matOriginTable(:,2);%column2
TaskID=matOriginTable(:,3);%column3
JobType=matOriginTable(:,4);%column4
NrmlTaskCores=matOriginTable(:,5);%column5
NrmlTaskMem=matOriginTable(:,6);%column6
TableFiltered=table(Time,ParentID,TaskID,JobType,NrmlTaskCores,NrmlTaskMem);% create and output the table
writetable(TableFiltered,"google-trace-filtered.csv");   
