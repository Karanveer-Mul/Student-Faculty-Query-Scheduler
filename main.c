#include<stdio.h>

struct querie
{
  int pid;
  int at;
  int bt;
  int rt;
  int wt;
  int tt;
};f[50],s[50],m[100] //faculty queue, student queue, merged queue

int fc=0,sc=0,mc=0;
int n;
int total_waiting_time=0,total_turnaround_time=0;

void input()
{
  int type;
  printf("/nEnter the number of processes:");
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  {
    printf("Enter 1 for faculty querie and 2 for student querie:");
    scanf("%d",&type);
    if(type==1)
    {
      f[fc].pid = i;
      printf("\nEnter the arrival time and burst time\n");
      printf("\nFormat for arrival time 0000 hrs (For example 11:45 as 1145)\n");
      printf("\nArrival time:");
      scanf("%d",&f[fc].at);
      if(f[fc].at<1000 || f[fc]>1200)
      {
        printf("Enter a valid arrival time");
        i--;
        continue;
      }
      else
      {
        f[fc].at = f[fc].at - 1000;
      }
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
      if(s[sc].at<1000 || s[sc]>1200)
      {
        printf("Enter a valid arrival time");
        i--;
        continue;
      }

      printf("\nBurst time:");
      scanf("%d",&s[sc].bt);
      s[sc].rt=s[sc].bt;
      sc++;
    }
    else {
      printf("Plese enter a valid type for querie")
      i--;
    }
  }
}

void merged_queue()
{
  int ifc=0,isc=0;
  if(fc!=0 && sc !=0)
  {
    while(ifc<=fc && isc<=sc)
    {
      if(f[ifc].at == s[isc].at)
      {
        m[mc]=f[ifc];
        ifc++;
        mc++;
        m[mc]=s[isc];
        isc++;
        mc++;
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
    else if(fc==(ifc-1))
    {
      while(isc!=sc)
      {
        m[mc]=s[isc];
        isc++;
        mc++;
      }
    }
    else if(sc==(isc-1))
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
  int time_quantum,time,flag=0;
  int left=n;
  printf("\nEnter the time quantum:")
  scanf("%d",&time_quantum);
  for(time=0,mc=0;left!=0;)
  {
    if(m[mc].rt<=time_quantum && m[mc].rt!=0)
    {
      time += m[mc]rt;
      m[mc].rt = 0;
      flag = 1;
    }
    else if(m[mc].rt>time_quantum)
    {
      time += time_quantum;
      m[mc].rt -= time_quantum;
    }
    if(m[mc].rt==0 && flag==1)
    {
      m[mc].wt += time-(m[mc].at+m[mc].bt);
      m[mc].tt += time-(m[mc].at);
      total_waiting_time += m[mc].wt;
      total_turnaround_time += m[mc].tt;
      flag=0;
      left--;
    }

    if(mc==n-1)
    {
      mc = 0;
    }
    else if(m[mc+1].at<time)
    {
      mc++;
    }
    else
    {
      mc = 0;
    }
  }
}
