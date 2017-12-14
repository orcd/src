#include <stdio.h>
 
int a[] = {1,2,3,5,6,7,8,9,10,11,12,13,14,15};
int main()
{
    int i = 0;
    printf("\n The arry is:\n");
    for(i = 0;i < sizeof(a)/sizeof(a[0]);i++)
        printf(" %d ",a[i]);
    printf("SUM of thearry is :%d\n",sum(a,sizeof(a)/sizeof(a[0])));
    printf("exit");
}

sum(int a[],int n)
{
    if(n<=0)
        return 0;
    return  a[n-1]+sum(a,n-1);
}
