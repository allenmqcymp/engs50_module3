#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

void f(car_t *cp) {
    cp->price = cp->price + 1;
}


int main(void) {
    lapply(&f);

    exit(EXIT_SUCCESS);
}
