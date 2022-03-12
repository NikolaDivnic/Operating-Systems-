/*
 * Sistem.h
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#ifndef SISTEM_H_
#define SISTEM_H_
#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"
#include"PCB.h"
#include"Thread.h"
#include"IdleNit.h"
#include"Liste.h"
#include"KernSem.h"
#include"Event.h"
#include"IVTEntry.h"
class IVTEntry;

#define PREPAREENTRY(entryBr,flag)\
void interrupt entry##entryBr(...);\
IVTEntry newEntry##entryBr(entryBr, &entry##entryBr);\
void interrupt entry##entryBr(...){\
	if(flag) (newEntry##entryBr).old();\
	newEntry##entryBr.signal();\
	Sistem::dispatch();\
}



class Sistem {
public:
	//static Uspavane uspavane;
	static PCB* mainPCB;
	static IdleNit* idlenit;
	static void init();
	static void restore();
	static void dispatch();
	static IVTEntry* Tabela[];
	typedef void interrupt(*pInterrupt)(...);
	static volatile unsigned int flock ;
	static volatile int Sistem::zahtev;
};


#endif /* SISTEM_H_ */
