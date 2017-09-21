#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NDEBUG 1

int main(int argc, char *argv[]) {
    /* example: for n=5
     * let S1 = sum of squares
     *        = 1^2 + 2^2 + ... + (n-1)^2 + n^2
     *        = 1^2 + 2^2 + 3^2 + 4^2 + 5^2
     *        = 55
     * let S2 = square of sums
     *        = (1+2+...+n-1+n)^2
     *        = (1+2+3+4+5)^2
     *        = (15)^2
     *        = 225
     *
     * d = S2 - S1
     *   = 225 - 55
     *   = 170
     *
     * S2 can also be written as:
     * (1+2+3+4+5)(1+2+3+4+5) => cross-multiplying:
     *
     *        1  2  3  4  5
     *        2  4  6  8  10
     *        3  6  9  12 15
     *        4  8  12 16 20
     *        5  10 15 20 25
     *
     * notice: the diagonal line going from 1 to 25 is equal
     * to S1, i.e. d is the sum of all of the numbers in the
     * grid except for that line. also the grid is symmetrical
     * along the line.
     *
     * also note, the centre of each row is the average of the
     * starting and ending numbers of the row.
     * e.g. (1+5)/2 = 3, (4+20)/2 = 12, etc.
     *
     * focus on the numbers on the left side of the diagonal.
     * the summation of each of the rows are:
     * 2, 9, 24, 50 (85 in total, half of d).
     *
     * the sum of the starting number and the number just before
     * the diagonal:
     * 2, 9, 16, 25
     * dividing by 2 (for the theoretical middle value, in the case of
     * 2, we do not divide) we get:
     * 2, 4.5, 8, 12.5
     * multiplying each of these numbers by the number of elements in the
     * row before the diagonal:
     * 2*1, 4.5*2, 8*3, 12.5*4
     * = 2, 9, 24, 50, i.e. our row summations.
     */
    int lim = 100;

    /* we ignore the first row as the diagonal line is on the '1'
     * meaning we don't count anything in it.
     *
     * similarly we skip row=2, as that is the row we do not
     * divide by two for(only 1 element), so we can just add 2
     * to our sum later. */

    int triangle_sum = 0;

    for(int row=3; row <= lim; row++) {
        /* number of elements on this row before the diagonal */
        int num_elems = row-1;

        /* our first element value is 'row'.
         * our last element value is 'row' * 'num_elems'
         */
        int first = row;
        int last = row * num_elems;

        float middle = (first + last) / 2.0f;
        float row_total = middle * num_elems;

#if NDEBUG
        int row_total_int = (int) row_total;
        if(row_total_int != row_total) {
            fprintf(stderr, "consistency error: row adds up to non-integer, expected: %d, got: %f (row=%d)\n", row_total_int, row_total, row);
            exit(1);
        }
#endif

        triangle_sum += row_total;
    }

    /* the missing row; see above */
    triangle_sum += 2;

    /* symmetrical grid */
    triangle_sum *= 2;

    printf("res: %d\n", triangle_sum);

    return 0;
}
