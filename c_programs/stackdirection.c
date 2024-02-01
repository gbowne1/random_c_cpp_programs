#include <stdio.h>
#include <stdbool.h>

bool upOrDown(int *other) {
    int x;

    if (!other) {
        return upOrDown(&x);
    }

    return &x > other;
}

int main(int argc, char *argv[]) {
    printf("Direction: %s\n", upOrDown(NULL) ? "UP" : "DOWN");

    return 0;
}
