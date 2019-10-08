#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

static car_t *front=NULL;

// tests - list with 0 elements, list with 1 element, list with 5 elements

/* put(): place a car at the beginning of the list
 * returns 0 if successful; nonzero otherwise 
 */
int32_t lput(car_t *cp) {
    if (cp == NULL) {
        return 1;
    }
    if (front == NULL) {
        front = cp;
        return 0;
    }
    cp->next = front;
    front = cp;
    return 0;
}

/* get(): remove and return the first car in the list;
 * return NULL if the list is empty
 */
car_t *lget() {
    if (front == NULL) {
        return NULL;
    }
    car_t *rp = front;
    front = front->next;
    return rp;
}

// no elements, 1 element, many elements
/* apply a function to every car in the list */
void lapply(void (*fn)(car_t *cp)) {
    if (front == NULL) {
        return;
    }
    for (car_t *p=front; p; p=p->next) {
        fn(p);
    }
}


// test with no instances, test with one instance, test with many instances of a designated plate
/* remove(): find, remove, and return any car with
 * the designated plate; return NULL if not present
 */
car_t *lremove(char *platep) {

    if (front == NULL) {
        return NULL;
    }

    car_t *curp = front;
    car_t *f_curp;
    while (curp != NULL) {
        if (strcmp(curp->plate, platep) != 0) {
            f_curp->next = curp->next;
            break;
        }
        f_curp = curp;
        curp = curp->next;
    }
    return curp;
}
