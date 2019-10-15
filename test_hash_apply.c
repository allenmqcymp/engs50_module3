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

/*
 * Takes in a person_t struct and adds 10 to their age
 */
void addten_age(void *ep) {
    person_t *pp = (person_t *) ep;
    pp->age = pp->age + 10;
}

int main(void) {

    hashtable_t *htp = hopen(50);

    if (htp == NULL) {
        exit(EXIT_FAILURE);
    }

    // first, test happly with nothing in the htable
    happly(htp, &addten_age);

    person_t p1 = make_person("alpha", 1, 10.00);
    person_t p2 = make_person("beta", 2, 10.00);
    person_t p3 = make_person("charlie", 3, 10.00);
    person_t p4 = make_person("delta", 4, 10.00);
    person_t p5 = make_person("echo", 5, 10.00);

    int p1_age = 1;
    int p2_age = 2;
    int p3_age = 3;
    int p4_age = 4;
    int p5_age = 5;

    // add them to the hashtable
    int32_t res = hput(htp, (void *) &p1, "alpha", sizeof("alpha"));
    if (res != 0) {
        exit(EXIT_FAILURE);
    }

    res = hput(htp, (void *) &p2, "beta", sizeof("beta"));
    if (res != 0) {
        exit(EXIT_FAILURE);
    }

    res = hput(htp, (void *) &p3, "charlie", sizeof("charlie"));
    if (res != 0) {
        exit(EXIT_FAILURE);
    }

    res = hput(htp, (void *) &p4, "delta", sizeof("delta"));
    if (res != 0) {
        exit(EXIT_FAILURE);
    }

    res = hput(htp, (void *) &p5, "echo", sizeof("echo"));
    if (res != 0) {
        exit(EXIT_FAILURE);
    }

    happly(htp, &addten_age);

    if (p1.age - 10 != p1_age) {
        
        exit(EXIT_FAILURE);
    }

    if (p2.age - 10 != p2_age) {
        exit(EXIT_FAILURE);
    }

    if (p3.age - 10 != p3_age) {
        exit(EXIT_FAILURE);
    }

    if (p4.age - 10 != p4_age) {
        exit(EXIT_FAILURE);
    }

    if (p5.age - 10 != p5_age) {
        exit(EXIT_FAILURE);
    }

    hclose(htp);

    exit(EXIT_SUCCESS);
}
