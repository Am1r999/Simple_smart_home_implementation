#include <avr/io.h>
#include <avr/interrupt.h>
#include <LCD.h>
#include <string.h>
int system_locked = 1;
unsigned char entered_pass[5];
unsigned char password[] = "1234";
unsigned char msg1[] = "p";
unsigned char msg2[] = "g";
unsigned char msg3[] = "d"; 
void msg_write(unsigned char* msg);
void add_char_to_string(unsigned char* str, char c);
int string_length(unsigned char* str); 
int compare_strings(unsigned char* str1, unsigned char* str2); 
char Rd;
int pass_visiable = 1;
int PressKey = 0;
char Rd;
char Td;
int main() {

	DDRC = 0xFF;
	DDRD = 0x07; 	


	// SPI initialization
	// SPI Type: Slave
	// SPI Clock Rate: 8MHz / 128 = 62.5 kHz
   	// SPI Clock Phase: Cycle Half
    	// SPI Clock Polarity: Low
    	// SPI Data Order: MSB First
	DDRB = (0<<DDB4) | (0<<DDB5) | (1<<DDB6) | (0<<DDB7);	

    	SPCR = (1<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (1<<SPR1) | (1<<SPR0);
    	SPSR = (0<<SPI2X);

	init_LCD(); 	// Initialize the LCD library
	LCD_cmd(0x0C); 	// Curser blinking
	msg_write(msg1);
	_delay_ms(250);
	LCD_cmd(0x01);
	Td = 'L';
	while(1) {
		if (system_locked) {
			SPDR = Td;
			while (((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;
			if (Rd == '*') {
				if (compare_strings(entered_pass, password)) {
					LCD_cmd(0x01);         // clear the screen	
					msg_write(msg2);
					system_locked = 0;
					Td = 'U';
				} 
				else {
				    	LCD_cmd(0x01);         // clear the screen	
					msg_write(msg3);
					_delay_ms(50);    	
					LCD_cmd(0x01);         // clear the screen
					msg_write(msg1);
					entered_pass[0] = '\0';
					_delay_ms(250);
					LCD_cmd(0x01);
				}	
			}
			else if (Rd == '#' && string_length(entered_pass) > 0) {
				entered_pass[string_length(entered_pass) - 1] = '\0';
				LCD_cmd(0x01);         // clear the screen
				if (pass_visiable) {
					msg_write(entered_pass);
				}
				else {
					for (int i = 0; i < string_length(entered_pass) - 1; ++i) LCD_write('*'); 
				}
			}
			else if (Rd == 'V') {
				pass_visiable = 1;	
				LCD_cmd(0x01);
				if (string_length(entered_pass) > 0) {
					msg_write(entered_pass);
				}
			}
			else if (Rd == 'I') {
				pass_visiable = 0;
				LCD_cmd(0x01);
				if (string_length(entered_pass) > 0) {
					for (int i = 0; i < string_length(entered_pass); ++i) LCD_write('*'); 
				}
			}
			else if (Rd == '1' || Rd == '2' || Rd == '3' || Rd == '4' || Rd == '5' || Rd == '6' 
			|| Rd == '7' || Rd == '8' || Rd == '9' || Rd == '0')
			{
				add_char_to_string(entered_pass, Rd);
				if (pass_visiable) LCD_write(Rd);
				else if (!pass_visiable) LCD_write('*');
			}
		}
		else {
			SPDR = Td;
			while (((SPSR >> SPIF) & 1) == 0);
			Rd = SPDR;		
		}
	}
}

void msg_write(unsigned char* msg) {
	for (int i = 0; i < string_length(msg); ++i) LCD_write(msg[i]);
}

void add_char_to_string(unsigned char* str, char c) {
    // Find the end of the string
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    // Add the new character to the end of the string
    str[i] = c;
    str[i+1] = '\0';
}

int string_length(unsigned char* str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

int compare_strings(unsigned char* str1, unsigned char* str2) {
    while (*str1 == *str2) {
        if (*str1 == '\0') {
            return 1; // strings are equal
        }
        str1++;
        str2++;
    }
    return 0; // strings are not equal
}
