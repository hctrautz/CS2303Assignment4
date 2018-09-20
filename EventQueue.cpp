/* Hunter Trautz and Gabe Aponte, EventQueue.cpp */
#include "EventQueue.h"

/** Removes the event that is at the head of the queue from the queue and sets the next event in line as the head
 * @Param *queue pointer to the queue that we want to remove the head event from
 * @Return void, removes the head of the queue
*/
void removeEventHelper(EventQueue *queue){
	queue = queue->nextEvent;
}

/** Removes the event that is at the head of the queue from the queue and sets the next event in line as the head
 * This function is so that you can easily call removeEventHelper on an object
 * @Return void, removes the head of the queue
*/
void EventQueue::removeEvent(){
	removeEventHelper(this);
}

/** Adds an event to the event queue
 * @Param *queue pointer to the eventQueue
 * @Param *event Pointer to the given event we want to add
 * @Return void, add the event to the event queue
*/
void addEventHelper(EventQueue *queue, Event *event){
	if(queue->nextEvent == NULL){
		//if the queue's first event is not pointing to anything, initalize a new event for it to point to
		queue->nextEvent = new EventQueue();

		//if the queue does not have a first event, assign the event that was passed in as the head
		if(queue->event == NULL){
			queue->event = event;

		}else //otherwise just add the event to the queue 	{
			queue->nextEvent->event = event;
		}
	
	else{
		//if the queue is normal insert the event in a place where the times line up
		if(event->time < queue->event->time){
			//Insert it here

			EventQueue* temp = new EventQueue();
			*temp = *queue;
			queue->event = event;

			queue->nextEvent = temp;
		}else{
			//call the function again with the next event and reapet until the times line up
			addEventHelper(queue->nextEvent, event);
		}
	}
}

/** Adds a event to the correct position in the queue
 * This function is so that you can easily call addEventHelper on an object
 * @param event the event you want to add to the queue
 * @Return void, adds the event to its correct position in queue
*/
void EventQueue::addEvent(Event *event){
	addEventHelper(this, event);
}
