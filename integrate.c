#include <stdio.h>

int main() {
    int num1, num2, quotient, product;
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    quotient = num1 / num2;
    product = num1 * num2;
    
    printf("Quotient: %d\n", quotient);
    printf("Product: %d\n", product);
    
    return 0;
}
