#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 20
 
int a[MAXN][MAXN];
int main()
{
    int min;//最小值
    int max;//最大值
    int row,col,n;
    printf("Please intput the order of the matrix:\n");
    scanf("%d",&n);//输入方阵的阶次 
    printf("Please input the elemente of the marix,、\n from a[0][0] to a[%d][%d]:\n",n-1,n-1);
    for(row = 0;row < n; row++)
        for(col = 0;col < n;col++)
            scanf("%d",&a[row]+col);
    for(min = a[row][0], row = 0;row < n;row++)//从每行选出最大数
    {
    for(max = a[row][0], col = 1;col < n;col++)//从row行选出最大数
           if(max < a[row][col])
               max = a[row][col];
    if(min > max)//保存row行最小数
        min = max;
    }
    printf("The minimum number in%d\n",min);
    for(max = a[0][0], row = 0;row < n;row++)//从每行选出最小数
    {
    for(min = a[row][0], col = 1;col < n;col++)//从row行选出最小数
           if(min < a[row][col])
               min = a[row][col];
    if(max > min)//保存row行最大数
        max = min;
    }
    printf("The maximum number in%d\n",max);
    printf("\n Press any key to quit....\n");
return 0;
}

