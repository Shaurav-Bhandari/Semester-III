#include <stdio.h>
long int multNum(int n) {
    if (n <= 1)
    {
        return 1;   
    }
    else
    {
        return n*multNum(n-1);
    }
    
}

int Fact(int n, int fact) {
    if (n ==1)
    {
        return fact;    
    }
    else
    {
        return Fact(n-1, n*fact);
    }
    
}


int main(int argc, char const *argv[])
{
    int x = 0;
    printf("Enter the number");
    scanf("%d", &x);
    long int res = multNum(x);
    int result = Fact(x, 1);
    printf("NO tail recursion: %d\n", res);
    printf("tail res %d", result);
    return 0;
}
