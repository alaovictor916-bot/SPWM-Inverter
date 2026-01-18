/*
 * SPWM inverter.c
 *
 * Created: 1/11/2026 2:56:29 PM
 * Author : USER
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#define TOP 499
#define half_cycle 160

volatile uint16_t index = 0 ;
volatile uint8_t  half = 0 ;

 
const uint16_t sine_values[half_cycle] ={ 255,	260,	265,	270,	274,	279,	284,	289, 294,	299,	303,	308,	     
	    313,	318,	322,	327,	332,	336,	341,   	
	    345,	350,	354,	359,	363,	367,	372,  	
	    376,	380,	384,	388,	392,	396,	400,	
	    404,	408,	412,	415,	419,	423,	426,    
		429,	433,	436,	439,	442,	445,	449,     	
		451,	454,	457,	460,	462,	465,	467,    	
		470,	472,	474,	476,	478,	480	,   482	,
		484,	485,	487,	488,	490,	491,	492,     	
		493,	494,	495,	496,	497,	497,	498 ,     	
		498,	499,	499,	499,	499,	499,	499,	
		499,    498,	498,	497,	497,	496,	495,	
		494,    493,	492,	491,	490,	488,	487,	
		485,    484,	482,	480,	478,	476,	474,	
		472,    470 ,	467,	465,	462,	460 ,	457 ,
		454  ,  451,	449,	446,	442,	439,	436,
		433,    429,	426,	423,	419,	415,	412,
		408,	404,	400,	396,    392,	388,	384,
		380,	376,	372,	367,	363,	359,	354,
		350,	345,	341,	336,	332,	327,	322,
		318,	313,	308,	303,	299,	294,	289,	
		284,	279,	274,	270,	265,	260,	255,
			250	};
			
			
	

int main(void)
{
    DDRB |= (1 << PB1); //defining OC1A as an output pin
    DDRB |= (1 << PB2); // defining OC1B as an output pin
    
    // Clearing timer1 registers
    TCCR1A = 0;
    TCCR1B = 0 ;
    
    
    // setting to mode 14  fast pwm 1110
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << WGM13) ;
    
    TCCR1A |=(1<< COM1A1);
    TCCR1A |=(1 << COM1B1);
    
    
    ICR1 = TOP ;
    
    TCCR1B |= (1 << CS10) ;
    
    TIMSK1 |= (1 << TOIE1);
    sei();
    while (1) 
    {
		
		
		
		
		
		
		
    }
}

ISR(TIMER1_OVF_vect){
	if (half==0){
		
		OCR1A =sine_values[index];
		OCR1B =0;
		
	}
	else{
		OCR1A =0;
		OCR1B = sine_values[index];
		
	}
	index++;
	if(index >= half_cycle){
		index =0;
		half^=1 ;
	}
	
	
	
}
