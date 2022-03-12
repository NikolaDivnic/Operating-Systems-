/*
 * PCB.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include"Sistem.h"
PCB* PCB::running  =0;
PCB::PCB(Thread *n,StackSize kap ,Time vreme){
	if (kap >65536) kap = 65536;
	nit = n;
	kapacitet = kap/sizeof(unsigned);
	t = vreme;
	id = 0;
	stek = 0;
	ss = 0;
	sp = 0;
	bp = 0 ;
	stanje = NEW;
	blokirane = new Blokirane();
}
void PCB::napraviStek(){
		stek = new unsigned[kapacitet];
			#ifndef BCC_BLOCK_IGNORE

			stek[kapacitet-1]=FP_SEG(nit);
			stek[kapacitet-2]=FP_OFF(nit);
			stek[kapacitet-3]=FP_SEG(&Sistem::dispatch);
			stek[kapacitet-4]=FP_OFF(&Sistem::dispatch);
			stek[kapacitet-5]=0x200;// PSW

			stek[kapacitet-6]=FP_SEG(&Thread::omotac);
			stek[kapacitet-7]=FP_OFF(&Thread::omotac);

			sp=FP_OFF(stek+kapacitet-16);
			ss=FP_SEG(stek+kapacitet-16);

			#endif
	}

PCB::~PCB() {
	if(id!=1) {
		delete[] stek;
		delete blokirane;
	}
}
void PCB::postaviStanje(int s){
	stanje = s;
}
void PCB::postaviID(int i){
	id = i;
}
int PCB::dohvatiID(){
	return id ;
}
Thread* PCB::dohvatiNit(){
	return nit;
}
void PCB::start (){
	napraviStek();
	stanje = READY;
	if(id!=0) {
		Scheduler::put(this);
	}
}
void PCB::waitToComplete(){
	if(PCB::running->dohvatiID()==id || stanje==NEW|| stanje==DONE ||id==0) return;
	PCB::running->postaviStanje(BLOCKED);
	this->blokirane->dodaj(PCB::running);
	Sistem::dispatch();
}

void PCB::omotac(){
	stanje = DONE;
	PCB* help2 = this->blokirane->uzmi();
	while(help2!=0){
		help2->postaviStanje(READY);
		Scheduler::put(help2);
		help2 = this->blokirane->uzmi();
	}
	//Sistem::dispatch();
}
int PCB::dohvatiStanje() {
	return stanje;
}
