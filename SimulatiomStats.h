#include <stdio.h>
#ifndef STATISTICS_H
#define STATISTICS_H

enum QueueType {PerTeller, Common};

class SimulatiomStats{
	public:
	int totalCustomers;
	int totalCustomersServed;
	float totalTimeToServe;
	int numberOfTellers;
	QueueType queueType; 
	float averageCustomerTimeSpent;
	float standardDeviation;
	float maxWaitTime;
	float totalTellerServiceTime;
	float totalTellerIdleTime;

	float *customerWaitTimes;

	SimulatiomStats(int customers){
		totalCustomers = 0;
		totalCustomersServed = 0;
		totalTimeToServe = 0;
		numberOfTellers = 0;
		queueType = PerTeller;
		averageCustomerTimeSpent = 0;
		standardDeviation = 0;
		maxWaitTime = 0;
		totalTellerServiceTime = 0;
		totalTellerIdleTime = 0;
		customerWaitTimes = new float[customers];
	}
	
	void print(){

		cout << "\n" << endl;
		cout << "Statistics " << endl;
		cout << "Total Customers Served: " << totalCustomersServed << endl;
		cout << "Total Time Taken to Serve: " << totalTimeToServe << endl;
		cout << "Total Tellers: " << numberOfTellers << endl;

		printf("Queue Type: ");
		if(queueType == PerTeller){
			printf("Per-Teller ");
		}else{
			printf("Common ");
		}

		cout << "\n" << endl;
		cout << "Average Customer Time Used: " << averageCustomerTimeSpent << endl;
		cout << "Standard Deviation: " << standardDeviation << endl;
		cout << "Maximum Customer Wait Time: " << maxWaitTime << endl;
		cout << "Total Teller Service Time: " << totalTellerServiceTime << endl;
		cout << "Total Teller Idle Time: " << totalTellerIdleTime << endl;
		cout << "" << endl;
	}
};

#endif
