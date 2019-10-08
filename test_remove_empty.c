#include "list.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]) {

    car_t *cp = lremove("hello123");

    if (cp != NULL)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}
