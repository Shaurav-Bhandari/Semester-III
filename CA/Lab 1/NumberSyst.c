// Calculate the binary, Hesadecimal, octal and 1's and 2's complement

#include <stdio.h>
#include <conio.h>

void Binary(int num, int bits){
    int k;
    for (int i = bits - 1; i >= 0; i--)
    {
        k = (num >> i) & 1;
        printf("%d", k);
    }
}

int main(int argc, char const *argv[])
{
    int number, bits;
    printf("Enter the number:\n");
    scanf("%d", &number);
    printf("Enter the number of bits for binary representation:\n");
    scanf("%d", &bits);
    printf("The HexaDecimal Equivalent of the given number is %x", number);
    printf("\nThe Octal Equivalent of the given number is: %o", number);
    printf("\nThe binary equivalent of the number is: ");
    Binary(number, bits);
    printf("\nThe 1's complement is: ");
    Binary(-number - 1, bits);
    printf("\nThe 2's complement is: ");
    Binary(-number, bits);
    printf("This code is run by Shaurav Bhandari");
    return 0;
}
