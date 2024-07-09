#include <stdio.h>

int main(void){
    int wt[20], tat[20], i, n = 4, temp;
    float wt_sum,tat_sum ;
    //int p[] = {0,1,2}; // processses
    //int bt[] = {24,3,3}; //burst time
    
    int p[] = {0,1,2,3}; 
    int bt[] = {6,8,7,3};
    wt_sum = wt[0] = 0; // wt for first process
    tat_sum = tat[0] =bt[0]; 
    
    /* for sjf shortest job first */
    for(i=0;i<n;i++){
        for(int k=i+1;k<n;k++){
            if(bt[i]> bt[k]){
                // sort processes array
                temp=p[i];
                p[i] = p[k];
                p[k] = temp;
                
                // sort burts time array
                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;    
             }  
        
        } 
    }
    /*===============================================*/
    
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
