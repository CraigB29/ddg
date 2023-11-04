/******************************************************************************
  * File Name          : duck2.h
  * Description        : provides code for 'second' duck in 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/

#ifndef DUCK2_H
#define DUCK2_H


extern uint32_t duck2_complete;

void CLBK_SetDuck2Complete(void);

void Duck2_THREAD(void);


#endif DUCK2_H