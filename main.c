#include<stdio.h>
#include<stdbool.h>
struct querie
{
  int pid;//process id
  int at;//arrival time of process
  int bt;//burst time of process
  int rt;//remaing time of process
  int wt;//wait time of process
  int tt;//turnaround time of process
}f[1000],s[1000],m[2000]; //faculty queue, student queue, merged queue

int fc=0,sc=0,mc=0;//faculty counter, student counter, merged queue counter
int n,time;//nuber of processes, total time of execution
int total_waiting_time=0,total_turnaround_time=0;

void input()
{
  int type;
  printf("Please enter the number of processes:");
  scanf("%d",&n);
  int i;
  for(i=0;i<n;i++)
  {
    printf("\n\t***Enter 1 for faculty querie and 2 for student querie***\n");
    printf("\nType(1/2):");
    scanf("%d",&type);
    if(type==1)
    {
      f[fc].pid = i;
      printf("\nEnter the arrival time and burst time\n");
      printf("\nFormat for arrival time 0000 hrs (For example 11:45 as 1145)\n");
      printf("\nArrival time:");
      scanf("%d",&f[fc].at);
      if(f[fc].at<1000 || f[fc].at>1200)
      {
        printf("\n\t***Enter a valid arrival time***\n\n");
        i--;//if we decrement i and continue, we are basically letting the user to go back to same iteration of i
        continue;
      }
      printf("\nEnter the amount of burst time(in mins)\n");
      printf("\nBurst time:");
      scanf("%d",&f[fc].bt);
      f[fc].rt=f[fc].bt;
      fc++;
    }
    else if(type==2)
    {
      s[sc].pid = i;
      printf("\nEnter the arrival time and burst time\n");
      printf("\nFormat for arrival time 0000 hrs (For example 11:45 as 1145)\n");
      printf("\nArrival time:");
      scanf("%d",&s[sc].at);
      if(s[sc].at<1000 || s[sc].at>1200)
      {
        printf("\n\t***Enter a valid arrival time***\n\n");
        i--;//if we decrement i and continue, we are basically letting the user to go back to same iteration of i
        continue;
      }
	  printf("\nEnter the amount of burst time(in mins)\n");
      printf("\nBurst time:");
      scanf("%d",&s[sc].bt);
      s[sc].rt=s[sc].bt;
      sc++;
    }
    else {
      printf("\n***Plese enter a valid type for querie***\n");
      i--;//if we decrement i, we are basically letting the user to go back to same iteration of i
    }
  }
}

void merged_queue()
{
  int ifc=0,isc=0;//faculty iterator, student iterator
  if(fc!=0 && sc !=0)
  {
    while(ifc<fc && isc<sc)//since at the end of loop we will have either ifc == fc or isc == sc and neither f[ifc] nor s[isc] will exist and will throw error
    {
      if(f[ifc].at == s[isc].at)
      {
        m[mc]=f[ifc];
        ifc++;
        mc++;
      }
      else if(f[ifc].at>s[isc].at)
      {
        m[mc]=s[isc];
        isc++;
        mc++;
      }
      else if(f[ifc].at<s[isc].at)
      {
        m[mc]=f[ifc];
        ifc++;
        mc++;
      }
    }
    if(fc==ifc)
    {
      while(isc!=sc)
      {
        m[mc]=s[isc];
        isc++;
        mc++;
      }
    }
    else if(sc==isc)
    {
      while(ifc!=fc)
      {
        m[mc]=f[ifc];
        ifc++;
        mc++;
      }
    }
  }

  else if(fc==0)//if no faculty query exists
  {
    while(isc!=sc)
    {
      m[mc]=s[isc];
      isc++;
      mc++;
    }
  }
  else if(sc==0)//if no student query exists
  {
    while(ifc!=fc)
    {
      m[mc]=f[ifc];
      ifc++;
      mc++;
    }
  }
}

void round_robin()
{
  int time_quantum;
  int left=n;//number of unresolved queries left 
  bool idle=0;//CPU idle status
  printf("\nEnter the time quantum:");
  scanf("%d",&time_quantum);
  printf("\n\n\t***Order of execution***\n");
  for(time=m[0].at,mc=0;left!=0;)//loop until no unresolved query is left
  {
  	
    if(m[mc].rt<=time_quantum && m[mc].rt!=0)//if remaining time is less than time quantum
    {
      time += m[mc].rt;
      m[mc].rt = 0;
      idle=1;
      m[mc].wt += time-(m[mc].at+m[mc].bt);
      m[mc].tt += time-(m[mc].at);
      total_waiting_time += m[mc].wt;
      total_turnaround_time += m[mc].tt;
      left--;
      printf("%d ",m[mc].pid);
    }
    else if(m[mc].rt>time_quantum)//if remaining time is greater than time quantum
    {
      time += time_quantum;
      m[mc].rt -= time_quantum;
      printf("%d ",m[mc].pid);
      idle=0;
    }

    if(mc==n-1)//if merged queue counter is at the last process
    {
      mc = 0;
    }
    else if(m[mc+1].at<time)//if next process has already arrived
    {
      mc++;
    }
    else if(idle == 1 && m[mc+1].at>time && m[mc-1].rt==0)//if CPU idle and previous processes have already executed, then jump to next process
    {
      time = m[mc+1].at;
      mc++;
    }
    else
    {
      mc = 0;
    }
  }
}

void display()
{
  int i;
  printf("\nProcess id | Burst Time | Arrival Time | Waiting Time | Turnaround Time\n");
  for(i=0;i<n;i++)
  {
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",m[i].pid,m[i].bt,m[i].at,m[i].wt,m[i].tt);
  }
  printf("\n\n\nTotal time spent:%d", (time-m[mc].at));
  printf("\nAverage waiting time:%d",(total_waiting_time/n));
  printf("\nAverage turnaround time:%d",(total_turnaround_time/n));
}

void main()
{
	input();
	merged_queue();	
	round_robin();
	printf("\n");
	display();
	printf("\n\n\t***Finished scheduling***");
}
