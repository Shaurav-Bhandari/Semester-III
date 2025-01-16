#include <stdio.h>

int binaryToDecimal(char *binary) {
    int decimal = 0;
    for (int i = 0; i < 4; i++) {
        if (binary[i] == '1') {
            decimal += (1 << (3 - i));
        }
    }
    // Handle negative numbers (4-bit signed representation)
    if (binary[0] == '1') {
        decimal -= 16;
    }
    return decimal;
}

int main(int argc, char const *argv[])
{
    char binA[5], binB[5];
    int A, B, result;
    int signA, signB, signResult;
    //get the inputs
    printf("Enter the two 4-bit binary numbers...\n");
    scanf("%4s %4s", binA, binB);
    A = binaryToDecimal(binA);
    B = binaryToDecimal(binB);
    // perform addition
    result = A + B;
    // Extract the sign Bits. In this case the 4th bit
    signA = (A >> 3) & 1;
    signB = (B >> 3) & 1;
    signResult = (result >> 3) & 1;
    if ((signA == signB) && (signB != signResult))
    {
        printf("\nOverflow detected! The result is: %d\n", result);
    }
    else
    {
        printf("\nNo overflow! The result is: %d\n", result);
    }
    printf("The code is run by Shaurav Bhandari...");
    return 0;
}
