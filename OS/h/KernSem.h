/*
 * KernSem.h
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include"semaphor.h"

class KernSem {
	volatile int vrednost;

	void block();
	void deblock();
	friend class Semaphore;
	ID id;
	static ID IDD;
	int flegZaWait;
public:
	Blokirane* blokirane;
	Uspavane* uspavane;
	KernSem (int i=1);
	~KernSem ();
	//int wait ();
	void sleep(Time timeToSleep);
	int signal(int n);
	int wait(Time vreme);
	int dohvatiID()const;
	void postaviVrednost(int vred);
	int dohvatiVrednost()const;
	int duzinaBlokiranih();
	void smanjiSvakojVreme();
	Uspavane* dohvatiUspavane();
	void signalizirajZaWait();
	Blokirane* dohvatiBlokirane();
};


#endif /* KERNSEM_H_ */
