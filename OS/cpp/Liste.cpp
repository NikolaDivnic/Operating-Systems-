/*
 * Liste.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: OS1
 */

#include "Liste.h"
#include "PCB.h"
#include"KernelEv.h"
#include <iostream.h>
#include "KernSem.h"
NizPCB* NizPCB::primerak = new NizPCB();
NizSemafora* NizSemafora::primerak = new NizSemafora();
NizDogadjaja* NizDogadjaja::primerak = new NizDogadjaja();
NizPCB::NizPCB(){
	kapacitet = 50;
	broj = 0;
	niz = new PCB*[50];
}

void NizPCB::pokreni(){
	for (int i = 0 ; i < kapacitet; i++){
		niz[i] = 0 ;
	}
}

void NizPCB::povecaj(){
	PCB** niz2 = new PCB*[kapacitet+10];
	for (int i = 0 ; i < kapacitet+10;i++ ){
		if (i<kapacitet) niz2[i] = niz[i];
		else niz2[i] = 0;
	}
	kapacitet +=10;
	delete niz;
	niz = niz2;
	niz2 = 0;
}

int NizPCB::ubaci(PCB* p){

	int index = -1;
	if (broj == kapacitet) {
		povecaj();
		niz[broj] = p;
		index = broj;
		broj++;
		return index;
	}
	else {
		for(int i = 0 ; i < kapacitet;i++){
			if (niz[i] == 0){
				index = i;
				niz[i] = p;
				broj++;
				return index;
			}
		}
	}
	return index;
}

PCB* NizPCB::uzmi(int i){

	if (i<0 || i>=kapacitet) return 0;
	else return niz[i];
}

void NizPCB::izbaci(int i){
	if (i<0 || i>=kapacitet) return;
	else {
		niz[i] =0 ;
		broj--;
	}
}

void NizPCB::obrisi(){
	delete niz;
}



Element::Element(PCB* p,Time tt ){
	info = p ;
	t = tt;
	next = 0;
}


Blokirane::Blokirane(){
	head = 0;
	duzina = 0;
	tail = 0;
}

Blokirane::~Blokirane(){
	Element* help = head;
	while(help!=0){
		head = head->next;
		delete help;
		help = head;
	}
	tail = 0;
}

void Blokirane::dodaj(PCB* p ,Time t){

		if (head == 0){
			head = new Element(p, t);
			tail = head;
		}
		else{
			Element* help = new Element(p ,t);
			tail->next = help;
			tail = tail->next;
		}
		duzina++;
}

PCB*Blokirane:: uzmi(){

		if (head == 0) return 0;
		Element* help = head;
		if (head == tail) {
			head = 0;
			tail = 0;
		}
		else head = head->next;
		PCB* p = help->info;
		delete help;
		duzina--;
		return p;
}


int Blokirane::dohvatiDuzinu(){
	return duzina;
}

NizSemafora::NizSemafora(){
	kapacitet = 5;
	broj = 0;
	niz = new KernSem*[5];
}
void NizSemafora::pokreni(){
	for (int i = 0 ; i < kapacitet; i++){
			niz[i] = 0 ;
	}
}
void NizSemafora::povecaj(){
	KernSem** niz2 = new KernSem*[kapacitet+5];
	for (int i = 0 ; i < kapacitet+5;i++ ){
		if (i<kapacitet) niz2[i] = niz[i];
		else niz2[i] = 0;
	}
	kapacitet +=5;
	delete niz;
	niz = niz2;
	niz2 = 0;
}
int NizSemafora::ubaci(KernSem* p){
	int index = -1;
	if (broj == kapacitet){
		povecaj();
		niz[broj] = p;
		index = broj;
		broj = broj +1;
	}
	else{
		for (int i = 0 ; i < kapacitet;i++){
			if (niz[i]==0){
				niz[i] = p;
				index = i;
				broj = broj +1;
				return index;
			}
		}
	}
	return index;
}
KernSem* NizSemafora::uzmi(int i){
	if (i<0 || i>= kapacitet)return 0;
	return niz[i];
}
void NizSemafora::izbaci(int i){
	if (i < 0|| i>=kapacitet) return ;
	niz[i] = 0;
	broj  = broj-1;

}
void NizSemafora::izbaciSem(KernSem*sem){
	for (int i  = 0; i < kapacitet ; i++){
		if (sem == niz[i])izbaci(i);
	}
}
void NizSemafora::obrisi(){
	delete niz;
}
int NizSemafora::dohvatiKapacitet(){
	return kapacitet;
}


Uspavane::Uspavane(KernSem* k){
	broj = 0;
	glava  = 0;
	rep = 0;
	sem = k;
}
Uspavane::~Uspavane(){
	Element* tek = glava;
		while(glava!=0){
			glava = glava->next;
			delete tek;
			tek =glava;
		}
		tek = 0;
}
void Uspavane::dodaj(PCB* p, Time t){

	if (glava == 0) {
		glava = new Element(p, t);
			rep = glava;
		}
		else {
			Element* help = glava;
			while (help != 0) {
				if (t>help->t) {
					t -= help->t;
					if (help == rep) {
						help = new Element(p, t);
						rep->next = help;
						rep = help;
						help = 0;
					}
					else {
						help = help->next;
					}
				}
				else {
					if (help == glava) {
						help = new Element(p, t);
						help->next = glava;
						glava->t -= t;
						glava = help;
						help = 0;
					}
					else {
						Element* novi = new Element(help->info, help->t-t);

						novi->next = help->next;
						help->next = novi;
						help->info = p;
						help->t = t;
						help = 0;
						if (rep->next!=0) rep = rep->next;
					}
				}
			}
		}
	broj = broj + 1;
//	cout<<"dodavanje izlaz broj niti "<<broj<<"poslednja dodata"<<p->dohvatiID()<<endl;
}
PCB* Uspavane::uzmi(){
	if (glava== 0)return 0 ;
	PCB*pom  = glava->info;
	if (glava == rep) rep =0;
	Element*pp= glava;
	glava = glava->next;
	glava->t = pp->t + glava->t;
	delete pp;
	return pom;

}
int Uspavane::proveri(){
	//cout<<"Proveri vreme ulaz"<<endl;
	if (glava != 0)return glava->t;
	return -1;
}
void Uspavane::umanjiCekanje(){
	//cout<<"Umanji cekanje"<<endl;
	if(glava!=0){
	//	cout<<"Umanji cekanje glava != 0"<<endl;
		glava->t = glava->t -1 ;
	}
	//cout<<"Umanji cekanje izlaz"<<glava->t<<endl;
}

void Uspavane::izbaci(int i){
	if (i<0||i>=broj)return;
	if (i == 0){
		uzmi();
	}
	else if (i == broj -1){
		Element* tek = glava;
		while(tek->next!= rep){
			tek = tek->next;
		}
		delete rep;
		rep = tek;
	}
	else{
		int j =0;
		Element*tek = glava;
		Element*pom = 0;
		while(j< i){
			j++;
			pom = tek;
			tek = tek->next;
		}
		pom->next  = tek->next;
		delete tek;
	}


}
int Uspavane::josKoliko(){
	if (glava == 0) return -1;
	return glava->t;
}

NizDogadjaja::NizDogadjaja(){
	kapacitet = 5;
	broj = 0;
	niz = new KernelEv*[5];
}
void NizDogadjaja::pokreni(){
	for (int i = 0 ; i < kapacitet; i++){
			niz[i] = 0 ;
	}
}
void NizDogadjaja::povecaj(){
	KernelEv** niz2 = new KernelEv*[kapacitet+5];
	for (int i = 0 ; i < kapacitet+5;i++ ){
		if (i<kapacitet) niz2[i] = niz[i];
		else niz2[i] = 0;
	}
	kapacitet +=5;
	delete niz;
	niz = niz2;
	niz2 = 0;
}
int NizDogadjaja::ubaci(KernelEv* p){
	int index = -1;
	if (broj == kapacitet){
		povecaj();
		niz[broj] = p;
		index = broj;
		broj = broj +1;
	}
	else{
		for (int i = 0 ; i < kapacitet;i++){
			if (niz[i]==0){
				niz[i] = p;
				index = i;
				broj = broj +1;
				return index;
			}
		}
	}
	return index;
}
KernelEv* NizDogadjaja::uzmi(int i){
	if (i<0 || i>= kapacitet)return 0;
	return niz[i];
}
void NizDogadjaja::izbaci(int i){
	if (i < 0|| i>=kapacitet) return ;
	niz[i] = 0;
	broj  = broj-1;

}
void NizDogadjaja::izbaciSem(KernelEv*sem){
	for (int i = 0 ; i <kapacitet;i++){
		if (niz[i] == sem){
			this->izbaci(i);
			return;
		}
	}
}
void NizDogadjaja::obrisi(){
	delete niz;
}
int NizDogadjaja::dohvatiKapacitet(){
	return kapacitet;
}

