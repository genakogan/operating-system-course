#include <stdio.h>

int main(void){
    int wt[20], tat[20], i, k, n = 3, temp;
    float wt_sum,tat_sum ;
    int p[] = {0,1,2}; // processses
    int bt[] = {24,3,3}; //burst time
    wt_sum = wt[0] = 0; // wt for first process
    tat_sum = tat[0] =bt[0]; 
    
    for(i = 1; i<n; i++){
        wt[i] = wt[i-1] + bt[i-1]; // wait time current proc = bt-wt (prev proc)
        tat[i] = tat[i-1] +bt[i]; // tat = tat prev + current bt
        wt_sum = wt_sum + wt[i];
        tat_sum = tat_sum + tat[i];
        
    }
    printf("\nprocess\t\tburst time\twaiting time\tturn around time");
    for(i = 0; i<n;i++)
        printf("\n%d \t\t %d \t\t %d \t\t %d \t\t", p[i], bt[i], wt[i],tat[i]);
    printf("\n Average Waiting Time is -- %f", wt_sum/n);
    printf("\n Average Turnaround Time is -- %f", tat_sum/n);
    

    return 0;
}
