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

volatile uint8_t prevSwitch = 0x00;
volatile uint8_t sdata = 0x00;

ISR (TIMER0_OVF_vect)
{
	// Timer0を停止
	TCCR0B = 0x00;
		
	uint8_t tmp = ~PIND;	// PINxレジスタの値はいったん変数に代入しないと比較がうまくいかない
	if (prevSwitch == tmp) {
		sdata ^= prevSwitch;
		PORTB = sdata;
	}
		
	// Pin Change Interruptの有効化
	PCICR = (1 << PCIE2);
}

ISR (PCINT2_vect)
{
	// Pin Change Interruptを無効化
	PCICR = 0x00;
	
	// 割り込みごとにLEDを点滅（デバッグ用）
	PORTC ^= (1 << PC0);
		
	prevSwitch = ~PIND;
	
	// Timer0を起動
	TCCR0B = 0x05;	// プリスケーラ：1024
	TCNT0 = 8;		// about: 1ms	
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
		_delay_ms(100);
	}
	PORTC = 0x00;
		
	// Pin Change Interruptの有効化
	PCICR = (1 << PCIE2);
	PCMSK2 = 0xFF;
	
	// TIMER0 オーバーフロー割り込みの有効化
	TCCR0B = 0x00;	// Timer0停止
	TIMSK0 = (1 << TOIE0);
	
	sei();
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}