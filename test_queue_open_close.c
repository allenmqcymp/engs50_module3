/*
 * tests opening and closing of the hashtable
 * module 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"
#include "list.h"

#define MAXNM 128

typedef struct person {
    char name[MAXNM];
    int age;
    double rate;
} person_t;

person_t make_person(const char *name, int age, double rate) {
    person_t p;
    strcpy(p.name, name);
    p.age = age;
    p.rate = rate;
    return p;
}


int main(void) {

    queue_t *qp = qopen();

    person_t p = make_person("allen", 21, 10.00);
    person_t p2 = make_person("allen", 22, 10.00);

    int32_t res1 = qput(qp, (void *) &p);
    if (res1 != 0) {
        exit(EXIT_FAILURE);
    }
    int32_t res2 = qput(qp, (void *) &p2);
    if (res2 != 0) {
        exit(EXIT_FAILURE);
    }

    qclose(qp);

    exit(EXIT_SUCCESS);
}
