#include <iostream>
#include <cmath>
#include <cstring>
#include <string>

class RestoringDivision {
private:
    // Function to convert decimal to binary string
    std::string decimalToBinary(unsigned int n, int* length) {
        if (n == 0) {
            *length = 1;
            return "0";
        }
        
        // Find number of bits needed
        int bits = static_cast<int>(log2(n)) + 1;
        *length = bits;
        
        // Create binary string
        std::string binary(bits, '0');
        
        // Convert to binary
        for (int i = bits - 1; i >= 0; i--) {
            binary[bits - i - 1] = (n & (1 << i)) ? '1' : '0';
        }
        
        return binary;
    }

    // Function to convert binary string to decimal
    unsigned int binaryToDecimal(const std::string& binary) {
        unsigned int decimal = 0;
        int length = binary.length();
        
        for (int i = 0; i < length; i++) {
            if (binary[i] == '1') {
                decimal += static_cast<unsigned int>(pow(2, length - i - 1));
            }
        }
        
        return decimal;
    }

public:
    // Function to perform restoring division algorithm
    void restoringDivision(unsigned int dividend, unsigned int divisor) {
        if (divisor == 0) {
            std::cout << "Error: Division by zero is not allowed." << std::endl;
            return;
        }
        
        if (dividend < divisor) {
            std::cout << "Quotient: 0 (Binary: 0)" << std::endl;
            int lenD;
            std::string binD = decimalToBinary(dividend, &lenD);
            std::cout << "Remainder: " << dividend << " (Binary: " << binD << ")" << std::endl;
            return;
        }
        
        // Convert to binary
        int lenA, lenB;
        std::string binA = decimalToBinary(dividend, &lenA);
        std::string binB = decimalToBinary(divisor, &lenB);
        
        std::cout << "Dividend (A): " << dividend << " (Binary: " << binA << ")" << std::endl;
        std::cout << "Divisor (B): " << divisor << " (Binary: " << binB << ")" << std::endl;
        std::cout << "\nRestoring Division Algorithm Steps:" << std::endl;
        
        // Determine the number of bits in the quotient
        int n = lenA;
        int m = lenB;
        int quotientBits = n - m + 1;
        
        // Initialize A and Q
        std::string A(n, '0');
        std::string Q(quotientBits, '0');
        
        // Create a buffer for the padded divisor
        std::string paddedB(n - m, '0');
        paddedB += binB;
        
        // Create a buffer for the full dividend
        std::string fullA = binA;
        
        std::cout << "\nInitial state:" << std::endl;
        std::cout << "A: " << A << std::endl;
        std::cout << "Q: " << fullA << std::endl;
        std::cout << "B: " << paddedB << std::endl;
        
        // Perform division
        for (int i = 0; i < quotientBits; i++) {
            // Shift A and Q left by 1 bit
            for (int j = 0; j < n - 1; j++) {
                A[j] = A[j + 1];
            }
            A[n - 1] = fullA[i];
            
            std::cout << "\nStep " << i + 1 << ":" << std::endl;
            std::cout << "Shift left: A = " << A << ", Q = " << fullA.substr(i + 1) << std::endl;
            
            // Subtract B from A
            int borrow = 0;
            std::string tempA(n, '0');
            
            for (int j = n - 1; j >= 0; j--) {
                int bitA = A[j] - '0';
                int bitB = paddedB[j] - '0';
                int diff = bitA - bitB - borrow;
                
                if (diff < 0) {
                    diff += 2;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                
                tempA[j] = diff + '0';
            }
            
            std::cout << "A - B = " << tempA << std::endl;
            
            // Check if A is negative (we use the borrow flag)
            if (borrow == 1) {
                // Restoring: A = A + B
                std::cout << "A is negative, restoring A = A + B" << std::endl;
                int carry = 0;
                for (int j = n - 1; j >= 0; j--) {
                    int bitA = tempA[j] - '0';
                    int bitB = paddedB[j] - '0';
                    int sum = bitA + bitB + carry;
                    
                    if (sum > 1) {
                        sum -= 2;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    
                    A[j] = sum + '0';
                }
                Q[i] = '0';
            } else {
                // A is positive, keep the result
                A = tempA;
                Q[i] = '1';
            }
            
            std::cout << "A: " << A << ", Q: " << Q << std::endl;
        }
        
        // Calculate the remainder (in A)
        unsigned int remainder = binaryToDecimal(A);
        unsigned int quotient = binaryToDecimal(Q);
        
        std::cout << "\nFinal Result:" << std::endl;
        std::cout << "Quotient: " << quotient << " (Binary: " << Q << ")" << std::endl;
        std::cout << "Remainder: " << remainder << " (Binary: " << A << ")" << std::endl;
        
        std::cout << "\nExpected outcome: " << dividend << " ÷ " << divisor 
                  << " = " << dividend / divisor << " with remainder " << dividend % divisor << std::endl;
        std::cout << "Observed outcome: " << dividend << " ÷ " << divisor 
                  << " = " << quotient << " with remainder " << remainder << std::endl;
    }
};

int main() {
    unsigned int dividend, divisor;
    
    std::cout << "Restoring Division Algorithm for Unsigned Binary Numbers" << std::endl;
    std::cout << "======================================================" << std::endl << std::endl;
    
    std::cout << "Enter dividend (decimal): ";
    std::cin >> dividend;
    
    std::cout << "Enter divisor (decimal): ";
    std::cin >> divisor;
    
    RestoringDivision divider;
    divider.restoringDivision(dividend, divisor);
    
    return 0;
}