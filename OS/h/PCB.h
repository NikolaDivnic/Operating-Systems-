/*
 * PCB.h
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include"Thread.h"
#include "SCHEDULE.H"
#include "Liste.h"


const int NEW = 0;
const int READY = 1;
const int BLOCKED = 2;
const int DONE = 3;
class Sistem;
class PCB{

protected:
	Blokirane* blokirane;
	friend class Thread;
	unsigned* stek;
	StackSize kapacitet;
	ID id;
	Thread* nit;
	int stanje;
public:
	static PCB *running;
	unsigned ss,sp,bp;
	Time t;
	int dohvatiStanje();
	PCB(Thread *n = 0,StackSize kap = defaultStackSize,Time vreme = defaultTimeSlice);
	~PCB();
	void napraviStek();
	void postaviID(int i);
	int dohvatiID();
	Thread* dohvatiNit();
	void start ();
	void waitToComplete();
	void omotac();
	void postaviStanje(int s);

};

#endif /* PCB_H_ */
