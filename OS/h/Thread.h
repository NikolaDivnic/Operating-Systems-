/*
 * Thread.h
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <iostream.h>
#include <dos.h>

#define lock asm pushf; \
                    asm cli;

#define unlock asm popf;

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
// Kernel's implementation of a user's thread
class PCB;
class NizPCB;

class Thread {

	public:
		void start();
		void waitToComplete();
		virtual ~Thread();
		ID getId();
		static void omotac(Thread* running);
		static ID getRunningId();
		static Thread * getThreadById(ID id);
	protected:
		friend class PCB;
		Thread (StackSize stackSize = defaultStackSize, Time timeSlice =defaultTimeSlice);
		virtual void run();
	private:
		static ID id;
		PCB* myPCB;
		ID myPCBid;

};
void dispatch ();



#endif /* THREAD_H_ */
