/*
 * KernelEv.h
 *
 *  Created on: Jun 24, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include"Sistem.h"
#include "Event.h"
class IVTEntry;
class KernelEv {
	int vrednost;
	ID myPCB;
	IVTNo brojUlaza;
public:
	KernelEv(IVTNo ulaz);
	virtual ~KernelEv();
	void signal();
	void wait ();
};

#endif /* KERNELEV_H_ */
