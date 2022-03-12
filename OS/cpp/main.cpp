#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"
#include"PCB.h"
#include"Thread.h"
#include"Sistem.h"
#include"semaphor.h"
#include"IVTEntry.h"
#include"user.h"



extern int userMain(int,char**);
int main(int argc, char* argv[]){


//	cout<<"main"<<endl;
	Sistem::init();
//	cout<<"main2 "<<endl;

	int rez = userMain(argc, argv);

    Sistem::restore();
   // cout<<"Zavrsen main"<<endl;
    return 0;

}
