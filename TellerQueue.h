/* Hunter Trautz and Gabe Aponte, TellerQueue.h */
#ifndef TELLERQUEUE_H
#define TELLERQUEUE_H

class Teller;

class TellerQueue{
	public:
		Teller *teller;
		TellerQueue *nextTeller;
		void add(int id);
		Teller *shortestTellerLine(TellerQueue *shortLine);
};
#endif
