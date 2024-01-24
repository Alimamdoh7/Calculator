/*
 * Calculator.h
 *
 * Created: 1/23/2024 11:07:50 AM
 *  Author: alima
 */ 


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "PORT_Core.h"
#include "LCD_Core.h"
#include "KeyPad_Core.h"

#define  Number_Of_Operands     15U
#define  Number_Of_Operations   10U

void Project_Init (void);
void Clear_Button (void);
void Operations_Buttons (void);
void Numbers_Buttons (void);
void App (void);
void Calculate (void);
void Multiplication (void);
void Division (void);
void MulDiv_Sequence(void);
void SumSub_Sequence(void);
void Division_By_Zero (void);


#endif /* CALCULATOR_H_ */