#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // (1): sum of squares  : (n(n+1)(2n+1))/6
    // (2): sum from 1 to n : (n(n+1))/2
    // d = (2)^2 - (1)
    //   = (3n^4 + 2n^3 - 3n^2 - 2n)/12

    unsigned int n = 100;
    unsigned int nsquare = n*n;

    int d = 3*(nsquare*nsquare);
    d += 2*(nsquare*n);
    d -= 3*nsquare;
    d -= 2*n;

    d /= 12;

    // 25164150
    printf("d: %d\n", d);
    return 0;
}
