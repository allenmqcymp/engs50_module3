/*
 * tests searching of the hashtable
 * module 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "hash.h"
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

bool search_fun(void *element, const void* search){
    person_t *e = (person_t *)element;
    person_t *s = (person_t *)search;
    if ((e->age >= s->age) && (fabs(e->rate - s->rate) > 0.0)){
        return true;
    }
    return false;
}

// search function checks if the person is older, and if the person has a higher rate

int main(void) {
    
    // make a bunch of people

    hashtable_t *htp = hopen(1000);

    if (htp == NULL) {
        exit(EXIT_FAILURE);
    }

    person_t p1 = make_person("alpha", 18, 6.00);
    person_t p2 = make_person("beta", 21, 11.00);
    person_t p3 = make_person("charlie", 30, 14.00);
    person_t p4 = make_person("delta", 35, 30.00);
    person_t p5 = make_person("echo", 50, 40.00);

    // add all of them to the hashtable
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

    // should match to echo
    person_t search_dude = {"echo", 49, 35.00};

    person_t *guy = hsearch(htp, &search_fun, (void *) &search_dude, sizeof("echo"));
    if ((guy->age != 50) || (strcmp(guy->name, "echo") != 0) || (guy->rate < 35.00)) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
