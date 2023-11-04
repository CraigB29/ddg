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
#include "stdint.h"
#include "rando_sleep.h"



extern struct k_sem duck1_semaphore;
 
uint32_t duck1_complete = 0;


//rough callback (out of time)
void CLBK_SetDuck1Complete(void)
{
    duck1_complete = 1;
}


//sleeps between 1 and 2 seconds then prints when signaled my main


void Duck1_THREAD(void)
{
   
    while(1)
    {   
      
        //between 1 to 2 second delay

        RandomSleepBounded(1000, 1, 999);
        
        //wait for clear to print from main thread
        k_sem_take(&duck1_semaphore, K_FOREVER);
        printk("duck1");
        CLBK_SetDuck1Complete();
    }
    

}




       