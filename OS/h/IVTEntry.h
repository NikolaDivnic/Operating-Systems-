/*
 * IVTEntry.h
 *
 *  Created on: May 10, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include <dos.h>


#include"Event.h"
#include"KernelEv.h"
//#include"Sistem.h"


class IVTEntry {
	IVTNo brojUlaza;
	KernelEv* dogadjaj;

public:
	void interrupt (*old)(...);
	void interrupt (*nova)(...);
	IVTEntry(IVTNo ulaz,void interrupt (*rutina)(...));
	void postaviDogadjaj(KernelEv* doga);
	virtual ~IVTEntry();
	void signal();
	void obrisi();
	void staraRutina();

};

#endif /* IVTENTRY_H_ */
