/*
 * tests takong stuff out of the queue
 * performs 3 tests:
 *  - puts 5 person into the queue
 *  - takes all of them out
 *  - tests removing from empty queue
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

int main(void) {

    queue_t *qp = qopen();
    person_t person1 = {"stjepan", 21, 1};
    person_t person2 = {"allen", 21, 2};
    person_t person3 = {"allen", 21, 3};
    person_t person4 = {"allen", 21, 4};
    person_t person5 = {"allen", 21, 5};
    qput(qp, (void *)&person1);
    qput(qp, (void *)&person2);
    qput(qp, (void *)&person3);
    qput(qp, (void *)&person4);
    qput(qp, (void *)&person5);

    person_t *p = (person_t *)qget(qp);
    if (p->rate != 1){
        exit(EXIT_FAILURE);
    }
    p = (person_t *)qget(qp);
    if (p->rate != 2){
        exit(EXIT_FAILURE);
    }
    p = (person_t *)qget(qp);
    if (p->rate != 3){
        exit(EXIT_FAILURE);
    }
    p = (person_t *)qget(qp);
    if (p->rate != 4){
        exit(EXIT_FAILURE);
    }
    p = (person_t *)qget(qp);
    if (p->rate != 5){
        exit(EXIT_FAILURE);
    }

    qget(qp);
    
    qclose(qp);
    printf("success");
    exit(EXIT_SUCCESS);
}
