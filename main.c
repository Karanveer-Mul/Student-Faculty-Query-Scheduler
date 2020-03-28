#include<stdio.h>
#include<stdbool.h>
struct querie
{
  int pid;
  int at;
  int bt;
  int rt;
  int wt;
  int tt;
}f[50],s[50],m[100]; //faculty queue, student queue, merged queue

int fc=0,sc=0,mc=0;
int n,time;
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
        printf("Enter a valid arrival time");
        i--;
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
        printf("Enter a valid arrival time");
        i--;
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
      i--;
    }
  }
}

void merged_queue()
{
  int ifc=0,isc=0;
  if(fc!=0 && sc !=0)
  {
    while(ifc<fc && isc<sc)
    {
      if(f[ifc].at == s[isc].at)
      {
        m[mc]=f[ifc];
        ifc++;
        mc++;
        /*
        m[mc]=s[isc];
        isc++;
        mc++;
        */
      }
      else if(f[ifc].at>s[isc].at)
      {
        m[mc]=s[isc];
        isc++;
        mc++;
      }
      else
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

  else if(fc==0)
  {
    while(isc!=sc)
    {
      m[mc]=s[isc];
      isc++;
      mc++;
    }
  }
  else if(sc==0)
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
  int time_quantum,flag=0;
  int left=n;
  bool idle=0;
  printf("\nEnter the time quantum:");
  scanf("%d",&time_quantum);
  for(time=m[0].at,mc=0;left!=0;)
  {
  	
    if(m[mc].rt<=time_quantum && m[mc].rt!=0)
    {
      time += m[mc].rt;
      m[mc].rt = 0;
      idle=1;
      m[mc].wt += time-(m[mc].at+m[mc].bt);
      m[mc].tt += time-(m[mc].at);
      total_waiting_time += m[mc].wt;
      total_turnaround_time += m[mc].tt;
      left--;
      printf("%d",mc);
    }
    else if(m[mc].rt>time_quantum)
    {
      time += time_quantum;
      m[mc].rt -= time_quantum;
      printf("%d",mc);
    }

    if(mc==n-1)
    {
      mc = 0;
    }
    else if(m[mc+1].at<time)
    {
      mc++;
    }
    else if(idle == 1 && m[mc+1].at>time && m[mc-1].rt==0)
    {
      time = m[mc+1].at;
      mc++;
      idle=0;
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
	display();
	printf("\n\n\t***Finished scheduling***");
}
