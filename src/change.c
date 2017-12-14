#include <stdio.h>//整数n转换d
#include <string.h>
#include <stdlib.h>
#define M sizeof(unsigned int)*8
int trans(unsigned n,int d,char s[])
{
    static char digits[] = "0123456789ABCDEF";//十六进制的字符
    char buf[M +1];
memset (buf ,0,33);
    memset(s,0,33);
    int j,i = M;
    if(d<2 || d>16)
       {
       s[0] ='\0';//不合理的进制 将S变成'\0';
       printf("error-d");
       return 0;
       }
       buf[i] = '\0';
       do{
       buf[--i] =digits[ n % d];//得出最低位，将对应字符存入数组
       n /= d;
       }while(n);
       for(j = 0,i=0;j<33;j++)
       {
            if (buf[j]!='\0' )
            {
                s[i++]=buf[j];//控制条件将工作数组的字符串复制到S

            }
       }
      return i;
}

int main()
{
    unsigned int num = 0;
    int scale[]= {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,1}; //各个进制
    char str[33];

    unsigned int i;
    puts("Please input a number to translate:");
    scanf("%d",&num);
    printf("The number you input is %d .\n the trandlation retuse ar:\n",num);
    for(i = 0;i < sizeof(scale)/sizeof(scale[0]);i++)
    {
        if(trans(num,scale[i],str))
            printf("%d = %s(%d)\n",num,str,scale[i]);
        else
           printf("%d => (%d) ERROR!\n",num,scale[i]);
    }
    printf("\n Press any key to quit...\n");
    return 0;
}

