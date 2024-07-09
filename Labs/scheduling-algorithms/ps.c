#include <stdio.h>

int main(void){
    int wt[20], tat[20], i, n = 4, temp;
    float wt_sum,tat_sum;    
    int p[] = {0,1,2,3,4}; 
    int bt[] = {10,1,2,1,5};
    int pri[] = {3,1,4,5,2};
    wt_sum = wt[0] = 0; // wt for first process
    tat_sum = tat[0] =bt[0]; 
    
    for(i=0;i<n;i++){
        for(int k=i+1;k<n;k++){
            if(pri[i]> pri[k]){
                // sort processes array
                temp=p[i];
                p[i] = p[k];
                p[k] = temp;
                
                // sort burts time array
                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;  
                
                // sort proirity arr
                temp = pri[i];
                pri[i] = pri[k];
                pri[k] = temp;
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
        printf("\n%d \t\t %d \t\t %d \t\t %d \t\t %d \t\t", p[i], pri[i], bt[i], wt[i],tat[i]);
    printf("\n Average Waiting Time is -- %f", wt_sum/n);
    printf("\n Average Turnaround Time is -- %f", tat_sum/n);
    

    return 0;
}
