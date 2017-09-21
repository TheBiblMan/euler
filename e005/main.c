#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prime_fac *p_prime_fac;
struct prime_fac {
    p_prime_fac next;
    int num;
    int count;
};

/* look for a node with the given number and return
 * if if present, else returns nullptr.
 *
 * note that, in the context of this application, zero is not
 * a value valid for num, i.e. 0 is not a factor of any other
 * number, therefore, if we encounter a node with it's num
 * attribute set to zero, then we assume this is a newly allocated
 * node (via calloc or malloc and memset) and so we treat it as a
 * hit. */
p_prime_fac search(p_prime_fac list, int num) {
    for(p_prime_fac ptr=list; ptr; ptr = ptr->next) {
        if(ptr->num == num || ptr->num == 0) {
            return ptr;
        }
    }

    return NULL;
}

/* tries to allocate a node in the list, if unsuccessful
 * it will terminate the program, therefore removing the
 * need to check the return value. note that the newly allocated
 * node is zeroed. */
p_prime_fac alloc_pfac() {
    p_prime_fac ptr = malloc(sizeof(struct prime_fac));

    if(!ptr) {
        char msg[255];
        memset(msg, 0, sizeof(msg));
        sprintf(msg, "could not malloc head struct");
        fputs(msg, stderr);
        exit(1);
    }
    memset(ptr, 0, sizeof(struct prime_fac));

    return ptr;
}

void free_list(p_prime_fac list) {
    p_prime_fac n = list;

    while(n) {
        p_prime_fac next_node = n->next;
        free(n);
        n = next_node;
    }
}

/* computes the prime factorisation of a number (intended to be relatively small)
 * and creates a list which contains them as well as the number of times
 * they appear in the prime factorisation.
 *
 * note: this was taken from the e003 solution. */
p_prime_fac get_prime_factors(int n) {
    p_prime_fac head = alloc_pfac();
    p_prime_fac cur = head;

    long int k = 2;

    while (n > 1 && n >= k) {
        if ((n % k) == 0) {
            n /= k;

            p_prime_fac kfac = search(head, k);
            if(!kfac) {
                kfac = alloc_pfac();
                cur->next = kfac;
            }

            kfac->num = k;
            kfac->count++;
            k = 2; /* reset */
        } else {
            /* could do += 2 every time after
             * the initial += 1 for k=2 to skip
             * half the numbers. */
            k++;
        }
    }

    return head;
}

/* goes through the src list and ensures that all of the
 * prime factors recorded in this list are also represented in dst.
 *
 * if the number is not contained in dst, a new node is allocated and
 * the exponent of that factor is set to the exponent of the same factor in the
 * src list.
 *
 * if the number is present, the exponent must be at least the same as in
 * the src list. if it is not, it is adjusted. */
void merge_pfac_lists(p_prime_fac dst, p_prime_fac src) {
    p_prime_fac dst_tail = dst;
    while(dst_tail->next) {
        dst_tail = dst_tail->next;
    }

    for(p_prime_fac ptr=src; ptr; ptr = ptr->next) {
        p_prime_fac dst_node;

        if(!(dst_node=search(dst, ptr->num))) {
            dst_node = alloc_pfac();
            dst_node->num = ptr->num;
            dst_node->count = ptr->count;
            dst_tail->next = dst_node;
            dst_tail = dst_node;
            continue;
        }

        dst_node->num = ptr->num;

        if(dst_node->count < ptr->count) {
            dst_node->count =  ptr->count;
        }
    }
}

int main(int argc, char *argv[]) {
    /* challenge given */
    int bound = 20;

    p_prime_fac pfacs = alloc_pfac();
    p_prime_fac cur_pfacs;

    for(int i=1; i <= bound; i++) {
        cur_pfacs = get_prime_factors(i);
        merge_pfac_lists(pfacs, cur_pfacs);

        free_list(cur_pfacs);
    }

    int res = 1;
    for (p_prime_fac ptr = pfacs; ptr; ptr = ptr->next) {

        for(int i=0; i < ptr->count; i++) {
            res *= ptr->num;
        }
    }

    printf("res: %d\n", res);

    free_list(pfacs);

    return 0;
}


