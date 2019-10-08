#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

void f(car_t *cp) {
    cp->price = cp->price + 1;
}


int main(int argc, char * argv[]) {

    car_t car1;
    strcpy(car1.plate, "abc121");
    car1.price = 2000.0;

    double old_car1_price = car1.price;

    car_t car0;
    strcpy(car0.plate, "abc120");
    car0.price = 1000.0;

    double old_car0_price = car0.price;

    lput(&car0);

    car0.next = &car1;
    car1.next = NULL;

    lapply(&f);

    if ((car0.price != old_car0_price + 1) || (car1.price != old_car1_price + 1)) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}
