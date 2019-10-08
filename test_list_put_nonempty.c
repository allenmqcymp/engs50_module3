#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(int argc, char * argv[]) {

    car_t car1;
    strcpy(car1.plate, "abc121");
    car1.price = 2000.0;
    car1.next = NULL;

    car_t car0;
    strcpy(car0.plate, "abc120");
    car0.price = 1000.0;
    car0.next = NULL;

    lput(&car1);
    int32_t res = lput(&car0);

    if (res != 0) {
        fprintf(stderr, "return code of %d\n", res);
        exit(EXIT_FAILURE);
    }

    if (car0.next != &car1) {
        fprintf(stderr, "car0's next car is not car 1\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}
