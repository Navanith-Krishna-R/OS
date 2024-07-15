#include <stdio.h>
#include <limits.h>

struct P{
    int id;
    int bt;
    int at;
    int p;
    int wt;
    int tat;
    int rt;
    int st;
    int et;
    int v;
    int b;
};

void main(){
    int n,ct=0;
    float awt=0,atat=0,art=0,tp;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct P p[n];
    struct P temp;
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        p[i].v=0;
        p[i].st=-1;
        printf("Enter Burst Time, Arrival Time and Priority of P%d: ",i+1);
        scanf("%d %d %d",&p[i].bt,&p[i].at,&p[i].p);
        p[i].b=p[i].bt;
    }

    int cf=0, min=INT_MAX,m=0,count=0;
    while(count<n){
        for(int i=0;i<n;i++){
            if(p[i].at<=cf){
                if(p[i].p<min && p[i].v!=1){
                    min=p[i].p;
                    m=i;
                }
            }
        }
        p[m].bt-=1;

        if(p[m].st<0)
        p[m].st=cf;

        cf+=1;
        if(p[m].bt==0){
            p[m].et=cf;
            count++;
            p[m].v=1;
        }
        min=INT_MAX;

    }
    printf("Process\tWaiting Time\tTurn Around Time\tResponse Time\n");

    for(int i=0;i<n;i++){

        p[i].tat=p[i].et-p[i].at;
        p[i].wt=p[i].tat-p[i].b;
        p[i].rt=p[i].st-p[i].at;

        printf("%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].wt,p[i].tat,p[i].rt);
        awt+=p[i].wt;
        atat+=p[i].tat;
        art+=p[i].rt;
    }

    tp=(float)cf/n;
    printf("Average Waiting Time: %.2f\n",awt/n);
    printf("Average Turn Around Time: %.2f\n",atat/n);
    printf("Average Response Time: %.2f\n",art/n);
    printf("Throughput: %.2f",tp);

}