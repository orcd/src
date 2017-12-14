#include <stdio.h>
 
int main()
{
    int min, row,col,n;
    int max,a[10];
   for(min = a[0][0],row =0;row < n;row++)
   {
for(max = a[row][0],col = 1;col <n;col++)
if(max < a[row][col])
    min = a[row][col];
    if(min > max)
        min = max;
   }
   printf("the mini num of maximum number is %d\n",min);
   return 0;
     }
