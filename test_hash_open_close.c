/*
 * tests opening and closing of the hashtable
 * module 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"
#include "list.h"

int main(void) {
    hashtable_t *htp2 = hopen(500);

    if (htp2 == NULL) {
        exit(EXIT_FAILURE);
    }

    hclose(htp2);

    exit(EXIT_SUCCESS);
}
