/*
 * KernelEv.cpp
 *
 *  Created on: Jun 24, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include"IVTEntry.h"
KernelEv::KernelEv(IVTNo ulaz){
	myPCB = PCB::running->dohvatiID();
	vrednost = 0;
	brojUlaza = ulaz;
	IVTEntry* pom = Sistem::Tabela[brojUlaza];
	pom->postaviDogadjaj(this);
}

void KernelEv::wait(){
	if (PCB::running->dohvatiID()!=myPCB) return;

	vrednost--;
	if (vrednost<0){
		PCB*help = NizPCB::primerak->uzmi(myPCB);
		help->postaviStanje(BLOCKED);
		Sistem::dispatch();
	}

}

void KernelEv::signal(){
	if (vrednost>= 0){
		vrednost =1;
	}
	else {
		PCB* help = NizPCB::primerak->uzmi(myPCB);
		help->postaviStanje(READY);
		Scheduler::put(help);
		vrednost++;
		Sistem::dispatch();
	}

}

KernelEv::~KernelEv(){
	myPCB = 0;
	(Sistem::Tabela[brojUlaza])->obrisi();
}
