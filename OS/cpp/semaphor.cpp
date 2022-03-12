/*
 * semaphor.cpp
 *
 *  Created on: Jun 25, 2020
 *      Author: OS1
 */

#include "semaphor.h"
#include "Liste.h"
#include "KernSem.h"

Semaphore::Semaphore(int init) {
	myImpl  = new KernSem(init);
	NizSemafora::primerak->ubaci(myImpl);
}

Semaphore::~Semaphore() {
	NizSemafora::primerak->izbaci(myImpl->dohvatiID());
	delete myImpl;
}



int Semaphore::signal(int n){


		/*if (n>0){

			int pom;
			if (n< myImpl->dohvatiVrednost()){
				cout<<"n < myImpl->dohvtiVrednost vrednost za n ="<<n<<"vrednost myImpl= "<<
						myImpl->dohvatiVrednost()<<endl;
				for(int i=  0 ; i< n;i++){
					myImpl->deblock();
					cout<<"Pozvat deblok vrednost i = "<<i<<endl;
				}
				pom = n;
			}
			else {
				cout<<"n > myImpl->dohvtiVrednost"<<endl;
				pom = myImpl->dohvatiVrednost();
				for (int i = 0; i< myImpl->dohvatiVrednost();i++)	{
					myImpl->deblock();
					cout<<"Pozvat deblok vrednost i = "<<i<<endl;
				}
				cout<<"vrednost myImpl = "<<myImpl->dohvatiVrednost()<<endl;

				cout<<"vrednost posle dodavanja myImpl = "<<myImpl->dohvatiVrednost()<<endl;

			}
			myImpl->postaviVrednost( myImpl->dohvatiVrednost() + n);
			cout<<"Return broj odblokiranih niti"<<endl;
			return pom;

		}
		else{
			cout<<"N <0 "<<endl;
			return n;
		}*/
	//cout<<"Semafor signal vrednost "<<val()<<endl;
	return myImpl->signal(n);

}
int Semaphore::val () const{
	return myImpl->dohvatiVrednost();
}
int Semaphore::wait (Time vreme){
	//cout<<"wait u semafor"<<endl;
	return myImpl->wait(vreme);
}

