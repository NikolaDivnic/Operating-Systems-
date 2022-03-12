/*
 * Thread.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "Liste.h"


ID Thread::id = 2;
Thread::Thread(StackSize stackSize, Time timeSlice){
	if (timeSlice<0) timeSlice = (Time)2;
	myPCB = new PCB(this,stackSize, timeSlice);
	myPCB->postaviID(NizPCB::primerak->ubaci(myPCB));
	myPCBid = myPCB->dohvatiID();
}

Thread::~Thread() {
	waitToComplete();
	NizPCB::primerak->izbaci(myPCBid);
	delete myPCB;
}
void Thread::start(){
	myPCB->start();
}
void Thread::run(){
}
void Thread::omotac(Thread* running){
	 running->run();
	 PCB* help = NizPCB::primerak->uzmi(running->myPCBid);
	 help->omotac();
 }
ID Thread::getRunningId(){
	return PCB::running->dohvatiID();
}
Thread * Thread::getThreadById(ID id){
	return NizPCB::primerak->uzmi(id)->nit;
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}
ID Thread::getId(){
	return myPCBid;
}
