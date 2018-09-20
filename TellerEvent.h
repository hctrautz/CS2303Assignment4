/* Hunter Trautz and Gabe Aponte, TellerEvent.h */
#ifndef TELLEREVENT_H
#define TELLEREVENT_H

#include "Teller.h"

class TellerEvent: public Event{

	public:
		TellerEventType type;
		Teller *teller;
		void action(EventQueue *eventQueue, TellerQueue *tellerQueue, float averageServiceTime, SimulatiomStats *stats, float simulationTime, bool commonQueue, CustomerQueue *theCommonQueue);
};
#endif
