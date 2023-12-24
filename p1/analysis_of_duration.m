%Task 4.5 Plot the distribution of tasks with respect to it duration time, using a line
%plot.

%get data from the origin excel
Table=readtable("google-trace-filtered.csv");
matTable=table2array(Table);

%get the first and third column and sortrow them
Column1and3=matTable(:,1:2:3);
AfterSort=sortrows(Column1and3,2);
TableSorted=array2table(AfterSort);

%groupcount the task according to the time
Q=groupcounts(TableSorted,'AfterSort2');
Q2=table2array(Q);

%use the num of consecutive time duration minus 1 times 300 to get duration
%time for each task
Q2(:,2)=(Q2(:,2)-1).*300;
Q3=array2table(Q2);

%count how much tasks are there in one kinds of time duration
Q4=groupcounts(Q3,'Q22');

%use loglog to better print a more clearer picture
loglog(Q4,"Q22",'GroupCount')

%add labels to make theplot clearer
xlabel('duration time(s)','FontSize',20)
ylabel('number of tasks with this duration time','FontSize',10)
%saveas(fig,'analysis_of_duration.jpg')