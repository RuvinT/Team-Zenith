#ifndef F_CPU
#define F_CPU 10000000UL // 10 MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTD0
#define EN eS_PORTD1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

short place=2; short raw=2; 
int num[4];
int *new_num1,*new_num2,*new_num3,*new_num4,*new_num;
int x=0,flag=0;

void keypad1();

void keypad();

void password_Reset_b1();
void password_set_b1();
void password_Reset_b2();
void password_set_b2();
int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0x0F;
	PORTC=0b00001010;
	
    DDRA = 0xFC;//first four input other four output
	Lcd4_Init();
	//function to select box
	PORTD &=~(1<<PIND3);
	PORTD &=~(1<<PIND2);
	PORTA|=(1<<PINA2);
	while(1){
	
		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("press the key");
		_delay_ms(300);
		
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("1 to use B1");
		_delay_ms(100);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String("2 to use B2");
		_delay_ms(300);
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("3 to unlock B1");
		_delay_ms(100);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String("4 to unlock B2");
	
	
		_delay_ms(10);
		keypad1();
		Lcd4_Clear();
		
		while(1){
			PORTB|=(1<<PINB0);
			//box1 unlock
			if((bit_is_set (PINB,6))&&(bit_is_set(PINC,6)))
			{
				
				flag=1;
				password_Reset_b1();
				_delay_ms(10);

				break;
			}else
			//box1 if not use
			if((bit_is_set(PINB,4))&&(!(bit_is_set(PINC,6))))
			{
				
				_delay_ms(100);
				password_set_b1();
				PORTA|=(1<<PINA6);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("Enter a coin");//loop a4 to detect coin enterd
				PORTC|=(1<<PINC0);
				while(!(bit_is_set(PINA,0)));
				PORTC|=(1<<PINC6);
				PORTC &=~(1<<PINC0);
				PORTD|=(1<<PIND3);
				PORTC &=~(1<<PINC1);
				PORTA &=~(1<<PINA6);
				break;
			}else
			//box2 if not use
			if((bit_is_set (PINB,5))&&(!(bit_is_set(PINC,7))))
			{
		
				_delay_ms(100);
				password_set_b2();
				PORTA|=(1<<PINA7);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("Enter a coin");//loop a4 to detect coin enterd
				PORTC|=(1<<PINC0);
				while(!(bit_is_set(PINA,1)));
				PORTC|=(1<<PINC7);
					PORTC &=~(1<<PINC0);
					PORTA &=~(1<<PINA7);
					PORTD|=(1<<PIND2);
					PORTA &=~(1<<PINA2);
				break;
			}else
			

			
			
			


			//box1 if in use
			if((bit_is_set (PINB,4))&&(bit_is_set(PINC,6)))
			{
				Lcd4_Set_Cursor(1,1);
				
				Lcd4_Write_String("sorry B1 in use");
				
				_delay_ms(500);
				Lcd4_Clear();
				break;
			}else
			//box2 if in use
			if((bit_is_set (PINB,5))&&(bit_is_set(PINC,7)))
			{
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("sorry B2 in use");
				
				_delay_ms(500);
				Lcd4_Clear();

				break;
			}else
			//try to unlock when nothing in it
			if((bit_is_set (PINB,6))&&(!(bit_is_set(PINC,6))))
			{
				
				Lcd4_Write_String("wrong input");
				_delay_ms(200);

				break;
			}
			PORTB&=~(1<<PINB0);
			PORTB|=(1<<PINB1);
			_delay_ms(20);
			//box2 unlock
			if((bit_is_set(PINB,4))&&(bit_is_set(PINC,7)))
			{
				password_Reset_b2();
				flag=2;
				_delay_ms(500);
				
				break;
			}else
			if((bit_is_set (PINB,4))&&(!(bit_is_set(PINC,7))))
			{
				Lcd4_Write_String("Wrong input");
				
				_delay_ms(200);
				PORTB&=~(1<<PINB1);
			break;}
			PORTB&=~(1<<PINB1);
			
		}
		Lcd4_Clear();
		
		
	

	if(flag==1){
		if(new_num1==new_num2){
			Lcd4_Clear();
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String("Door B1 open");
			PORTA&=~(1<<PINA6);
			PORTA|=(1<<PINA4);
			PORTC&=~(1<<PINC6);
			flag=0;
			PORTC|=(1<<PINC1);
			PORTD &=~(1<<PIND3);
			_delay_ms(1000);
			PORTA&=~(1<<PINA4);
			Lcd4_Clear();
			
		}else{Lcd4_Write_String("Password wrong");
			_delay_ms(200);
			while(1){if(new_num1==new_num2){flag=0;
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("Door B1 open");
				PORTA&=~(1<<PINA6);
				PORTA|=(1<<PINA4);
				PORTC&=~(1<<PINC6);
				PORTC|=(1<<PINC1);
				PORTD &=~(1<<PIND3);
				_delay_ms(500);
				
				PORTA&=~(1<<PINA4);
			break;
			}else password_Reset_b1();
				
			}
		
		
			_delay_ms(10);
			Lcd4_Clear();
			
		}
		}
		if(flag==2){
			if(new_num3==new_num4){
				
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String("Door B2 open");
				PORTA|=(1<<PINA5);
				PORTA&=~(1<<PINA7);
				PORTC&=~(1<<PINC7);
				PORTA|=(1<<PINA2);
				PORTD &=~(1<<PIND2);
				flag=0;
				_delay_ms(500);
				PORTA&=~(1<<PINA5);
				Lcd4_Clear();
				
				}else{
					Lcd4_Write_String("Password wrong");
					_delay_ms(200);
				while(1){if(new_num3==new_num4){
					flag=0;
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String("Door B2 open");
					PORTA&=~(1<<PINA7);
					PORTA|=(1<<PINA5);
					PORTC&=~(1<<PINC7);
					PORTC|=(1<<PINC3);
					PORTD &=~(1<<PIND2);
					_delay_ms(500);
					PORTA&=~(1<<PINA5);
					break;
				}else password_Reset_b2();

				}
				
				Lcd4_Clear();
				
			}
		
	}
	}
}
	
	
	
	void password_set_b1(){
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Enter password : ");
		
		_delay_ms(100);
		

	//*********************************************************************************************************************************************	
		Lcd4_Set_Cursor(2,1);
		keypad();
		
		
		new_num1=(num[0]*1000)+(num[1]*100)+(num[2]*10)+num[3];
		
		
		_delay_ms(100);
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Close the door");
		
		_delay_ms(200);
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("press any key");
		_delay_ms(200);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String("when door closed");
		keypad1();
		Lcd4_Clear();

	}
	//*****************************************************************
	void password_Reset_b1(){
		_delay_ms(20);
		Lcd4_Clear();
		Lcd4_Write_String("Renter password:");
		

		
		Lcd4_Set_Cursor(2,1);
		keypad();
		new_num2=(num[0]*1000)+(num[1]*100)+(num[2]*10)+num[3];
		
		
		
		Lcd4_Clear();

	}
	
	void password_set_b2(){
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Enter password : ");
		
		_delay_ms(100);
		

		
		Lcd4_Set_Cursor(2,1);
		keypad();
	new_num3=(num[0]*1000)+(num[1]*100)+(num[2]*10)+num[3];
	
		
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Close the door");
		
		_delay_ms(200);
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("press any key");
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String("when door closed");
		keypad1();
		Lcd4_Clear();

	}
	void password_Reset_b2(){
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Renter password:");
		keypad();
		_delay_ms(50);
		
new_num4=(num[0]*1000)+(num[1]*100)+(num[2]*10)+num[3];
		
	
		
		
		Lcd4_Clear();

	}

void keypad(){x=0;
	do{
		if(x<=3){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("_");
		}
		else{x=0;place=2;
		break;}

		PORTB|=1<<PINB0;
		_delay_ms(1);

		if(bit_is_set(PINB,4))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=1;
			++x;
		}

		if(bit_is_set (PINB,5))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=2;
			++x;
		}

		if(bit_is_set (PINB,6))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=3;
			++x;
		}

		PORTB&=~(1<<PINB0);
		PORTB|=(1<<PINB1);
		_delay_ms(2);

		if(bit_is_set(PINB,4))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(1);
			place++;
			num[x]=4;
			++x;
		}

		if(bit_is_set (PINB,5)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=5;
			++x;
		}

		if(bit_is_set(PINB,6)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=6;
			++x;
		}

		PORTB&=~(1<<PINB1);
		PORTB|=(1<<PINB2);
		_delay_ms(2);

		if(bit_is_set(PINB,4))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=7;
			++x;
		}

		if(bit_is_set (PINB,5))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=8;
			++x;
		}

		if(bit_is_set(PINB,6)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=9;
			++x;
		}

		PORTB&=~(1<<PINB2);
		PORTB|=(1<<PINB3);
		_delay_ms(1);

		if(bit_is_set (PINB,5)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("*");
			_delay_ms(2);
			place++;
			num[x]=0;
			++x;
		}

		PORTB&=~(1<<PINB3);
	}
	while(1);
}


void keypad1(){x=0;
	do{
		if(x==1){
		x=0;place=2;
		break;
		}

		PORTB|=1<<PINB0;
		_delay_ms(1);

		if(bit_is_set(PINB,4))
		{
			
			_delay_ms(2);
	
			++x;
		}

		if(bit_is_set (PINB,5))
		{
			
			_delay_ms(2);
			
			++x;
		}

		if(bit_is_set (PINB,6))
		{
			
			_delay_ms(2);
		
			++x;
		}

		PORTB&=~(1<<PINB0);
		PORTB|=(1<<PINB1);
		_delay_ms(1);

		if(bit_is_set(PINB,4))
		{
			
			_delay_ms(2);
			
			++x;
		}

		if(bit_is_set (PINB,5)){
			
			_delay_ms(2);
			
			++x;
		}

		if(bit_is_set(PINB,6)){
			
			_delay_ms(2);
			
			++x;
		}

		PORTB&=~(1<<PINB1);
		PORTB|=(1<<PINB2);
		_delay_ms(1);

		if(bit_is_set(PINB,4))
		{
			
			_delay_ms(2);
			
			++x;
		}

		if(bit_is_set (PINB,5))
		{
			
			_delay_ms(2);
		
	
			++x;
		}

		if(bit_is_set(PINB,6)){
	
		
			_delay_ms(2);
			
			
			++x;
		}

		PORTB&=~(1<<PINB2);
		PORTB|=(1<<PINB3);
		_delay_ms(1);

		if(bit_is_set (PINB,5)){
			
		
			_delay_ms(2);
			
			
			++x;
		}
		if(bit_is_set (PINB,4)){
			
			
			_delay_ms(2);
			
			
			++x;
		}
		if(bit_is_set (PINB,6)){
			
			
			_delay_ms(2);
			
			
			++x;
		}

		PORTB&=~(1<<PINB3);
	}
	while(1);
}

