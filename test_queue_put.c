/*
 * tests takong stuff out of the queue
 *  - puts 5 person into the queue
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
    person_t person1 = {"stjepan", 21, 5};
    person_t person2 = {"allen", 21, 5};
    person_t person3 = {"allen", 21, 5};
    person_t person4 = {"allen", 21, 5};
    person_t person5 = {"allen", 21, 5};
     if (qput(qp, (void *)&person1) != 0){
         exit(EXIT_FAILURE);
     }
    if (qput(qp, (void *)&person2) != 0){
         exit(EXIT_FAILURE);
     }
     if (qput(qp, (void *)&person3) != 0){
         exit(EXIT_FAILURE);
     }
     if (qput(qp, (void *)&person4) != 0){
         exit(EXIT_FAILURE);
     }
     if (qput(qp, (void *)&person5) != 0){
         exit(EXIT_FAILURE);
     }
    printf("success");
    qclose(qp);
    exit(EXIT_SUCCESS);
}
