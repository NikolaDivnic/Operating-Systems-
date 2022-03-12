/*
 * Event.cpp
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#include "Event.h"
#include"KernelEv.h"
#include"Liste.h"
Event::Event(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	myImpl = new KernelEv(ivtNo);
	NizDogadjaja::primerak->ubaci(myImpl);
}

Event::~Event() {
	// TODO Auto-generated destructor stub
	NizDogadjaja::primerak->izbaciSem(myImpl);
	delete myImpl;
}

void Event::wait (){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
