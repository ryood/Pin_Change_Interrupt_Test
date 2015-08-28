/*
 * Pin_Change_Interrupt_Test.c
 *
 * Created: 2015/08/28 17:23:44
 *  Author: gizmo
 *
 * PORTD: SWx8
 * PORTB: LEDx8
 * PORTC: PC0: LED
 *
 */ 

#define F_CPU	8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

ISR (PCINT2_vect)
{
	// äÑÇËçûÇ›Ç≤Ç∆Ç…LEDÇì_ñ≈
	PORTC ^= (1 << PC0);
	
	PORTB = ~PIND;
}

int main(void)
{
	// PORTD input/pullup
	DDRD = 0x00;
	PORTD = 0xFF;
	
	// PORTB output
	DDRB = 0xFF;
	
	// PORTC: PC0 ouput
	DDRC = (1 << PC0);
	
	// LED Check	
	PORTB = 0xFF;
	PORTC = (1 << PC0);
	for (int i = 0; i < 8; i++) {
		PORTB &= ~(1 << i);
		_delay_ms(200);
	}
	PORTC = 0x00;
		
	// Pin Change InterruptÇÃóLå¯âª
	PCICR = (1 << PCIE2);
	PCMSK2 = 0xFF;
	
	sei();
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}