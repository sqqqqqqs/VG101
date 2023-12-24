%Task 4.2(1) Plot the proportion of tasks per job type in the dataset using a bar figure
Table=readtable("google-trace-filtered.csv");
matTable=table2array(Table);
number=size(matTable);

%initialize each job type's numbers: 
a=0;%job 0's number
b=0;%job 1's number
c=0;%job 2's number
d=0;%job 3's number

%recording each typr's number using a for loop
for i=1:number(1)
      if matTable(i,4)==0
            a=a+1;
      elseif matTable(i,4)==1
            b=b+1;
      elseif matTable(i,4)==2
            c=c+1;
      elseif matTable(i,4)==3
            d=d+1;
      end
end

%initializing the x-axis and y-axis
x=0:3;
y=[a/number(1) b/number(1) c/number(1) d/number(1)];

%print the according bar plot
bar(x,y,0.6,'FaceColor',[0 .8 .8],'EdgeColor',[0 .5 .5],'LineWidth',1)

%adding label on each axis and print the according number on each bar top
barPut=bar(x,y,0.6,'FaceColor',[0 .8 .8],'EdgeColor',[0 .5 .5],'LineWidth',1);
xlabel('Job Type','FontSize',15)
ylabel('proportion of tasks under this type in the dataset','FontSize',10)
ylim([0 1])
xtips1 = barPut(1).XEndPoints;
ytips1 = barPut(1).YEndPoints;
labels1 = string(barPut(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center',...
    'VerticalAlignment','bottom')

%add grid to make a clearer look
grid on
%saveas(fig,'analysis_of_tasks_and_jobs_1.jpg')

%Task 4.2(2)Plot the distribution of jobs with different number of tasks. 

%first use groupcount equation to groupcount the parent ID
ParentIDcount=groupcounts(Table,'ParentID');

%groupcount the number of parentID already counted before
Groupcount=groupcounts(ParentIDcount,'GroupCount');

%change into matrix and take out the x-variable and y-variable
matGroup=table2array(Groupcount);
job_num=matGroup(:,1);
task_num=matGroup(:,2);

%use loglog plot to see more clearly the distribution
loglog(job_num,task_num)

%set the label of each axis correspondingly
xlabel('number of tasks','FontSize',20)
ylabel('number of jobs with this specific task number','FontSize',10)
%saveas(fig,'analysis_of_tasks_and_jobs_2.jpg')








