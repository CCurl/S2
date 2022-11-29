#include <stdio.h>
int isPrime(int x) {
    int d=3;
    while (1) {
        if (x%d==0) { return 0; }
        if ((x/d)<d) { return 1; }
        d += 2;
    }
}

int main() {
    int n=10000000;
    int c=4;
    for (int i = 11; i<n; i+=2) {
        if (isPrime(i)) { ++c; }
    }
    printf("%d primes in %d",c, n);
}