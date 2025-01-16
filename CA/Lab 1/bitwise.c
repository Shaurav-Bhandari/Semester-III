#include <stdio.h>
#include <string.h>

int onesComplement(int num) {
    int bitNum = 4; // Default = 4 bits
    for (int i = 0; i < bitNum; i++) {
        num ^= (1 << i); // Invert each bit
    }
    return num;
}

void twosComplement(char *binary) {
    int length = strlen(binary);
    int firstIndex = -1;

    for (int i = length - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            firstIndex = i;
            break;
        }
    }

    if (firstIndex == -1) {
        return; // No '1' found, already zero
    }

    for (int i = firstIndex - 1; i >= 0; i--) {
        binary[i] = (binary[i] == '0') ? '1' : '0';
    }
}

int main() {
    char binaryNum[5]; // 4 bits + null terminator
    printf("Enter 4-bit Binary Number:\n");
    scanf("%s", binaryNum);

    if (strlen(binaryNum) != 4 || strspn(binaryNum, "01") != 4) {
        printf("Invalid input. Please enter a 4-bit binary number.\n");
        return 1;
    }

    int decimalNum = 0;
    for (int i = 0; binaryNum[i] != '\0'; i++) {
        decimalNum = decimalNum * 2 + (binaryNum[i] - '0');
    }

    printf("\nOriginal Binary Number = %s\n", binaryNum);

    // Calculating one's complement
    int onesComp = onesComplement(decimalNum);
    printf("One's complement = ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (onesComp >> i) & 1);
    }
    printf("\n");

    // Calculating 2's complement using the 1's complement value above
    int twosComp = onesComp + 1;
    printf("2's complement = ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (twosComp >> i) & 1);
    }
    printf("\n");

    char longBin[] = "1010110";
    printf("\n2's complement value calculated using the function:\n");
    printf("Original value = %s\n", longBin);
    twosComplement(longBin);
    printf("2's complement = %s\n", longBin);
    printf("This code is run by Shaurav Bhandari...");
    return 0;
}
