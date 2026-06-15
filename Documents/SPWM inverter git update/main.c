/*
 * SPWM inverter.c
 *
 * Created: 1/11/2026 2:56:29 PM
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#define TOP 499
#define half_cycle 160

volatile uint8_t dead_time =0;
volatile uint16_t index = 0 ;
volatile uint8_t  half = 0 ;

 
const uint16_t sine_values[half_cycle] ={ 0 , 10 , 20 , 29 , 39 , 49 , 59 , 68 , 78 , 88 , 97 , 107  , 116  , 126 , 135 , 145 ,
	154 , 163 , 173 , 182 , 191 , 200 , 209 , 218 , 227 , 235 , 244 , 252 , 261 , 269 , 277 , 285 ,
	293 , 301 , 309 , 317 , 324 , 331 , 339 , 346 , 353 , 360 , 366 , 373 , 379 , 386 , 392 , 398 ,
	404 , 409 , 415 , 420 , 425 , 431 , 435 , 440 , 445 , 449 , 453 , 457 , 461 , 465 , 468 , 471 ,
	475 , 478 , 480 , 483 , 485 , 487 , 489 , 491 , 493 , 494 , 496 , 497 , 497 , 498 , 499 , 499 ,
	499 , 499 , 499 , 498 , 497 , 497 , 496 , 494 , 493 , 491 , 489 , 487 , 485 , 483 , 480 , 478 ,
	475 , 471 , 468 , 465 , 461 , 457 , 453 , 449 , 445 , 440 , 435 , 431 , 425 , 420 , 415 , 409 ,
	404 , 398 , 392 , 386 , 379 , 373 , 366 , 360 , 353 , 346 , 339 , 331 , 324 , 317 , 309 , 301 ,
	293 , 285 , 277 , 269 , 261 , 252 , 244 , 235 , 227 , 218 , 209 , 200 , 191 , 182 , 173 , 163 ,
154 , 145 , 135 , 126 , 116 , 107 , 97 , 88 , 78 , 68 , 59 , 49 , 39 , 29 , 20 ,10 ,0 };

			
			
	

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
	if(dead_time){
	OCR1A =0;
	OCR1B =0;
	dead_time--;
	return ;
		
	}
	
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
		OCR1A = 0;
		OCR1B = 0;
		half^=1 ;
		dead_time = 1;
	}
	
	
	
}
