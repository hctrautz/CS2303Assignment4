/* Hunter Trautz and Gabe Aponte, CustomerEvent.cpp */
#include "CustomerEvent.h"

/** Processes the queue with a single indiviudal line if the user specified a common queue
 * @Param *tellerQueue pointer to tellerQueue
 * @Param *eventQueue pointer to eventQueue  
 * @Param clock simulation clock, current time
 * @Param averageServiceTime each teller's service time
 * @Param *statistics the statistics for the simulation
 * @Param simulationTime time the simulation will run for
 * @Param *customerQueue Pointer to the CustomerQueue
 * @Return void, processes each event in the common queue
*/
void processCommonQueue(TellerQueue *tellerQueue, EventQueue *eventQueue, float clock, float averageServiceTime, SimulatiomStats *statistics, float simulationTime, CustomerQueue *customerQueue){ 

	//if there is nothing in the queue then terminate
	if(tellerQueue == NULL){
		return;
	}
	
	//if the queue hasn't already begun processeing, start processing
	if(tellerQueue->teller->timeElapsed == 0){
		tellerQueue->teller->timeElapsed = clock;
		tellerQueue->teller->startService(eventQueue, averageServiceTime, statistics, simulationTime, true, customerQueue);
		return;
	}
	//move to the next teller 
	processCommonQueue(tellerQueue->nextTeller, eventQueue, clock, averageServiceTime, statistics, simulationTime, customerQueue);
}


/** Completes the event of the individual object event the function was called on
 * @Param *eventQueue Pointer to EventQueue  
 * @Param *tellerQueue Pointer to TellerQueue
 * @Param averageServiceTime Average service time for the Teller services
 * @Param *statistics The statistics for the simulation
 * @Param simulationTime The duration the bank is open
 * @Param commonQueue Boolean whether the tellers draw from a common or from individual queues (true == common)
 * @Param *customerQueue pointer to the CustomerQueue
 * @Return void, processes the indiivudal event
*/
void CustomerEvent::action(EventQueue *eventQueue, TellerQueue *tellerQueue, float averageServiceTime, SimulatiomStats *statistics, float simulationTime, bool commonQueue, CustomerQueue *customerQueue){

	//if the event is customer arriving
	if(this->type == CustomerArrival){
		//either process it as a common queue 
		if(commonQueue){
			this->customer->arrivalTime = this->time;
			customerQueue->addCustomer(this->customer);
			processCommonQueue(tellerQueue, eventQueue, this->time, averageServiceTime, statistics, simulationTime, customerQueue);

		}else{ //or assign it to the shortest teller line
			Teller *lowestTeller = tellerQueue->shortestTellerLine(tellerQueue);
			this->teller = lowestTeller;
			this->customer->arrivalTime = this->time;
			this->teller->addCustomerToQueue(eventQueue, this->customer, this->time, averageServiceTime, statistics, simulationTime);
		}
	}

	//if the event is completed already record it's statistics
	if(this->type == CustomerServiceCompleted){
		
		float duration = (this->time - this->customer->arrivalTime);

		if(statistics->maxWaitTime < duration){
			statistics->maxWaitTime = duration;
		}
		
		//record the time it took to complete the event
		if(this->time > statistics->totalTimeToServe){
			statistics->totalTimeToServe = this->time;
		}
		//record the wait time
		statistics->customerWaitTimes[this->customer->id] = duration;

		//record the total customers served
		statistics->totalCustomersServed = statistics->totalCustomersServed+1;
		//record the average time it took to serve 
		statistics->averageCustomerTimeSpent = statistics->averageCustomerTimeSpent+duration;

		//saves the event for reference by the tellers 
		TellerEvent *CompletedEvent = new TellerEvent();
		CompletedEvent->time = this->time;
		CompletedEvent->type = TellerServiceCompleted;
		CompletedEvent->teller = this->teller;
		eventQueue->addEvent(CompletedEvent);
	}
}
