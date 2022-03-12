/*
 * KernSem.cpp
 *
 *  Created on: May 4, 2020
 *      Author: OS1
 */

#include "KernSem.h"
#include"PCB.h"
#include"Sistem.h"
ID KernSem::IDD = 0;
KernSem::KernSem(int i) {
	vrednost = i;
	blokirane = new Blokirane();
	uspavane = new Uspavane(this);
	id = IDD;
	IDD = IDD +1;
	flegZaWait = 0;
}
int KernSem::dohvatiID()const{
	return id;
}
KernSem::~KernSem() {
	delete blokirane;
	delete uspavane;
	NizSemafora::primerak->izbaciSem(this);
}

int KernSem::wait (Time vreme){

	vrednost--;
	if (vrednost<0){
		if (vreme == 0){
			//cout<<"kernsem wait block"<<endl;
			block();
			Sistem::dispatch();
			return 1;
		}
		else{
			//cout<<"KernSem wait sleep"<<endl;
			//int pom = PCB::running->dohvatiID();

			sleep(vreme);
			Sistem::dispatch();
			if (flegZaWait){
				flegZaWait--;
				return 0;
			}
		}
	}
	return 1;
}
int KernSem::signal(int n){
	int fleg = 0;
	int i = 0;
	int pom = 0;
	int pom2  = -dohvatiVrednost();
//	cout <<"Signal kernSem -vrednost"<<pom2<<endl;
	if (n<0){
		//cout<<"n <0"<<n<<endl;
		return n;
	}
	if (n == 0){
		pom = 1;
		fleg = 1;
		n = 1;
	}
	if (dohvatiVrednost()<0){
		if (n == 0){
			deblock();
			postaviVrednost( dohvatiVrednost() + pom);
	//		cout<<"Pozvat deblok n = 0" <<endl;
			return 0;
		}
		else {
			if (n>-dohvatiVrednost()){

				for ( i = 0 ; i < pom2;i++){
					deblock();
			//		cout<<"Pozvat deblok vrednost i = "<<i << "  vrednost pom2  ="<<pom2 <<endl;
				}
				pom = -dohvatiVrednost();
			}
			else {
				for ( i = 0 ; i < n;i++){
					deblock();
				//	cout<<"Pozvat deblok vrednost i = "<<i << "  vrednost n ="<<n<<endl;
				}
				pom = n;
			}
		}

	}
	else {
		pom = n;
	}

	if (fleg){
		postaviVrednost( dohvatiVrednost() + 1);
	}
	else {
		postaviVrednost( dohvatiVrednost() + n);
	}
//	cout<<"vrednost semafora izlaz iz signala  "<<dohvatiVrednost()<<endl;
	return pom;
}
void KernSem::block(){
	PCB::running->postaviStanje(BLOCKED);
	blokirane->dodaj(PCB::running);
}
void KernSem::deblock(){

	PCB* pom  = 0;
	pom = uspavane->uzmi();

	if (pom==0){
		pom = blokirane->uzmi();
	}
	if(pom){
		pom->postaviStanje(READY);
		Scheduler::put(pom);
	}

}
void KernSem::postaviVrednost(int vred){
	vrednost = vred;
}
int KernSem::dohvatiVrednost()const{
	return vrednost;
}
void KernSem::sleep(Time vreme){
	if (vreme == 0) return;
	//Time vr = (int)(vreme/55);
	//if (vr==0) vr++;
	PCB::running->postaviStanje(BLOCKED);
	uspavane->dodaj(PCB::running,vreme);
}
int KernSem::duzinaBlokiranih(){
	return blokirane->dohvatiDuzinu();
}
void KernSem::smanjiSvakojVreme(){
	Element*tek = blokirane->head;
	Element*pred = 0;
	while (tek!=0){
		tek->t--;
		if (tek->t==0){
			Scheduler::put(tek->info);
			if (blokirane->head != blokirane->tail)
					{
						pred->next = tek->next;
						tek = tek->next;
					}
			else {
				delete tek;return;
			}
		}
		else {
			pred = tek;
			tek = tek->next;
		}

	}
}

Uspavane* KernSem::dohvatiUspavane(){
	return uspavane;
}
void KernSem::signalizirajZaWait(){
	flegZaWait++;
}

Blokirane* KernSem::dohvatiBlokirane(){
	return blokirane;
}
