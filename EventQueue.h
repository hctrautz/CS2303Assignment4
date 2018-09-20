/* Hunter Trautz and Gabe Aponte, EventQueue.h */
#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

class Event;

#include "Event.h"

class EventQueue{
	public:
		Event *event;
		EventQueue *nextEvent;
		void addEvent(Event *event);
		void removeEvent();
};

#endif
