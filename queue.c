/* 
 * Stjepan Vrbić, Allen Ma, Joe Signorelli 10.8.2019
 * queue.c -- implements a generic queue
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    struct node *next;
    void *data;
} node_t;

typedef struct queue {
    node_t *front;
    node_t *back;
} queue_t;

/* create an empty queue */
queue_t* qopen(void){
    queue_t *empty_queue = malloc(sizeof(queue_t));
    empty_queue->front = NULL;
    empty_queue->back = NULL;
    return empty_queue;
}      

/* deallocate a queue, frees everything in it */
void qclose(queue_t *qp){
    node_t *temp = qp->front;
    node_t *prev;
    while (temp != NULL){
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    free(qp);
}  

/* put element at the end of the queue
 * returns 0 is successful; nonzero otherwise 
 */
int32_t qput(queue_t *qp, void *elementp){
    node_t *node_element = malloc(sizeof(node_t));
    if (qp->front == NULL && qp->back == NULL){
        node_element->next = NULL;
        node_element->data = elementp;
        qp->front = node_element;
        qp->back = node_element;
        return 0;
    }else{
        node_element->next = NULL;
        node_element->data = elementp;
        qp->back->next = node_element;
        qp->back = node_element;
        return 0;
    }
    return -1;
}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp){
    if (qp->front == NULL){
        return NULL;
    }
    node_t *first_element = qp->front;
    qp->front = qp->front->next;
    void *d = first_element->data;
    free(first_element);
    return d;
}

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
    node_t *temp = qp->front;
    while (temp != NULL){
        fn(temp->data);
        temp = temp->next;
    }
}

/* search a queue using a supplied boolean function
 * skeyp -- a key to search for
 * searchfn -- a function applied to every element of the queue
 *          -- elementp - a pointer to an element
 *          -- keyp - the key being searched for (i.e. will be 
 *             set to skey at each step of the search
 *          -- returns TRUE or FALSE as defined in bool.h
 * returns a pointer to an element, or NULL if not found
 */
void* qsearch(queue_t *qp, 
							bool (*searchfn)(void* elementp,const void* keyp),
							const void* skeyp){
    node_t *temp = qp->front;
    while (temp != NULL){
        bool found = searchfn(temp->data, skeyp);
        if (found) {
            return temp->data;
        }
        temp = temp->next;
    }
    return NULL;
}

/* search a queue using a supplied boolean function (as in qsearch),
 * removes the element from the queue and returns a pointer to it or
 * NULL if not found
 */
void* qremove(queue_t *qp,
							bool (*searchfn)(void* elementp,const void* keyp),
							const void* skeyp){
    node_t *curr = qp->front;
    node_t *prev = NULL;
    while (curr != NULL){
        bool found = searchfn(curr->data, skeyp);
        if (found){
            //if it is the only element
            if (curr == qp-> front && curr == qp->back){
                qp->front = NULL;
                qp->back = NULL;
                void *d = curr->data;
                free(curr);
                return d;
            }else if (curr == qp->front){ //check if it is the first or last element
                qp->front = curr->next;
                void *d = curr->data;
                free (curr);
                return d;
            }else if (curr == qp->back){
                qp->back = prev;
                prev->next = NULL;
                void *d = curr->data;
                free(curr);
                return d;
            }else{ //if it is neither the first or last element
                prev->next = curr->next;
                void *d = curr->data;
                free(curr);
                return d;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

/* concatenatenates elements of q2 into q1
 * q2 is dealocated, closed, and unusable upon completion 
 */
void qconcat(queue_t *q1p, queue_t *q2p){
	if (q1p->front == NULL && q2p->front == NULL){
		free(q2p);
	}
	else if(q1p->front != NULL && q2p->front == NULL){
		free(q2p);
	}
	else if(q1p->front == NULL && q2p->front != NULL){
		q1p->front = q2p->front;
		q1p->back = q2p->back;
		free(q2p);
	}
	else{
		q1p->back->next = q2p->front;
		q1p->back = q2p->back;
		free(q2p);
	}
}

