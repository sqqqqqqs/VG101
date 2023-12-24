%Task 4.4 Plot the number of jobs fluctuation situation in the whole time range using
%line plot

%first get the origin table 
Table=readtable("google-trace-filtered.csv");
matTable=table2array(Table);

%seperate the first and second column
HasRepeat=matTable(:,1:2);

%use unique function to delete the repeated job in the same time
[NoRepeat,ia,ic] = unique(HasRepeat(:,1:2),'rows');
TableNoRepeat=array2table(NoRepeat);

%use groupcount function to count how many different jobs are there in a
%single time
Data=groupcounts(TableNoRepeat,"NoRepeat1");

%plot the according data
plot(Data,"NoRepeat1","GroupCount")

% add label and grid to make the plot clearer
xlabel('time(s)','FontSize',20)
ylabel('number of jobs at that time','FontSize',15)
grid on
%saveas(fig,'analysis_of_workloads.m.jpg')

    
