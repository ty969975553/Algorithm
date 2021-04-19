#include"stdio.h"
int main(){
    int a[10]={-1,3,5,7,-9,-2,-4,6,-8,1};
    int i,j=0,temp;
    for(i=0;i<10;i++){
        temp=a[j];
        if(a[i]<0){
            a[j]=a[i];
            a[i]=temp;
            j++;
        }
    }
    for(i=0;i<10;i++)
        printf("%d\t",a[i]);
    return 0;
}