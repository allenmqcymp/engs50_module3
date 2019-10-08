#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char * argv[]) {

    car_t car0;
    strcpy(car0.plate, "abc120");
    car0.price = 1000.0;
    car0.next = NULL;

    int32_t res = lput(&car0);

    if (res != 0) {
        fprintf(stderr, "return code of %d\n", res);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}
