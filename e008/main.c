#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct btreenode
{
    struct btreenode *leftchild ;
    char *data ;
    struct btreenode *rightchild ;
} ;


int sum(char *buf) {
    int sum = 0;

    char *p = buf;
    while(*p) {
        sum *= (int)(*p);
        p++;
    }

    return sum;
}

void insert(struct btreenode **sr, char *buf) {
    int hash = sum(buf);

    if (*sr == NULL) {
        *sr = malloc(sizeof(struct btreenode));

        if(!(*sr)) {
            fprintf(stderr, "malloc error");
            exit(1);
        }

        (*sr)->leftchild = NULL;
        (*sr)->data = buf;
        (*sr)->rightchild = NULL;
    } else {
        if (hash < sum((*sr)->data))
            insert(&((*sr)->leftchild), buf);
        else
            insert(&((*sr)->rightchild), buf);
    }
}

void inorder(struct btreenode *sr) {
    if (sr != NULL) {
        inorder(sr->leftchild);
        printf("%s\n", sr->data);
        inorder(sr->rightchild);
    }
}

char *get_number() {
    FILE *fp;

    fp = fopen("the_number.txt", "r");

    if(!fp) {
        fprintf(stderr, "couldn't open number file.\n");
        exit(1);
    }

    char *buf = calloc(1001, sizeof(char));
    char *str = buf;

    if(!buf) {
        fprintf(stderr, "couldn't malloc buffer.\n");
        exit(1);
    }

    int c;
    while((c = fgetc(fp)) != EOF) {
        if(c != '\n') {
            *buf = c;
            buf++;
        }
    }

    *buf = 0;

    fclose(fp);

    return str;
}

int main(int argc, char *argv[]) {
    char *number = get_number();

    char *cur = number;

    struct btreenode *bt ;
    bt = NULL;

    int i, invalid;

    while((cur - number) < 1000) {
        invalid = 0;

        for(i=0; i < 13; i++) {
            if(cur[i] == '0') {
                invalid = 1;
                break;
            }
        }

        if(!invalid) {
            char *buf = calloc(14, sizeof(char));
            memcpy(buf, cur, 13);
            buf[13] = 0;

            insert(&bt, buf);

//            printf("%s\n", buf);
        }

        cur += (i + 1);
    }

    inorder(bt);
    return 0;
}
