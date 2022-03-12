/*
 * Liste.h
 *
 *  Created on: Apr 27, 2020
 *      Author: OS1
 */

#ifndef LISTE_H_
#define LISTE_H_
#include "Thread.h"
class KernSem;
class KernelEv;
class PCB;

class NizPCB{

protected:
	void povecaj();
	int kapacitet;
	int broj;
	PCB** niz;

public:

	static NizPCB* primerak;
	NizPCB();
	void pokreni();
	int ubaci(PCB* p);
	PCB* uzmi(int i);
	void izbaci(int i);
	void obrisi();
};
class Element{

	friend class Red;
public:

		PCB* info;
		Time t;
		Element* next;

		Element(PCB* p=0,Time tt = 0);
};
class NizSemafora{
	void povecaj();
	int kapacitet;
	int broj;
	KernSem** niz;
public:
	static NizSemafora* primerak;
	NizSemafora();
	void pokreni();
	int ubaci(KernSem* p);
	KernSem* uzmi(int i);
	void izbaci(int i);
	void izbaciSem(KernSem*sem);
	void obrisi();
	int dohvatiKapacitet();
};
class Blokirane{
	int duzina;
public:

	Element* head ;
	Element* tail ;

	Blokirane();
	~Blokirane();
	void dodaj(PCB* p, Time t = -1);
	PCB* uzmi();
	int dohvatiDuzinu();
};
class Uspavane{
protected:

	Element* glava ;
	Element* rep ;
	int broj;
	KernSem* sem;
public:

	Uspavane(KernSem *sem);
	~Uspavane();
	void dodaj(PCB* p, Time t);
	PCB* uzmi();
	int proveri();
	void umanjiCekanje();
	void izbaci(int i);
	int josKoliko();
};

class NizDogadjaja{
	void povecaj();
		int kapacitet;
		int broj;
		KernelEv** niz;
	public:
		static NizDogadjaja* primerak;
		NizDogadjaja();
		void pokreni();
		int ubaci(KernelEv* p);
		KernelEv* uzmi(int i);
		void izbaci(int i);
		void izbaciSem(KernelEv*sem);
		void obrisi();
		int dohvatiKapacitet();
};
#endif /* LISTE_H_ */
