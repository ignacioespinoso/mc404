#include <stdio.h>

int xablau(int a, int b) {
    int c = a;
    for(int i = 1; i < b; i++) {
        c *= a;
    }

    printf("%d ** %d = %d\n", a, b, c);
    return c;
}
