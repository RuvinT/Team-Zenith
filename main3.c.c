#ifndef F_CPU
#define F_CPU 10000000UL // 10 MHz clock speed
#endif


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


#include <avr/io.h>







int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xF0;
	DDRA=0x0F;//first four output other input
	
	Lcd4_Init();
	Lcd4_Set_Cursor(1,1);
	
	
	Lcd4_Write_String("Box 2 is empty  ");
	
	while(1){
		
		// if(bit_is_set(PINA,6))flag=1;
		//  if(bit_is_set(PINA,7))flag=2;
		
		
		
		if(bit_is_set(PINA,7)){
			
			if(!(bit_is_set (PINC,0))){
				PORTA|=(1<<PINA1);
				PORTD|=(1<<PIND0);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("Coin you entered");
				Lcd4_Set_Cursor(2,3);
				Lcd4_Write_String("RS 5");
				_delay_ms(100);
				Lcd4_Clear();
				for(int i=25;i>0;--i){
					if(bit_is_set(PINA,5)){Lcd4_Clear();
						Lcd4_Set_Cursor(1,1);
						
						
						Lcd4_Write_String("Box 2 is empty  ");
						
						
						PORTD&=~(1<<PIND0);
						PORTA&=~(1<<PINA1);
						break;
					}
					Lcd4_Clear();
					char str2[2];
					sprintf(str2, "%d", i);
					
					
					Lcd4_Set_Cursor(1,1);
					
					
					Lcd4_Write_String("Time rem in B2");
					
					
					Lcd4_Set_Cursor(2,2);
					
					Lcd4_Write_String(str2);
					
					Lcd4_Set_Cursor(2,5);
					
					Lcd4_Write_String(":");
					for(int j=59;j>0;j--){
						_delay_ms(10);
						char str1[2];
						sprintf(str1, "%d", j);
						
						Lcd4_Set_Cursor(2,7);
						Lcd4_Write_String(str1);
						if(j<10)
						{Lcd4_Set_Cursor(2,8);
							Lcd4_Write_String(" ");
						}
						
						if(bit_is_set(PINA,5)){
							Lcd4_Clear();
							Lcd4_Set_Cursor(1,1);
							
							
							Lcd4_Write_String("Box 2 is empty");
							PORTD&=~(1<<PIND0);
							
							PORTA&=~(1<<PINA1);
							break;
						}
						
						
						
					}
					
				}
				
				} else if(!(bit_is_set (PINC,1))){
				PORTA|=(1<<PINA1);
				PORTD|=(1<<PIND0);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("Coin you entered");
				Lcd4_Set_Cursor(2,3);
				Lcd4_Write_String("RS 10");
				_delay_ms(100);
				Lcd4_Clear();
				for(int i=60;i>0;--i){
					if(bit_is_set(PINA,5)){Lcd4_Clear();
						Lcd4_Set_Cursor(1,1);
						
						
						Lcd4_Write_String("Box 2 is empty  ");
						
						
						PORTD&=~(1<<PIND0);
						
						PORTA&=~(1<<PINA1);
						break;
					}
					Lcd4_Clear();
					char str2[2];
					sprintf(str2, "%d", i);
					
					
					Lcd4_Set_Cursor(1,1);
					
					
					Lcd4_Write_String("Time rem in B2");
					
					
					Lcd4_Set_Cursor(2,2);
					
					Lcd4_Write_String(str2);
					
					Lcd4_Set_Cursor(2,5);
					
					Lcd4_Write_String(":");
					for(int j=59;j>0;j--){
						_delay_ms(10);
						char str1[2];
						sprintf(str1, "%d", j);
						
						Lcd4_Set_Cursor(2,7);
						Lcd4_Write_String(str1);
						if(j<10)
						{Lcd4_Set_Cursor(2,8);
							Lcd4_Write_String(" ");
						}
						
						if(bit_is_set(PINA,5)){Lcd4_Clear();
							Lcd4_Set_Cursor(1,1);
							
							
							Lcd4_Write_String("Box 2 is empty");
							PORTD&=~(1<<PIND0);
							
							PORTA&=~(1<<PINA1);
							break;
						}
						
						
						
					}
					
				}
				PORTD&=~(1<<PIND0);
				PORTA&=~(1<<PINA1);
				
			}
			
			
			
			
			
		}
	}
	
	
	
}


