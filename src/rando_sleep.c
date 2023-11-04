/******************************************************************************
  * File Name          : random.h
  * Description        : provides random number and delay helper functions to 
  *                      the duck duck and goose tasks
  ******************************************************************************/

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>
#include "stdint.h"
#include "rando_sleep.h"


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
       result = (uint64_t)GeneratePseudoRandom();
        result = (result*(max_ull-min_ull))/0xffffffff;
       
        return (uint32_t)result;
        
}

void RandomSleepBounded(uint32_t min_sleep_ms, uint32_t min_offset, uint32_t max_offset)
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
