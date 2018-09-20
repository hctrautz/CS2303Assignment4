/* Hunter Trautz and Gabe Aponte, CustomerQueue.cpp */
#include "CustomerQueue.h"

/** Removes the customer that is at the head of the queue from the queue and sets the next customer in line as the head
 * @Param *queue pointer to the queue that we want to remove the head customer from
 * @Return void, removes the head of the queue
*/
void removeCustomerHelper(CustomerQueue *queue){
	//if the head of the queue is not pointintg to another customer, initiallize a new one so that the queue
	//so that the queue can be mainted
	if(queue->nextCustomer == NULL){
		queue->nextCustomer = new CustomerQueue();
	}
	//set the head of the queue to the next customer in line
	*queue = *queue->nextCustomer;
}

/** Removes the customer that is at the head of the queue from the queue and sets the next customer in line as the head
 * This function is so that you can easily call removeCustomerHelper on an object
 * @Return void, removes the head of the queue
*/
void CustomerQueue::removeCustomer(){
	removeCustomerHelper(this);
}

/** Adds a customer to the end of the queue 
 * @Param *customer pointer to the customer that we want to add
 * @Param *queue pointer to the queue that we want to add the customer to 
 * @Return void, adds the customer to the end of the queue
*/
void addCustomerHelper(Customer *customer, CustomerQueue *queue){
	if(queue->customer == NULL){
		queue->customer = customer;
	} else {
		if(queue->nextCustomer == NULL){
			queue->nextCustomer = new CustomerQueue();
		}
		addCustomerHelper(customer, queue->nextCustomer);
	}
}

/** adds a customer to the end of the queue 
 * This function is so that you can easily call addCustomerHelper on an object
 * @Return void, adds the customer to the end of the queue
*/
void CustomerQueue::addCustomer(Customer *customer){
	addCustomerHelper(customer, this);
}

