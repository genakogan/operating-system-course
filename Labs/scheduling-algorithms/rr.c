#include<stdio.h>
int main(void){
    int i,j,n=3,wa[10],tat[10],t=1,ct[10],max;  
    float wt_sum=0,tat_sum=0,temp=0;
    int  bt[] = {3,4,3};  

    for(i=0;i<n;i++)
    {
        ct[i]=bt[i];
    }
    max=bt[0];
    for(i=1;i<n;i++)
    if(max<bt[i])
	    max=bt[i];

    for(j=0;j<(max/t)+1;j++)
        for(i=0;i<n;i++)
            if(bt[i]!=0)
            if(bt[i]<=t)
            {
	            tat[i]=temp+bt[i];
	            temp=temp+bt[i];
	            bt[i]=0;
            }
            else
            {
	            bt[i]=bt[i]-t;
	            temp=temp+t;
            }
    for(i=0;i<n;i++)
    {
	    wa[i]=tat[i]-ct[i];
	    tat_sum+=tat[i];
	    wt_sum+=wa[i];
    }
    printf("\n\tPROCESS\t BURST TIME \t WAITING TIME\tTURNAROUND TIME\n");
    for(i=0;i<n;i++)
    printf("\t%d \t %d \t\t %d \t\t %d \n",i+1,ct[i],wa[i],tat[i]);
    printf("\nThe Average Waiting time is -- %f ",wt_sum/n);

    printf("\nThe Average Turnaround time is -- %f\n",tat_sum/n);

}
