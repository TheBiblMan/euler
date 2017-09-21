#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc <= 1) {
		fputs("err: no target specified\n", stderr);
		return 0;
	}

	long int n = atol(argv[1]);

	/* divide by the smallest number possible
	 * each time, starting at 2· this guarantees
	 * that we will collect prime factors. */
	long int k = 2;

	while(n > 1 && n > k) {
		if((n % k) == 0) {
			n /= k;
			printf("prime factor: %ld\n", k);
			k = 2; /* reset */
		} else {
			/* could do += 2 every time after
			 * the initial += 1 for k=2 to skip
			 * half the numbers. */
			k++;
		}
	}

	printf("prime factor: %ld (rem:%ld)\n", k, n);

	return 0;
}
