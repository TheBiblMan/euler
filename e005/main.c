#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_BITS (8 * sizeof(unsigned int))

static inline void bit_set(unsigned int *bitarray, size_t idx) {
    bitarray[idx / WORD_BITS] |= (1 << (idx % WORD_BITS));
}

static inline int bit_is_set(unsigned int *bitarray, size_t idx) {
    return (bitarray[idx / WORD_BITS] & (idx % WORD_BITS)) != 0;
}

struct induction_set {
    int n;
    int *implies;
};

struct induction_set *compute_induction_set(int n) {
    struct induction_set *set = malloc(sizeof(struct induction_set));
    if(!set) {
        char msg[255];
        sprintf(msg, "error mallocing induction set for n=%d\n", n);
        fputs(msg, stderr);
        exit(1);
    }

    set->n = n;
//    int ncur_set = (n/2)+1;
//    int *cur_set = calloc(ncur_set, sizeof(int));
//
//    if(!cur_set) {
//        char msg[255];
//        sprintf(msg, "error callocing cur_set of size %d\n", ncur_set);
//        fputs(msg, stderr);
//        exit(1);
//    }
//
//    int cur_set_pos = 0;

    printf("bytes: %d\n", n / 8 + 1);
    unsigned int *set_bits = calloc(n / 8 + 1, sizeof(unsigned int));
    int nset = 0;

    /* this could be optimised, but it's intended as pre-initialisation code. */
    for(int i=n; i >= 1; i--) {
        /* if it divides fully */
        if((n%i) == 0) {
            int other = n/i;

            if(!bit_is_set(set_bits, i-1)) {
                nset++;
            }

            /* for a square number, x*x will divide,
             * we don't want to count it twice. */
            if(i != other && !bit_is_set(set_bits, other-1)) {
                nset++;
            }

            printf("%d %d\n", i, other);
            /* using zero based indexing in the bitset. */
            bit_set(set_bits, i-1);
            bit_set(set_bits, other-1);

            // ignore for now
            /* theoretically(guestimating) we only need to expand by about n more
             * elements. the larger n is, the larger the uncertainty on this guess
             * is. if we underestimate, we will need to expand it again later with
             * a smaller value of n, reducing the amount of wasted space. */
//            if(cur_set_pos >= ncur_set) {
//            }
        }
    }

    set->implies = calloc(sizeof(nset)+1, sizeof(int));

    int j = 0;
    for(int i=0; i < n; i++) {
        if(bit_is_set(set_bits, i)) {
            printf("%d set\n", i);
            set->implies[j++] = i+1;
        }
    }

    printf("set for %d\n", n);
    int *ptr = set->implies;

    while(--nset > 0) {
        printf("%d, ", (*ptr) + 1);
        ptr++;
    }
    printf("\n");

    return set;
}

int main(int argc, char *argv[]) {
    compute_induction_set(10);
    return 0;
}
