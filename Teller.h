/* Hunter Trautz and Gabe Aponte, Teller.h */
#ifndef TELLER_H
#define TELLER_H

#include "Event.h"
#include "CustomerQueue.h"

class Teller{
	void addCustomerHelper(Customer *customer, CustomerQueue *queue, float averageServiceTime);
	public:
		int id;
		int customersInLine;
		float timeElapsed;
		CustomerQueue *customers;
		void addCustomerToQueue(EventQueue *eventQueue, Customer *customer, float time, float averageServiceTime, SimulatiomStats *statistics, float simulationTime);
		void startService(EventQueue *eventQueue, float averageServiceTime, SimulatiomStats *statistics, float simulationTime, bool commonQueue, CustomerQueue *customerQueue);
};

#endif 
