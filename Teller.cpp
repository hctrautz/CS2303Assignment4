/* Hunter Trautz and Gabe Aponte, Teller.cpp */
#include "TellerEvent.h"
#include "CustomerEvent.h"
#include "EventQueue.h"

/** Processes a customer for a teller 
 * @Param *eventQueue pointer to the eventQueue
 * @Param averageServiceTime the average service time for a customer
 * @Param *statistics the statistics for the current simulation
 * @Param simulationTime total amount of time the simulation will run for
 * @Param commonQueue boolean indicating whether to use a common queue or individual queues (true == common queue, false == individual queues)
 * @Param *customerQueue poiner to the customerQueue
 * @Return void, 
*/
void Teller::startService(EventQueue *eventQueue, float averageServiceTime, SimulatiomStats *statistics, float simulationTime, bool commonQueue, CustomerQueue *customerQueue){

	//if the teller has no customers then set the customer's field to a blank customerQueue
	if(this->customers == NULL){
		this->customers = new CustomerQueue();
	}
	//if it's not a common queue and there is no customer, or if it is a common queue and there is no customer
	if((!commonQueue && this->customers->customer == NULL) || (commonQueue && customerQueue->customer == NULL)){

		int idleTime = (rand()%140)+10;

		if(this->timeElapsed + idleTime > simulationTime && statistics->totalCustomers == statistics->totalCustomersServed){
			return;
		}

		//create a new idle and customer event
		TellerEvent *tellerEvent = new TellerEvent();
		tellerEvent->type = TellerIdleCompleted;
		tellerEvent->teller = this;
		tellerEvent->time = this->timeElapsed + idleTime;
		statistics->totalTellerIdleTime = statistics->totalTellerIdleTime+idleTime;
		this->timeElapsed = tellerEvent->time;
		eventQueue->addEvent(tellerEvent);

	} else /* if there is a customer */ {

		//create a new service event that is completed at 
		float serviceTime = 2*averageServiceTime*rand()/float(RAND_MAX);
		statistics->totalTellerServiceTime = statistics->totalTellerServiceTime+serviceTime;
		this->timeElapsed = this->timeElapsed+serviceTime;

		CustomerEvent *customerServicedEvent = new CustomerEvent();
		customerServicedEvent->type = CustomerServiceCompleted;

		if(commonQueue){
			customerServicedEvent->customer = customerQueue->customer;
		}else{
			customerServicedEvent->customer = this->customers->customer;
		}

		customerServicedEvent->time = this->timeElapsed;
		customerServicedEvent->teller = this;
		
		if(commonQueue){
			customerQueue->removeCustomer();
		}
		eventQueue->addEvent(customerServicedEvent);
	}
}

/** Adds a customer to the end of the queue 
 * @Param *customer pointer to the customer that we want to add
 * @Param *queue pointer to the queue that we want to add the customer to 
 * @Param averageServiceTime the time it took for the customer to be served
 * @Return void, adds the customer to the end of the queue
*/
void Teller::addCustomerHelper(Customer *customer, CustomerQueue *queue, float averageServiceTime){
	if(queue->customer == NULL){
		queue->customer = customer;
	} else {
		if(queue->nextCustomer == NULL){
			queue->nextCustomer = new CustomerQueue();
		}
		this->addCustomerHelper(customer, queue->nextCustomer, averageServiceTime);
	}
}

/** Adds a customer to the end of the queue 
 * @Param *eventQueue pointer to the customer that we want to add
 * @Param *customer pointer to the queue that we want to add the customer to 
 * @Param time amonut of time the teller has been active
 * @Param averageServiceTime the average service time for a customer
 * @Param statistics the stats for the simulation
 * @Param simulationTime the limit on how long the simulation can urn
 * @Return void, adds the customer to the end of the queue
*/
void Teller::addCustomerToQueue(EventQueue *eventQueue, Customer *customer, float time, float averageServiceTime, SimulatiomStats *statistics, float simulationTime){
	if(this->customers == NULL){
		this->customers = new CustomerQueue();
	}

	this->addCustomerHelper(customer, this->customers, averageServiceTime);
	this->customersInLine = this->customersInLine+1;

	//If this teller hasn't had a customer before, we need to get them checking.
	if(this->timeElapsed == 0){
		this->timeElapsed = time;
		this->startService(eventQueue, averageServiceTime, statistics, simulationTime, false, new CustomerQueue());
	}
}
