/******************************************************************************
  * File Name          : goose.h
  * Description        : provides code for 'goose' in printed 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/

#ifndef GOOSE_H
#define GOOSE_H


     
     
extern uint32_t goose_complete;

void CLBK_SetGooseComplete(void);

void Goose_THREAD(void);


#endif GOOSE_H