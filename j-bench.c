#include <stdio.h>
#include <stdlib.h>

// braindead find divisors algorithm
// - simple to implement in langauges

int main(int argc, char** argv) {
  long pp= argc>1 ? atol(argv[1]) : 2124680;

  // 710 ms (android clang -O3)
  for(long a=2; a<=100; a++) {
    long b=pp-1;
    for(long c=2; c<=b; c++) {
      long r= pp % c;
      if (r==0) { printf("%ld is not prime says %ld\n", pp, c); }
    }
  }
}
