#include <stdio.h>
#include <limits.h>

struct P{
    int id;
    float et;
    int tp;
    int v;
    int b;
};
int gcd(int a, int b){
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int findlcm(int arr[], int n)
{
    int ans = arr[0];
 
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /(gcd(arr[i], ans)));
 
    return ans;
}
void main(){
    int n,ct=0,f=0;
    float awt=0,atat=0,art=0,tp;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct P p[n];
    struct P temp;
    int a[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        p[i].v=0;
        printf("Enter Excecution Time and Time Period of P%d: ",i+1);
        scanf("%f %d",&p[i].et,&p[i].tp);
        p[i].b=p[i].et;
        a[i]=p[i].tp;
    }

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].tp>p[j].tp){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    int ans=findlcm(a,n);

    for(int i=0;i<ans;i++){
        f=0;
        for(int j = 0;j<n;j++){
            if (i%p[j].tp==0) {
                p[j].v=0;
                p[j].et=p[j].b;
            }
        }
            for(int j=0;j<n;j++){
                if(p[j].v==0){
                    f=1;
                    p[j].et-=1;
                    printf("%d to %d P%d\n",i,i+1,p[j].id);
                    if(p[j].et==0){
                        p[j].v=1;
                    }
                    break;
                }
            }

            if(f==0){
                printf("%d to %d -\n",i,i+1);
            }
        }
    }


