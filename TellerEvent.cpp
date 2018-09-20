/* Hunter Trautz and Gabe Aponte, TellerEvent.cpp */
#include "TellerEvent.h"

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
void TellerEvent::action(EventQueue *eventQueue, TellerQueue *tellerQueue, float averageServiceTime, SimulatiomStats *statistics, float simulationTime, bool commonQueue, CustomerQueue *customerQueue){
	if(this->type == TellerServiceCompleted){
		
		this->time = this->time + 2*averageServiceTime*rand()/float(RAND_MAX);
		this->teller->timeElapsed = this->time;
		if(!commonQueue){
			this->teller->customers = this->teller->customers->nextCustomer;
		}
		this->teller->customersInLine = this->teller->customersInLine-1;
		this->teller->startService(eventQueue, averageServiceTime, statistics, simulationTime, commonQueue, customerQueue);
	}

	if(this->type == TellerIdleCompleted){
		this->teller->startService(eventQueue, averageServiceTime, statistics, simulationTime, commonQueue, customerQueue);
	}
}
