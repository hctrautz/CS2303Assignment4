
/* Hunter Trautz and Gabe Aponte, TellerQueue.cpp */
#include "TellerQueue.h"
void TellerQueue::add(int id){

	if(this->teller == NULL){
		Teller* teller = new Teller();
		teller->id = id;
		teller->customersInLine = 0;
		this->teller = teller;

	}else{
		if(this->nextTeller == NULL){
			this->nextTeller = new TellerQueue();
		}
		this->nextTeller->add(id);
	}

}

Teller *TellerQueue::shortestTellerLine(TellerQueue *shortestline){

	if(this->teller->customersInLine < shortestline->teller->customersInLine){
		shortestline = this;
	}

	if(this->nextTeller == NULL){
		return shortestline->teller;
	}
	return this->nextTeller->shortestTellerLine(shortestline);
}
