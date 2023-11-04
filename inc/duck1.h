 /******************************************************************************
  * File Name          : duck1.h
  * Description        : provides code for 'first' duck in 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/


#ifndef DUCK1_H
#define DUCK1_H
/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */




/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>
//#include <duck1.h>


#define DUCK1_STACKSIZE       512

//#define DUCK1_PRIORITY       4

//K_SEM_DEFINE(duck1_semaphore, 0, 1);



     
     
     
extern uint32_t duck1_complete;

void CLBK_SetDuck1Complete(void);


//void Duck1_THREAD(void);










#endif DUCK1_H