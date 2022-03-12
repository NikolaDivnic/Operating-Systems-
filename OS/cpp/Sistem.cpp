/*
 * Sistem.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: OS1
 */

#include "Sistem.h"
//#include"IVTEntry.h"

#include"user.h"
volatile unsigned int Sistem::flock = 1;
volatile int Sistem::zahtev=0;
typedef void interrupt(*pInterrupt)(...);
volatile int IdleNit::i = 1;
unsigned tsp;
unsigned tss;
IVTEntry* Sistem::Tabela[256];

unsigned oldTimerOFF =0, oldTimerSEG = 0;
volatile int brojac = 1;
volatile int zahtevana_promena_konteksta = 0;
extern void tick();

//PREPAREENTRY(8, 1);
//Uspavane Sistem::uspavane;
PCB* pom = 0;
Uspavane* uspavanee = 0 ;
KernSem* pomSem  =0 ;
Blokirane* blokirane;
volatile int i , j, brojBlokiranih;

void interrupt timer(){

	if (!zahtevana_promena_konteksta && brojac>0 ) {
			if (brojac>0) brojac--;
			tick();
			for (i = 0 ; i < NizSemafora::primerak->dohvatiKapacitet(); i++){
				pomSem = NizSemafora::primerak->uzmi(i);
				if (pomSem!=0){
					uspavanee = pomSem->dohvatiUspavane();
					//uspavane = pomSem->dohvatiUspavane();
					if (uspavanee != 0 && uspavanee->proveri()!=-1){
						uspavanee->umanjiCekanje();
						while(uspavanee->proveri()==0){
							pomSem->signalizirajZaWait();
							//pom = uspavanee->uzmi();
							pomSem->signal(1);
							if(pom!=0){
								pom->postaviStanje(READY);
								Scheduler::put(pom);
							}
						}
					}
					else {
						//	cout<<endl<<endl<<"Uslo u else granu u timeru"<<endl<<endl<<endl;
						/*	blokirane = pomSem->dohvatiBlokirane();
							if (blokirane!=0){
								pom = blokirane->uzmi();
							}
							if(pom!=0){
								pom->postaviStanje(READY);
								Scheduler::put(pom);
							}
*/
					}
				}
			}
	}

		if (brojac == 0 || zahtevana_promena_konteksta) {
			if (Sistem::flock){
				Sistem::flock = 0;
			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
			}

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			if (PCB::running->dohvatiStanje()==READY && PCB::running->dohvatiID()!=0 ){
				Scheduler::put(PCB::running);
			}

			PCB::running = Scheduler::get();
			if (PCB::running == 0){
				PCB::running = NizPCB::primerak->uzmi(0);
			}

			if (PCB::running->t>0){
				brojac = PCB::running->t;
			}
			else{

				brojac = -1;
			}
			tsp = PCB::running->sp;
			tss = PCB::running->ss;

			asm {
				mov sp, tsp
				mov ss, tss
			}
			Sistem::flock = 1;
		}
		else {
			Sistem::zahtev = 1;
		}
		}
	if(!zahtevana_promena_konteksta) asm int 60h;

		zahtevana_promena_konteksta = 0;
}

void inic(){
	asm{
					cli
					push es
					push ax

					mov ax,0   //  ; inicijalizuje rutinu za tajmer
					mov es,ax

					mov ax, word ptr es:0022h //; pamti staru rutinu
					mov word ptr oldTimerSEG, ax
					mov ax, word ptr es:0020h
					mov word ptr oldTimerOFF, ax

					mov word ptr es:0022h, seg timer	 //postavlja
					mov word ptr es:0020h, offset timer //novu rutinu

					mov ax, oldTimerSEG	 //	postavlja staru rutinu
					mov word ptr es:0182h, ax //; na int 60h
					mov ax, oldTimerOFF
					mov word ptr es:0180h, ax

					pop ax
					pop es
					sti
				}
}
void restor(){
		asm {
				cli
				push es
				push ax

				mov ax,0
				mov es,ax


				mov ax, word ptr oldTimerSEG
				mov word ptr es:0022h, ax
				mov ax, word ptr oldTimerOFF
				mov word ptr es:0020h, ax

				pop ax
				pop es
				sti
			}
}
IdleNit* Sistem::idlenit=0;
PCB* Sistem::mainPCB=0;
void Sistem::dispatch(){ // sinhrona promena konteksta
	asm cli;
	zahtevana_promena_konteksta = 1;
	timer();
	asm sti;
}

void Sistem::init(){

	NizPCB::primerak->pokreni();
	NizSemafora::primerak->pokreni();
	NizDogadjaja::primerak->pokreni();
	Sistem::idlenit = new IdleNit();
	Sistem::mainPCB = new PCB();
	Sistem::mainPCB->postaviID(NizPCB::primerak->ubaci(Sistem::mainPCB));
	PCB::running = Sistem::mainPCB;
	PCB::running->t = 2;
	brojac = 2;
	PCB::running->postaviStanje(READY);
	Sistem::idlenit->start();

	inic();
/*#ifndef BCC_BLOCK_IGNORE
	asm cli;
	Sistem::old=getvect(0x08);
	setvect(0x08, timer);
	setvect(0x60, Sistem::old);
	asm sti;
#endif*/
}
void Sistem::restore(){
	restor();
/*	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax


			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}*/
/*#ifndef BCC_BLOCK_IGNORE
	setvect(0x08, old);
#endif*/
}


