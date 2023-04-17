#include <stdio.h>

int main() {
    int dividend, divisor, quotient;
    
    printf("Enter dividend: ");
    scanf("%d", &dividend);
    
    printf("Enter divisor: ");
    scanf("%d", &divisor);
    
    quotient = dividend / divisor;
    
    printf("Quotient: %d", quotient);
    
    return 0;
}
