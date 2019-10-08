#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"


int main(int argc, char * argv[]) {

    // make a list
    car_t *cp = lget();

    if (cp != NULL) {
        fprintf(stderr, "error: cp is %p\n", (void *) cp);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
