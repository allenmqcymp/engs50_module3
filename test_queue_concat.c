/* test_queue_concat.c --- 
 * 
 * 
 * Author: Steven J. Signorelli Jr. 
 * Description: tests the concat function of a queue
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include "time.h"
#include "list.h"
#include "queue.h"


int main(void){
	car_t car1;
	strcpy(car1.plate, "aaa111");
	car1.price = 100.0;
	
	car_t car2;
	strcpy(car2.plate, "bbb222");
	car2.price = 200.0;

	car_t car3;
	strcpy(car3.plate, "ccc333");
	car3.price = 300.0;

	queue_t *qp1 = qopen();
	queue_t *qp2 = qopen();

	qput(qp1, &car1);
	qput(qp1, &car2);
	qput(qp2, &car3);

	qconcat(qp1, qp2);

  car_t *car12 = (car_t *)qget(qp1);
	car_t *car22 = (car_t *)qget(qp1);
	car_t *car32 = (car_t *)qget(qp1);

	if((car1.price != car12->price) || (car2.price != car22->price) || (car3.price != car32->price)){
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);


}
