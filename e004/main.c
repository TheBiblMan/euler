#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

int is_palindromic(long n);

/* finds the largest palindromic number that can be expressed as
 * a product of two three digit numbers. */
int main(int argc, char *argv[]) {
    long int largest = 0;

    for(int x=100; x <= 999; x++) {
        for(int y=100; y <= 999; y++) {
            long int r = x*y;

            if(is_palindromic(r) && r >= largest) {
                largest = r;
            }
        }
    }

    printf("largest found: %ld\n", largest);

    return 0;
}

void check_bounds(long int n, long int l, long int u) {
#if DEBUG
    if(n < l || n > u) {
        char msg[255];
        memset(msg, 0, sizeof(msg));
        sprintf(msg, "number, %ld, is out of bounds %ld to %ld\n", n, l, u);
        fputs(msg, stderr);
        exit(1);
    }
#endif
}

int is_palindromic(long int n) {
    long int max_ucol;
    int l_dig, r_dig;

    if(n < 0) {
        return 0;
    }

    /* n.b: integer(/long int) division here is dependent (specification
     * compliant, I think) on the fact that if an integer division would have
     * had a fractional part (if computed using real floating point types),
     * then the fractional part is discarded, leaving just the divisor.
     * Essentially, all integer divisions will round downwards, towards zero.*/

    max_ucol = 1;

    while(n / max_ucol >= 10) {
        max_ucol *= 10;
    }

    check_bounds(max_ucol, 1, n);

    while(n) {
        /* compute the left most and right most digits of n. */
        l_dig = n/max_ucol;
        r_dig = n%10;

        check_bounds(l_dig, 0, 9);
        check_bounds(r_dig, 0, 9);

        if(l_dig != r_dig) {
            return 0;
        }

        /* n changes each time this loop runs completely: it loses it's
         * first and last digit (may be 0).
         *
         * the two steps to this computation:
         *    n%max_ucol cuts the right most digit
         *    r/10       cuts the left most digit.
         *
         * then we decrease the size of max_ucol by 10^2 due to the
         * two removed columns. */
        n = (n % max_ucol) / 10;
        max_ucol /= 100;
    }

    return 1;
}
