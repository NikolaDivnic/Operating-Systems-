/*
 * semaphor.h
 *
 *  Created on: Jun 25, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
#include "SCHEDULE.H"
#include"Liste.h"
typedef unsigned int Time;
class KernSem;
class Semaphore {
public:
		Semaphore (int init=1);
		virtual ~Semaphore ();
		virtual int wait (Time maxTimeToWait);
		virtual int signal(int n=0);
		int val () const; // Returns the current value of the semaphore
	private:
		KernSem* myImpl;
};

#endif /* SEMAPHOR_H_ */
