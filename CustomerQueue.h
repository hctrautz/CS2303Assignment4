/* Hunter Trautz and Gabe Aponte, CustomerQueue.h */
#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

class Customer;

class CustomerQueue{
	public:
		Customer *customer;
		CustomerQueue *nextCustomer;
		void addCustomer(Customer *customer);
		void removeCustomer();
};
#endif
