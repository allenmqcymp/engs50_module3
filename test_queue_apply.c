/*
 * tests takong stuff out of the queue
 *  - tests qapply for an empty queue
 * module 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include "time.h"
#include "queue.h"

#define MAXNM 128

typedef struct person {
    char name[MAXNM];
    int age;
    double rate;
} person_t;

void apply(void *element){
    person_t *e = (person_t *)element;
    e->age = e->age + 1;
}

int main(void) {

    queue_t *qp = qopen();
    qapply(qp, &apply);
    
    qclose(qp);
    exit(EXIT_SUCCESS);
}
