
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>
#include "rando_sleep.h"




extern struct k_sem duck2_semaphore;
 
uint32_t duck2_complete = 0;


//rough callback function
void CLBK_SetDuck2Complete(void)
{
    duck2_complete = 1;
}

//brief: duck2 thread runs every 2-3 seconds and prints when signaled by main
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











       