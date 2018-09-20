/* Hunter Trautz and Gabe Aponte, Event.h */
#ifndef EVENT_H
#define EVENT_H

#include "TellerQueue.h"
#include "EventQueue.h"
#include "CustomerQueue.h"

class Event{
	public:
		float time;
		virtual void action(EventQueue *eventQueue, TellerQueue *tellerQueue, float averageServiceTime, SimulatiomStats *stats, float simulationTime, bool commonQueue, CustomerQueue *theCommonQueue) = 0;
};
#endif
