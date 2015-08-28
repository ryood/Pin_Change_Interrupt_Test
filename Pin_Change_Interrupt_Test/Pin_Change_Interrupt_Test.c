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
	// Timer0���~
	TCCR0B = 0x00;
		
	uint8_t tmp = ~PIND;	// PINx���W�X�^�̒l�͂�������ϐ��ɑ�����Ȃ��Ɣ�r�����܂������Ȃ�
	if (prevSwitch == tmp) {
		sdata ^= prevSwitch;
		PORTB = sdata;
	}
		
	// Pin Change Interrupt�̗L����
	PCICR = (1 << PCIE2);
}

ISR (PCINT2_vect)
{
	// Pin Change Interrupt�𖳌���
	PCICR = 0x00;
	
	// ���荞�݂��Ƃ�LED��_�Łi�f�o�b�O�p�j
	PORTC ^= (1 << PC0);
		
	prevSwitch = ~PIND;
	
	// Timer0���N��
	TCCR0B = 0x05;	// �v���X�P�[���F1024
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
		
	// Pin Change Interrupt�̗L����
	PCICR = (1 << PCIE2);
	PCMSK2 = 0xFF;
	
	// TIMER0 �I�[�o�[�t���[���荞�݂̗L����
	TCCR0B = 0x00;	// Timer0��~
	TIMSK0 = (1 << TOIE0);
	
	sei();
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}