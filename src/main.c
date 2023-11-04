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

#include "duck1.h"
#include "duck2.h"
#include "goose.h"

#define MAIN_STACKSIZE        512
#define DUCK1_STACKSIZE       512
#define DUCK2_STACKSIZE       512
#define GOOSE_STACKSIZE       512




#define MAIN_PRIORITY        4
#define DUCK1_PRIORITY       4
#define DUCK2_PRIORITY       4
#define GOOSE_PRIORITY       4

#define MAX_UINT32_VALUE (0xffffffff)






K_SEM_DEFINE(duck1_semaphore, 0, 1);
K_SEM_DEFINE(duck2_semaphore, 0, 1);
K_SEM_DEFINE(goose_semaphore, 0, 1);



     
     
     




void Main_THREAD(void)
{


    while(1)
    {

	//signal duck1, duck2 and goose are clear to start count
	//k_sem_give(&duck1_complete);
	//k_sem_give()

    //signal duck1 thread is clear to print when ready
    k_sem_give(&duck1_semaphore);
   


	while(0!=k_sem_count_get(&duck1_semaphore))
	{
		k_yield();
	}
    //wait until duck1 callback was received (duck1 ran to completion (ie printed first 'duck'))
    while(duck1_complete==0)
    {
        k_yield();
    }
    duck1_complete = 0;

    printk(", ");
    

    
   

    //signal duck2 thread is clear to print when ready
    k_sem_give(&duck2_semaphore);

    //wait until duck2 callback was received (duck1 ran to completion (ie printed second 'duck'))
    while(duck2_complete==0)
    {
        k_yield();
    }
    duck2_complete = 0;
    printk(", ");

     


    //signal goose thread cleared to print when ready
    k_sem_give(&goose_semaphore);

    //wait until goose callback was received (goose ran to completion (ie printed goose))
    while(goose_complete==0)
    {
        k_yield();
    }
    goose_complete = 0;
    printk("\r\n");

    
    }
    
   

}


#ifdef asdfasdfasdf
static uint32_t HLPR_GetRandomNumberBounded(uint32_t min, uint32_t max)
{
    //cast to accomodate calculation result size
        uint64_t result; 
        uint64_t min_ull = (uint64_t)min;
        uint64_t max_ull = (uint64_t)max;

    //constrain max/min to logical ranges
    /*
        if(min_ull>max_ull)
        {
            min_ull = max_ull;
        }
    */
    

    //calculate result

        result = (uint64_t)(sys_rand32_get());
        result = (result*(max_ull-min_ull))/MAX_UINT32_VALUE;
        
        return (uint32_t)result;
}

void RandomSleepBounded(uint32_t min_sleep_ms, uint32_t min_offset, uint32_t max_offset)
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
    calculated_delay.ticks = 2000000000; //min_sleep_ms + offset;

	//k_busy_wait
	k_sleep(K_MSEC(2000));

    //k_sleep(calculated_delay);
}
#endif 

#ifdef ASDF
// Function for getting access of resource
void get_access(void)
{
	/* STEP 10.1 - Get semaphore before access to the resource */
	k_sem_take(&instance_monitor_sem, K_FOREVER);

	/* STEP 6.1 - Decrement available resource */

	available_instance_count--;
printk("Resource taken and available_instance_count = %d\n",  available_instance_count);

}

// Function for releasing access of resource
void release_access(void)
{
	/* STEP 6.2 - Increment available resource */
	available_instance_count++;
printk("Resource given and available_instance_count = %d\n", available_instance_count);

	/* STEP 10.2 - Give semaphore after finishing access to resource */
	k_sem_give(&instance_monitor_sem);

}

/* STEP 4 - Producer thread relinquishing access to instance */
void producer(void)
{
	printk("Producer thread started\n");
	while (1) {
		release_access();
		// Assume the resource instance access is released at this point
		k_msleep(500 + sys_rand32_get() % 10);
	}
}

/* STEP 5 - Consumer thread obtaining access to instance */
void consumer(void)
{
	printk("Consumer thread started\n");
	while (1) {
		get_access();
		// Assume the resource instance access is released at this point
		k_msleep(sys_rand32_get() % 10);
	}
}

#endif

// Define and initialize threads
/*
K_THREAD_DEFINE(producer_id, PRODUCER_STACKSIZE, producer, NULL, NULL, NULL,
		PRODUCER_PRIORITY, 0, 0);

K_THREAD_DEFINE(consumer_id, CONSUMER_STACKSIZE, consumer, NULL, NULL, NULL,
		CONSUMER_PRIORITY, 0, 0);
*/

K_THREAD_DEFINE(Duck1_THREAD_id, 512, Duck1_THREAD, NULL, NULL, NULL,
        DUCK1_PRIORITY, 0, 0);


K_THREAD_DEFINE(Duck2_THREAD_id, 512, Duck2_THREAD, NULL, NULL, NULL,
        DUCK2_PRIORITY, 0, 0);

K_THREAD_DEFINE(Goose_THREAD_id, 512, Goose_THREAD, NULL, NULL, NULL,
        GOOSE_PRIORITY, 0, 0);

K_THREAD_DEFINE(Main_THREAD_id, 512, Main_THREAD, NULL, NULL, NULL,
        MAIN_PRIORITY, 0, 0); 