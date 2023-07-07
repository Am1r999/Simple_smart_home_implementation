#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define Delay 500 
int system_locked = 1;

// KEYPAD /////////////////////////////
#define KEY_PORT    PORTC
#define KEY_DDR     DDRC
#define KEY_PIN     PINC
#define C1  4
#define C2  5
#define C3  6
int PressKey;
unsigned char KEY_released(void);
unsigned char KEY_pressed(void);
char KEY_finder(void);
void KEY_init(void);
char table [] = {
	'1','2','3',
	'4','5','6',
	'7','8','9',
	'*','0','#'
}; 
///////////////////////////////////////

unsigned char ignore;
int pass_visiable = 1;
char Td;
char Rd;

int main() {
	
	// DDRA = 0x01;


	// SPI initialization //////////////////////////////////////////////////////////////////////////////
    	// SPI Type: Master 			  //////////////////////////////////////////////////////////
    	// SPI Clock Rate: 8MHz / 128 = 62.5 kHz  //////////////////////////////////////////////////////////
    	// SPI Clock Phase: Cycle Half		  //////////////////////////////////////////////////////////
    	// SPI Clock Polarity: Low
    	// SPI Data Order: MSB First
	DDRD = (1<<DDD0);
	DDRB = (1<<DDB7) | (0<<DDB6) | (1<<DDB5) | (1<<DDB4);
    	PORTB = (1<<PORTB4); // Select slave
	SPCR = (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (1<<SPR1) | (1<<SPR0);
	SPSR = (0<<SPI2X);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// ADC initialization 			  //////////////////////////////////////////////////////////
	// Using AVCC and prescaling to 8         //////////////////////////////////////////////////////////
	// ADLAR is default
	ADMUX = (0<<REFS1) | (1<<REFS0);
	ADCSRA = (1<<ADEN) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	DDRD = 0x00; 
	PORTD = 0x04; 
	GICR |= (1 << INT0); 
	MCUCR |= ((1 << ISC01) | (1 << ISC00)); // Rising edge triggered
	sei();
	_delay_ms(5);	


	while (1) {
		if (Rd == 'U') system_locked = 0;
		if (system_locked) {	
			KEY_init();
			Td = KEY_finder();
			if (Td == '*') {
				PORTB &= ~(1<<PORTB4); 		// Select Slave
				SPDR = Td;
				while(((SPSR >> SPIF) & 1) == 0);
				Rd = SPDR;
				PORTB |= (1<<PORTB4); 		// Deselect Slave
								
				//////	

				PORTB &= ~(1<<PORTB4); 		// Select Slave
				SPDR = 'D';
				while(((SPSR >> SPIF) & 1) == 0);
				Rd = SPDR;
				PORTB |= (1<<PORTB4); 		// Deselect Slave
			}
			else {
				PORTB &= ~(1<<PORTB4);
				SPDR = Td;
				while(((SPSR >> SPIF) & 1) == 0);
				Rd = SPDR;
				PORTB |= (1<<PORTB4);
			}
		}
		else if (!system_locked) {
			// PORTA = (1 << PORTA0); 	// Checks if system got unlocked
			//////////////////////////////////////////////////////////////////////////////////
			ADMUX = (0<<MUX0); 		// Single ended input ADC0 (temp)	
			Td = 'T'; 			// Informing slave to be ready for incoming temp	
			PORTB &= ~(1<<PORTB4);
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			PORTB |= (1<<PORTB4);	
			ADCSRA |= ((1 << ADSC) | (1 << ADIF)); 	// Start conversion
			while((ADCSRA & (1 << ADIF)) == 0); 	// Wait till end of the conversion
			Td = ADCL;
			PORTB &= ~(1<<PORTB4);
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			PORTB |= (1<<PORTB4);	
			Td = ADCH;
			PORTB &= ~(1<<PORTB4);
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			PORTB |= (1<<PORTB4);	
			///////////////////////////////////////////////////////////////////////////////////
			ADMUX = (1<<MUX0); 		// Single ended input ADC1 (light)	
			Td = 'L'; 			// Informing slave to be ready for incoming light	
			PORTB &= ~(1<<PORTB4);
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			PORTB |= (1<<PORTB4);	
			ADCSRA |= ((1 << ADSC) | (1 << ADIF)); 	// Start conversion
			while((ADCSRA & (1 << ADIF)) == 0); 	// Wait till end of the conversion
			Td = ADCL;
			PORTB &= ~(1<<PORTB4);
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			PORTB |= (1<<PORTB4);	
			Td = ADCH;
			PORTB &= ~(1<<PORTB4);
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			PORTB |= (1<<PORTB4);	
		}

	}	
}

ISR(INT0_vect){
	pass_visiable = !pass_visiable;
	if (pass_visiable) {
			Td = 'V'; 
			PORTB &= ~(1<<PORTB4); ;
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;	} 
	else {
			Td = 'I'; 
			PORTB &= ~(1<<PORTB4); ;
			SPDR = Td;
			while(((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;	
	};
}




// KEYBAD ////////////////////////////////////////////////////////////////////////
unsigned char KEY_released(void) {  
    KEY_PORT = 0xf0;
    _delay_us(Delay);              
    if((KEY_PIN & 0xf0) == 0xf0)
        return 1;
    else
        return 0;
}

unsigned char KEY_pressed(void) {
    KEY_PORT = 0xf0;
    _delay_us(Delay);
    if( (KEY_PIN & 0xf0) != 0xf0 ) { // User presses some key
        return 1;
    }
    return 0;
}

char KEY_finder(void) {

    unsigned char i, key; 
    if(KEY_pressed()){
	PressKey = 1;
        for(i = 0; i < 4; i++){
            KEY_PORT = ~(1 << i); 
            _delay_us(Delay);
 
            if(((KEY_PIN >> C1) & 1) == 0)     key = table[i*3];
 
            if(((KEY_PIN >> C2) & 1) == 0)     key = table[i*3+1];
 
            if(((KEY_PIN >> C3) & 1) == 0)     key = table[i*3+2];            
        }              
        while(!KEY_released());     
        return key;              
    }
    
    else 
        return 255;
 
}

void KEY_init(void){
    KEY_DDR = 0x0f;
    KEY_PORT = 0xf0;
}

////////////////////////////////////////////////////////////////////////////////

