#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
int main()
{
    int primes[MAX];
    int pc,m,k;
    int N; 

    printf("输入N\n");
    scanf("%d",&N);
    printf("\n the first %d prime numbers are :\n",N);
    primes[0] = 2;
    pc = 1;//已知质数有1个
    m = 3;//测试的数从三开始
    while(pc < N)
    {
        k = 0;
        while(primes[k] * primes[k] <= m)//调整m为下一个质数
            if(m % primes[k] == 0)
            {
        m += 2;//让m取下一个奇数
        k = 1;//不必用2去测试
            }
            else
                k++;//继续用下一个奇数
        primes[pc++] = m;
        m += 2;//除2，以外其余质数都为奇数
    }
    for(k = 0; k < pc;k++)
    printf("%d ",primes[k]);
    printf("\n\n Press any key to quit...\n");
    return 0;

}
