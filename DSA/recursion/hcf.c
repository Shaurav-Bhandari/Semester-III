#include <stdio.h>
#include <stdlib.h>


int HCF(int x, int y, int i){
    if (i == 0)
    {
        return HCF(x, y, 1);
    }
    if (x < i || i > y)
    {
        return 1;
    }

    if (x % i == 0 && y % i == 0)
    {
        return i * HCF(x/i, y/i, 2);
    }
    return HCF(x,y,++i);
    
    
    
    
}
int main(int argc, char const *argv[])
{
    int a, b;
    printf("Enter the two numbers: ");
    scanf("%d %d", &a, &b);
    int result = HCF(a,b,0);
    printf("The HCF is: %d", result);

    return 0;
}
