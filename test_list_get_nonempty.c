#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"


int main(int argc, char * argv[]) {

    car_t car0;
    strcpy(car0.plate, "abc120");
    car0.price = 1000.0;
    car0.next = NULL;

    lput(&car0);

    car_t *cp = lget();

    if (cp != &car0) {
        fprintf(stderr, "error: cp is %p when it should be %p\n", (void *) cp, (void *) &car0);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

}
