/*
 * Event.h
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
#include"Thread.h"
typedef unsigned char IVTNo;
class KernelEv;
class NizDogadjaja;
class Event {
	public:
		Event (IVTNo ivtNo);
		~Event ();
		void wait ();
	protected:
		friend class KernelEv;
		void signal(); // can call KernelEv
	private:
		KernelEv* myImpl;
};
#endif /* EVENT_H_ */
