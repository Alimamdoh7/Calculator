/*
 * Calculator.c
 *
 * Created: 1/23/2024 11:07:38 AM
 *  Author: Ali Mamdoh
 */ 

#include "Calculator.h"

sint32 Numbers[Number_Of_Operands]={0};
uint8 Operations[Number_Of_Operations]={0};
uint8 Key_Value =0;
sint32 result=0;
uint8 Division_By_Zero_Flag=0;
uint8 num_cntr=0 , op_cntr=0;
uint8 i=0 , j=0;

void Project_Init (void)
{
	PORT_Init();
	LCD_Init();
	KeyPad_Init();
	LCD_GoTo(0,0);
	LCD_WriteString("Calculator");
	_delay_ms(2000);
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteString("Made By:");
	LCD_GoTo(1,0);
	LCD_WriteString("Ali Mamdoh");
	_delay_ms(2000);
	LCD_Clear();
}

void Clear_Button (void)
{
	 LCD_Clear();
	 Division_By_Zero_Flag=0;
	 op_cntr=0;
	 num_cntr=0;
	 result=0;
	 for (i=0; i<Number_Of_Operations ; i++)
	 {
		 Operations[i]=0;
	 }
	 for (j=0 ; j<Number_Of_Operands ; j++)
	 {
		 Numbers[j]=0;
	 }
}

void Operations_Buttons (void)
{
	Operations[op_cntr] = Key_Value;
	num_cntr++;
	op_cntr++;
}

void Numbers_Buttons (void)
{
	Numbers[num_cntr] *=10;
	Numbers[num_cntr] += (Key_Value -'0');
}

void App (void)
{
	 Key_Value = KeyPad_GetValue();
	 if (Key_Value !=0)
	 {
		 LCD_WriteChar(Key_Value);

		 if (Key_Value == 'x' || Key_Value == '/' || Key_Value == '+' || Key_Value == '-')
		 {
			 Operations_Buttons();
		 }
		 else if (Key_Value >= '0' && Key_Value <= '9')
		 {
			 Numbers_Buttons();
		 }
		 else if (Key_Value == '=')
		 {
			 Calculate();
			 Calculate();
		 }
		 else if (Key_Value == 'c')
		 {
			Clear_Button();
		 }
	 }
}

void Calculate (void)
{
	MulDiv_Sequence();
	SumSub_Sequence();
	
	if (Division_By_Zero_Flag == 1)
	{
		Division_By_Zero();
	}
	else
	{
		LCD_GoTo(1,0);
		LCD_WriteInteger(result);
	}
}

void Division_By_Zero (void)
{
	LCD_GoTo(1,0);
	LCD_WriteString("Math Error");
	_delay_ms(2000);
	Division_By_Zero_Flag=0;
	op_cntr=0;
	num_cntr=0;
	result=0;
	for (i=0; i<Number_Of_Operations ; i++)
	{
		Operations[i]=0;
	}
	for (j=0 ; j<Number_Of_Operands ; j++)
	{
		Numbers[j]=0;
	}
	LCD_Clear();
}

void MulDiv_Sequence (void)
{
	for (i=0 ; i < op_cntr ; i++)
	{
		if (Operations[i] == 'x' && Operations[i+1]== '/')
		{
			while (Operations[i] == 'x' && Operations[i+1] == '/')
			{
				Multiplication();
				Division();
			}
		}
		else if (Operations[i] == '/' && Operations[i+1] == 'x')
		{
			while (Operations [i] == '/' && Operations[i+1] == 'x')
			{
				Division();
			    Multiplication();
			}
		}
		else 
		{
			if (Operations[i] == 'x')
			{
				while (Operations [i] == 'x')
				{
					Multiplication();
				}
			}
			else if (Operations[i] == '/')
			{
				while (Operations [i] == '/')
				{
					Division();
				}
			}
		}
	}
	result = Numbers[0];	
}

void Multiplication (void)
{
	Numbers[i] *=  Numbers[i+1] ;
	for (j=i; j < op_cntr ; j++)
	{
		Operations[j] = Operations[j+1];
		Numbers[j+1] = Numbers [j+2];
	}
}

void Division (void)
{
	if (Numbers[i+1] == 0)
	{
		Division_By_Zero_Flag=1;
	}
	else if (Numbers[i+1] != 0)
	{
		Numbers[i] /=  Numbers[i+1] ;
	}
	for (j = i; j<op_cntr ; j++)
	{
		Operations[j] = Operations[j+1];
		Numbers[j+1] = Numbers[j+2];
	}
}

void SumSub_Sequence (void)
{
	for(i = 0 ; i < op_cntr; i++)
	{
		if(Operations[i] == '+')
		result += Numbers[i+1];

		else if (Operations[i] == '-')
		result -= Numbers[i+1];
	}
}