/*
 * Allen ma, Stjepan Vrbic, Joe Signorelli 10.15.19 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))

static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;
  
  if (len <= 0 || data == NULL)
		return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

// think of hsize as the number of buckets


typedef struct hashtable {
  // an array of pointers to a queue
  queue_t **table;
  uint32_t hsize;
} hashtable_t;

/* hopen -- opens a hash table with initial size hsize */
hashtable_t *hopen(uint32_t hsize) {
  hashtable_t *htp = malloc(sizeof(hashtable_t));
  htp->table = (queue_t **) malloc(sizeof(queue_t *) * hsize);
  htp->hsize = hsize;
  // for each bucket, allocate a queue
  for (int i = 0; i < hsize; i++) {
    (htp->table)[i] = qopen();
  }
  if (htp == NULL) {
    printf("calloc failed to allocate hashtable\n");
    return NULL;
  }
  return htp;
}

/* hclose -- closes a hash table */
void hclose(hashtable_t *htp) {
  // deallocate every queue in the hashtable as well as the hashtable itself
  for (int i = 0; i < htp->hsize; i++) {
    queue_t *q = (htp->table)[i];
    qclose(q);
  }
  // free the hashtable
  free(htp->table);
  free(htp);
}

/* hput -- puts an entry into a hash table under designated key 
 * returns 0 for success; non-zero otherwise
 */
int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen) {
  uint32_t idx = SuperFastHash(key, keylen, htp->hsize);
  // place the element at idx
  assert(idx >= 0 && idx < htp->hsize);
  queue_t *q = (htp->table)[idx];
  int32_t qres = qput(q, ep);
  return qres;
}

/* happly -- applies a function to every entry in hash table */
void happly(hashtable_t *htp, void (*fn)(void* ep)) {
  for (int i = 0; i < htp->hsize; i++) {
    queue_t *q = (htp->table)[i];
    qapply(q, fn);
  }
}

/* hsearch -- searchs for an entry under a designated key using a
 * designated search fn -- returns a pointer to the entry or NULL if
 * not found
 */
void *hsearch(hashtable_t *htp, 
	      bool (*searchfn)(void* elementp, const void* searchkeyp), 
	      const char *key, 
	      int32_t keylen) {

  // get the correct index
  uint32_t idx = SuperFastHash(key, keylen, htp->hsize);
  queue_t *q_idx = (htp->table)[idx];
  return qsearch(q_idx, searchfn, key);
}

/* hremove -- removes and returns an entry under a designated key
 * using a designated search fn -- returns a pointer to the entry or
 * NULL if not found
 */
void *hremove(hashtable_t *htp, 
	      bool (*searchfn)(void* elementp, const void* searchkeyp), 
	      const char *key, 
	      int32_t keylen) {
  // get the correct index
  uint32_t idx = SuperFastHash(key, keylen, htp->hsize);
  queue_t *q_idx = (htp->table)[idx];
  return qremove(q_idx, searchfn, key);
}

