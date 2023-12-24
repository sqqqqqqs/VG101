%Task 4.3(1) Plot the distribution of memory consumption for each job type using a boxplot
Table=readtable("google-trace-filtered.csv");
matTable=table2array(Table);

%seperate the jobtype variable and memory variable from the origin table
Jobtype=matTable(:,4);
Memory=matTable(:,6);

%use these two variables to plot out the boxplot
boxplot(Memory,Jobtype)
xlabel('Job Type','FontSize',15)
ylabel('memory consumption','FontSize',15)
%saveas(fig,'analysis_of_resource_memory.jpg')

%Task 4.3(2) Plot the distribution of CPU consumption

%seperate the core variable from the origin table
Core=matTable(:,5);

%use two variables to plot out the boxplot
boxplot(Core,Jobtype)
xlabel('Job Type','FontSize',15)
ylabel('CPU consumption','FontSize',15)
%saveas(fig,'analysis_of_resource_cpu.jpg')