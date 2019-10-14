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
    // create a new hashtable
    // hashtable_t *htp = hopen(0);
    // hashtable_t *htperr = hopen(-1);
    // hashtable_t *htp1 = hopen(1);
    hashtable_t *htp2 = hopen(100);

    car_t fastcar;
    fastcar.next = NULL;
    strcpy(fastcar.plate, "need4speed");
    fastcar.price = 10000000.0;
    fastcar.year = 1988;

    // const char *key = "tracy chapman";

    // long int keylen = strlen(key);

    // // add stuff to the hashtables
    // if (!hput(htp, (void *) &fastcar, key, keylen)) {
    //     exit(EXIT_FAILURE);
    // }
        
    // if (!hput(htp1, (void *) &fastcar, key, keylen)) {
    //     exit(EXIT_FAILURE);
    // }
        
    // if (!hput(htp1, (void *) &fastcar, key, keylen)) {
    //     exit(EXIT_FAILURE);
    // }
        
    // if (!hput(htp2, (void *) &fastcar, key, keylen)) {
    //     exit(EXIT_FAILURE);
    // }

    // test closing of the hashtable
    // hclose(htp1);
    hclose(htp2);
    // hclose(htperr);
    // hclose(htp);

    exit(EXIT_SUCCESS);
}
