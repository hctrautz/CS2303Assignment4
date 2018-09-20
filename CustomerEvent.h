/* Hunter Trautz and Gabe Aponte, CustomerEvent.h */
#ifndef CUSTOMEREVENT_H
#define CUSTOMEREVENT_H

class CustomerEvent: public Event{
	public:
		Teller *teller;
		Customer *customer;
		CustomerEventType type;
		void action(EventQueue *eventQueue, TellerQueue *tellerQueue, float averageServiceTime, SimulatiomStats *statistics, float simulationTime, bool commonQueue, CustomerQueue *customerQueue);
};
#endif
