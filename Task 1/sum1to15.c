#include<stdio.h>

int main()
{
    int i,n=15,sum=0;
    
    for (i=1;i<=n;i++)
    {
        sum+=i;
    }
    printf("The sum from 1 to %d is %d\n\n",n,sum);
    return 0;
}