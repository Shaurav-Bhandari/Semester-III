#include <iostream>
#include <cmath>
#include <string>

class NonRestoringDivision {
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
    
    // Function to add two binary strings
    std::string binaryAdd(const std::string& a, const std::string& b) {
        std::string result(a.length(), '0');
        int carry = 0;
        
        for (int i = a.length() - 1; i >= 0; i--) {
            int bitA = a[i] - '0';
            int bitB = b[i] - '0';
            int sum = bitA + bitB + carry;
            
            result[i] = (sum % 2) + '0';
            carry = sum / 2;
        }
        
        return result;
    }
    
    // Function to subtract two binary strings (a - b)
    std::string binarySubtract(const std::string& a, const std::string& b) {
        std::string result(a.length(), '0');
        int borrow = 0;
        
        for (int i = a.length() - 1; i >= 0; i--) {
            int bitA = a[i] - '0';
            int bitB = b[i] - '0';
            int diff = bitA - bitB - borrow;
            
            if (diff < 0) {
                diff += 2;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            result[i] = diff + '0';
        }
        
        return result;
    }
    
    // Function to get two's complement
    std::string getTwosComplement(const std::string& binary) {
        std::string onesComplement(binary.length(), '0');
        
        // Get one's complement
        for (size_t i = 0; i < binary.length(); i++) {
            onesComplement[i] = (binary[i] == '0') ? '1' : '0';
        }
        
        // Add 1 to get two's complement
        std::string one(binary.length(), '0');
        one[binary.length() - 1] = '1';
        
        return binaryAdd(onesComplement, one);
    }

public:
    // Function to perform non-restoring division algorithm
    void nonRestoringDivision(unsigned int dividend, unsigned int divisor) {
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
        std::cout << "\nNon-Restoring Division Algorithm Steps:" << std::endl;
        
        // Determine the number of bits in the quotient
        int n = lenA;
        int m = lenB;
        int quotientBits = n - m + 1;
        
        // Initialize A and Q
        std::string A(n, '0');
        std::string Q = binA;
        
        // Create a buffer for the padded divisor
        std::string B(n - m, '0');
        B += binB;
        
        // Create a buffer for the negative of divisor (-B)
        std::string negB = getTwosComplement(B);
        
        std::cout << "\nInitial state:" << std::endl;
        std::cout << "A: " << A << std::endl;
        std::cout << "Q: " << Q << std::endl;
        std::cout << "B: " << B << std::endl;
        std::cout << "-B: " << negB << std::endl;
        
        // Perform division
        for (int i = 0; i < quotientBits; i++) {
            std::cout << "\nStep " << i + 1 << ":" << std::endl;
            
            // Shift A and Q left by 1 bit
            A = A.substr(1) + Q[0];
            Q = Q.substr(1) + "0";
            
            std::cout << "Shift left: A = " << A << ", Q = " << Q << std::endl;
            
            // Check if A is negative (MSB = 1)
            if (A[0] == '1') {
                std::cout << "A is negative, A = A + B" << std::endl;
                A = binaryAdd(A, B);
                Q[Q.length() - 1] = '0';
            } else {
                std::cout << "A is positive, A = A - B" << std::endl;
                A = binarySubtract(A, B);
                Q[Q.length() - 1] = '1';
            }
            
            std::cout << "After operation: A = " << A << ", Q = " << Q << std::endl;
        }
        
        // Final correction step: if A is negative, add B
        if (A[0] == '1') {
            std::cout << "\nFinal correction (A is negative, A = A + B):" << std::endl;
            A = binaryAdd(A, B);
            std::cout << "A = " << A << std::endl;
        }
        
        // Calculate the quotient and remainder
        unsigned int quotient = binaryToDecimal(Q);
        unsigned int remainder = binaryToDecimal(A);
        
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
    
    std::cout << "Non-Restoring Division Algorithm for Unsigned Binary Numbers" << std::endl;
    std::cout << "=========================================================" << std::endl << std::endl;
    
    std::cout << "Enter dividend (decimal): ";
    std::cin >> dividend;
    
    std::cout << "Enter divisor (decimal): ";
    std::cin >> divisor;
    
    NonRestoringDivision divider;
    divider.nonRestoringDivision(dividend, divisor);
    
    return 0;
}