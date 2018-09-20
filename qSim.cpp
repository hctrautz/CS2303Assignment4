/* Hunter Trautz and Gabe Aponte, qSim.cpp */
#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <cmath>
using namespace std;

#include "qSim.h"
#include "SimulatiomStats.h"

#include "Event.h"
#include "Event.cpp"
#include "EventQueue.h"
#include "EventQueue.cpp"

#include "Customer.h"
#include "Customer.cpp"
#include "Teller.h"
#include "Teller.cpp"

#include "CustomerEvent.h"
#include "CustomerEvent.cpp"
#include "TellerEvent.h"
#include "TellerEvent.cpp"

#include "TellerQueue.h"
#include "TellerQueue.cpp"
#include "CustomerQueue.h"
#include "CustomerQueue.cpp"

/** Processes each event in the eventQueue
 * @Param *eventQueue pointer to the simulation's eventQueue
 * @Param *tellerQueue pointer to the simulation's tellerQueue
 * @Param *customerQueue pointer to the simulation's CustomerQueue
 * @Param averageServiceTime the service time for each teller 
 * @Param simulationTime keeps track of the simulation time for each individual simulation 
 * @Param *statidtics pointer to a statisitics object which keeps track of various data for each simulation 
 * @Param commonQueue boolean indicating whether to use a common queue or individual queues (true == common queue, false == individual queues)
 * @Return void, processes the queue until there are no more customers 
*/
void processQueue(EventQueue *eventQueue, TellerQueue *tellerQueue, CustomerQueue *customerQueue, float averageServiceTime, float simulationTime, SimulatiomStats *statisitics, bool commonQueue){
	if(eventQueue->event == NULL){
		//if there are no more events left to process return nothing and terminate
		return;
	}

	//processes the event with the action fcn
	eventQueue->event->action(eventQueue, tellerQueue, averageServiceTime, statisitics, simulationTime, commonQueue, customerQueue);

	//After it's been processed, remove it
	eventQueue->removeEvent();

	//Call the function again but with the next event in the queue
	processQueue(eventQueue->nextEvent, tellerQueue, customerQueue, averageServiceTime, simulationTime, statisitics, commonQueue);
}

/** Runs the simulation
 * @Param customers Number of customers in the simulation
 * @Param tellers Number of tellers in the simulation
 * @Param simulationTime Clock for simulation
 * @Param averageServiceTime average service time for each customer
 * @Param commonQueue Boolean value representing if the tellers draw from a single common queue or individual queues
 * @Return Prints statistics for the simulation
*/
void simulation(int customers, int tellers, float simulationTime, float averageServiceTime, bool commonQueue){
	EventQueue *eventQueue = new EventQueue();				
	TellerQueue *tellerQueue = new TellerQueue();	
	CustomerQueue *customerQueue = new CustomerQueue();	
	SimulatiomStats *statisitics = new SimulatiomStats(customers);			
	statisitics->numberOfTellers = tellers;					

	//adds tellers to tellerQueue
	for(int i = 0; i < tellers; i++){
		tellerQueue->add(i);
	}

	//sets defaults for every customer and their events
	for(int i = 0;i < customers; i++){
		statisitics->customerWaitTimes[i] = 0;								
		Customer *customer = new Customer();								
		customer->id = i;													
		CustomerEvent *customerEvent = new CustomerEvent();					
		customerEvent->customer = customer;									
		customerEvent->type = CustomerArrival;								
		customerEvent->time = simulationTime * rand()/float(RAND_MAX);		
		eventQueue->addEvent(customerEvent);								
	}

	statisitics->totalCustomers = customers; // sets totalCustomers field of statisitics to number of customers

	processQueue(eventQueue, tellerQueue, customerQueue, averageServiceTime, simulationTime, statisitics, commonQueue);

	// calculates averageCustomerTimeSpent and save's it to the statitics object
	statisitics->averageCustomerTimeSpent = statisitics->averageCustomerTimeSpent/statisitics->totalCustomersServed;
	

	float standardDeviation = 0; 

	//calculates the standard deviantion for the siulation
	for(int i = 0; i < customers; i++){
		if(statisitics->customerWaitTimes[i] != 0){
			standardDeviation = standardDeviation+(pow(statisitics->customerWaitTimes[i]-statisitics->averageCustomerTimeSpent,2));
		}
	}
	standardDeviation = standardDeviation/statisitics->totalCustomersServed;
	standardDeviation = sqrt(standardDeviation);

	//after done calculating save it to the statistics object
	statisitics->standardDeviation = standardDeviation;

	//if the user indicated that a common queue should be used processes it as such
	if(commonQueue){
		statisitics->queueType = Common;
	}
	statisitics->print(); // prints out statistics after the simulation is done 
}

int main(int argc, char **argv){
	int tellers = 0;
	int customers = 0;									
	float simulationTime = 0.0;			
	float averageServiceTime = 0.0;		

	//produces an error and prints a message if there is a problem with the arguments
	if ((argc < 5) || (argc > 6)){
		cout << "Usage:" << endl;
		cout << "./qSim #customers #tellers simulationTime averageServiceTime <seed>" << endl;
		return EXIT_FAILURE;
	}

	if(argc == 6){
		srand(atoi(argv[5]));
	}else{
		srand(0);
	}

	customers = atoi(argv[1]);				
	tellers = atoi(argv[2]);				
	simulationTime = atof(argv[3]);		
	averageServiceTime = atof(argv[4]);		

	//individual teller queue sim
	simulation(customers, tellers, simulationTime, averageServiceTime, false);	
	// commonQueue sim
	simulation(customers, tellers, simulationTime, averageServiceTime, true);	

	//Sucess.
	return 0;
}
