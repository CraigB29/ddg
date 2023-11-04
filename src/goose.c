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


extern struct k_sem goose_semaphore;
 
uint32_t goose_complete = 0;


void CLBK_SetGooseComplete(void)
{
    goose_complete = 1;
}

//sleeps between 3 and 4 seconds then prints 'goose' when signaled by main

void Goose_THREAD(void)
{
   
    while(1)
    {

        
        //delay betwee 3 and 4 seconds
         
        RandomSleepBounded(3000, 1, 999);

        
        //wait for clear to print from main thread
        k_sem_take(&goose_semaphore, K_FOREVER);
        printk("goose");
        CLBK_SetGooseComplete();
    }
    

}






       