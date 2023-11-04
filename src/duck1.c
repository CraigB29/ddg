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



//static uint32_t GetRandomNumberBounded(uint32_t min, uint32_t max);
//static void RandomSleepBounded(uint32_t min_sleep_ms, uint32_t min_offset, uint32_t max_offset);
//#include <duck1.h>


//#define DUCK1_STACKSIZE       512

//#define DUCK1_PRIORITY       4


//#define MAX_UINT32_VALUE (0xffffffff)

extern struct k_sem duck1_semaphore;
 
uint32_t duck1_complete = 0;



void CLBK_SetDuck1Complete(void)
{
    duck1_complete = 1;
}


void Duck1_THREAD(void)
{
   
    while(1)
    {   
        //wait until signaled to proceed by main 
       // k_sem_take(&duck1_semaphore);
        //between 1 to 2 second delay

        RandomSleepBounded(1000, 1, 999);
        
        //wait for clear to print from main thread
        k_sem_take(&duck1_semaphore, K_FOREVER);
        printk("duck1");
        CLBK_SetDuck1Complete();
    }
    

}



/*
static uint32_t GeneratePseudoRandom(void)
{
    static uint32_t seed = 533;

    uint32_t time = k_uptime_get_32();

    

    if(time & 0x00000001)
    {
        seed = seed*time;
    }
    else
    {
        seed = seed/time;
    }

    
    return seed;


}


static uint32_t GetRandomNumberBounded(uint32_t min, uint32_t max)
{
    
    //cast to accomodate calculation result size
        uint64_t result; 
        uint64_t min_ull = (uint64_t)min;
        uint64_t max_ull = (uint64_t)max;  
        uint32_t temp;  

    //calculate result

        //temp = sys_rand32_get();
       // result = (uint64_t)(temp);
       result = GeneratePseudoRandom();
        result = (result*(max_ull-min_ull))/0xffffffff;
       
        return (uint32_t)result;
        
}

static void RandomSleepBounded(uint32_t min_sleep_ms, uint32_t min_offset, uint32_t max_offset)
{

    
    uint32_t offset;
    uint32_t calculated_delay_ms;

    
    //constrain max/min to logical ranges

        if((max_offset+min_sleep_ms < min_sleep_ms) ) //indicates overflow
        {
            //adjust max offset to max possible.
            max_offset = 0xffffffff-(max_offset+min_sleep_ms);
        }

        if(min_offset>=max_offset)
        {
            min_offset = max_offset;
        }


    //calculate offset and resulting sleep delay

    //offset = GetRandomNumberBounded(min_offset, max_offset);
    offset = GetRandomNumberBounded(min_offset, max_offset);
    calculated_delay_ms = min_sleep_ms + offset;

    //k_sleep(calculated_delay);

    k_sleep(K_MSEC(calculated_delay_ms));

    
}
*/



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

       