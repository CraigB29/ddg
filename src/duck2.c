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
#include "rando_sleep.h"


//#define DUCK1_STACKSIZE       512

//#define DUCK1_PRIORITY       4


//#define MAX_UINT32_VALUE (0xffffffff)

extern struct k_sem duck2_semaphore;
 
uint32_t duck2_complete = 0;



void CLBK_SetDuck2Complete(void)
{
    duck2_complete = 1;
}


void Duck2_THREAD(void)
{
   
    while(1)
    {
        
        //between 2 to 3 second delay

        RandomSleepBounded(2000, 1, 999);

        
        //wait for clear to print from main thread
        k_sem_take(&duck2_semaphore, K_FOREVER);
        printk("duck2");
        CLBK_SetDuck2Complete();
    }
    

}






#ifdef asldfkjas
static uint32_t DUCK1_HLPR_GetRandomNumberBounded(uint32_t min, uint32_t max)
{
    //cast to accomodate calculation result size
        uint64_t result; 
        uint64_t min_ull = (uint64_t)min;
        uint64_t max_ull = (uint64_t)max;    

    //calculate result

        result = (uint64_t)(sys_rand32_get());
        result = (result*(max_ull-min_ull))/MAX_UINT32_VALUE;
        
        return (uint32_t)result;
}

static void DUCK1_RandomSleepBounded(uint32_t min_sleep_ms, uint32_t min_offset, uint32_t max_offset)
{

    
    uint32_t offset; 
    k_timeout_t calculated_delay;

    
    //constrain max/min to logical ranges

        if((max_offset+min_sleep_ms < min_sleep_ms) ) //indicates overflow
        {
            //adjust max offset to max possible.
            max_offset = MAX_UINT32_VALUE-(max_offset+min_sleep_ms);
        }

        if(min_offset>=max_offset)
        {
            min_offset = max_offset;
        }


    //calculate offset and resulting sleep delay

    offset = HLPR_GetRandomNumberBounded(min_offset, max_offset);
    calculated_delay.ticks = min_sleep_ms + offset;

    k_sleep(calculated_delay);
}

#endif


/*
K_THREAD_DEFINE(Duck1_THREAD_id, DUCK1_STACKSIZE, Duck1_THREAD, NULL, NULL, NULL,
        DUCK1_PRIORITY, 0, 0);


K_THREAD_DEFINE(Duck2_THREAD_id, DUCK2, Duck2_THREAD, NULL, NULL, NULL,
        DUCK2_PRIORITY, 0, 0);

K_THREAD_DEFINE(Goose_THREAD_id, 512, Goose_THREAD, NULL, NULL, NULL,
        GOOSE_PRIORITY, 0, 0);

K_THREAD_DEFINE(Main_THREAD_id, 512, Main_THREAD, NULL, NULL, NULL,
        MAIN_PRIORITY, 0, 0); 

        */

       