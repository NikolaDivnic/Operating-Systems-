/*
 * IVTEntry.cpp
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "Sistem.h"
IVTEntry::IVTEntry(IVTNo ulaz,Sistem::pInterrupt rutina){
	old = 0;
	brojUlaza = ulaz;
	nova = rutina;
	dogadjaj = 0;
	Sistem::Tabela[ulaz]=this;
	#ifndef BCC_BLOCK_IGNORE
		old=getvect(ulaz);
		setvect(ulaz, nova);
	#endif
}

void IVTEntry::postaviDogadjaj(KernelEv* kev){
	dogadjaj = kev;
}
void IVTEntry::obrisi(){
	dogadjaj = 0;
}
void IVTEntry::signal(){
	if(dogadjaj!=0) dogadjaj->signal();
}
void IVTEntry::staraRutina(){
	(*old)();
}
IVTEntry::~IVTEntry(){
	Sistem::Tabela[brojUlaza] = 0;
	#ifndef BCC_BLOCK_IGNORE
		setvect(brojUlaza, old);
	#endif
}
