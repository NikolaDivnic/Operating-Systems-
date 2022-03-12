/*
 * IdleNit.h
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */

#ifndef IDLENIT_H_
#define IDLENIT_H_
#include"Thread.h"
class IdleNit: public Thread{

protected:

	static volatile int i;
public:

	IdleNit(Time t=1):Thread(defaultStackSize, t){}
	void run();
};
#endif /* IDLENIT_H_ */
