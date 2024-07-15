#include<stdio.h>
#include<limits.h>
struct hole{
    int size;
    int v;
}hole;

struct p{
    int size;
    int d;
}p;

void main(){
    int n1,n2,n,m=-1;

    printf("Enter number of holes: \n");
    scanf("%d",&n1);
    struct hole h[n1];
    printf("Enter hole size: \n");

    for(int i=0;i<n1;i++){
        scanf("%d",&h[i].size);
        h[i].v=-1;
    }

    printf("Enter number of processes: \n");
    scanf("%d",&n2);
    struct p p[n2];
    printf("Enter processes size: \n");
    for(int i=0;i<n2;i++){
        scanf("%d",&p[i]);
        p[i].d=-1;
    }

    for(int i=0;i<n2;i++){
        for(int j=0;j<n1;j++){
            if(p[i].size<=h[j].size && h[j].v==-1){
                p[i].d=1;
                h[j].v=i;
                break;
            }
        }
    }
    printf("\nFirst fit \n");
    for(int i=0;i<n1;i++){
            if(h[i].v==-1){
                printf(" -- ");
            }
            else{
            printf(" P%d ",h[i].v+1);
            }
    }
    printf("\n");
    for(int i=0;i<n2;i++){
        if(p[i].d==-1){
            printf("Process P%d(%d) is unfinished\n",(i+1),p[i].size);
        }
    }

    for(int i=0;i<n1;i++){
        h[i].v=-1;
    }
    for(int i=0;i<n2;i++){
        p[i].d=-1;
    }
    printf("\nBest fit \n");
    for(int i=0;i<n2;i++){
        n=INT_MAX;
        for(int j=0;j<n1;j++){
            if(p[i].size<=h[j].size && h[j].v==-1 && h[j].size<n){
                m=j;
                n=h[j].size;
            }
        }
        if(n!=INT_MAX){
            p[i].d=1;
            h[m].v=i;
        }
    }

    for(int i=0;i<n1;i++){
            if(h[i].v==-1){
                printf(" -- ");
            }
            else{
            printf(" P%d ",h[i].v+1);
            }
    }
    printf("\n");
    for(int i=0;i<n2;i++){
        if(p[i].d==-1){
            printf("Process P%d(%d) is unfinished\n",(i+1),p[i].size);
        }
    }

     for(int i=0;i<n1;i++){
        h[i].v=-1;
    }
    for(int i=0;i<n2;i++){
        p[i].d=-1;
    }
    printf("\nWorst fit \n");
    for(int i=0;i<n2;i++){
        n=-1;
        for(int j=0;j<n1;j++){
            if(h[j].v==-1 && h[j].size>n){
                m=j;
                n=h[j].size;
            }
        }
        if(n!=-1 && p[i].size<=h[m].size){
            p[i].d=1;
            h[m].v=i;
        }
    }

    for(int i=0;i<n1;i++){
            if(h[i].v==-1){
                printf(" -- ");
            }
            else{
            printf(" P%d ",h[i].v+1);
            }
    }
    printf("\n");
    for(int i=0;i<n2;i++){
        if(p[i].d==-1){
            printf("Process P%d(%d) is unfinished\n",(i+1),p[i].size);
        }
    }
}
