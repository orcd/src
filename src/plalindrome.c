#include <stdio.h>
#include <stdlib.h>


int circle(int n,int d)
{
int s=0;int m = n;
while(m)
{
    s=s*d+m%d;
    m /= d;
}
return s == n;
}

int num[]={232,27,815};
int scale[] = {2,10,16};

int main()
{
    int i,j;
    for(i =0;i < sizeof(num)/sizeof(num[0]);i++)
      for(j =0;j < sizeof(scale)/sizeof(scale[0]);j++)
          if(circle(num[i],scale[j]))
              printf("%d ->(%d) is a circle number !\n",num[i],scale[j]);
         else
              printf("%d ->(%d) is not a circle number !\n",num[i],scale[j]);
printf("exit");
return 0;
}
