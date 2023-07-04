/*/1* */
/*   4x4 Keypad Interfacing with ATmega16/32 */
/*   http://www.electronicwings.com */
/* *1/ */ 
 
/*#include "LCD16x2_4bit.h" */
/*#include <avr/io.h> */
/*#include <util/delay.h> */


/*#define KEY_PRT 	PORTA */
/*#define KEY_DDR		DDRA */
/*#define KEY_PIN		PINA */

/*unsigned char keypad[4][4] = {	{'7','8','9','/'}, */
/*				{'4','5','6','*'}, */
/*				{'1','2','3','-'}, */
/*				{' ','0','=','+'}}; */

/*unsigned char colloc, rowloc; */

/*char keyfind() */
/*{ */
/*	while(1) */
/*	{ */
/*	    KEY_DDR = 0xF0;           	/1* set port direction as input-output *1/ */
/*	    KEY_PRT = 0xFF; */

/*	    do */
/*	    { */
/*		KEY_PRT &= 0x0F;      		/1* mask PORT for column read only *1/ */
/*		asm("NOP"); */
/*		colloc = (KEY_PIN & 0x0F); 	/1* read status of column *1/ */
/*	    }while(colloc != 0x0F); */
		
/*	    do */
/*	    { */
/*		do */
/*		{ */
/*	            _delay_ms(20);             /1* 20ms key debounce time *1/ */
/*		    colloc = (KEY_PIN & 0x0F); /1* read status of column *1/ */
/*		}while(colloc == 0x0F);        /1* check for any key press *1/ */
			
/*		_delay_ms (40);	            /1* 20 ms key debounce time *1/ */
/*		colloc = (KEY_PIN & 0x0F); */
/*	    }while(colloc == 0x0F); */

/*	   /1* now check for rows *1/ */
/*	    KEY_PRT = 0xEF;            /1* check for pressed key in 1st row *1/ */
/*	    asm("NOP"); */
/*	    colloc = (KEY_PIN & 0x0F); */
/*	    if(colloc != 0x0F) */
/*            { */
/*		rowloc = 0; */
/*		break; */
/*	    } */

/*	    KEY_PRT = 0xDF;		/1* check for pressed key in 2nd row *1/ */
/*	    asm("NOP"); */
/*	    colloc = (KEY_PIN & 0x0F); */
/*	    if(colloc != 0x0F) */
/*	    { */
/*		rowloc = 1; */
/*		break; */
/*	    } */
		
/*	    KEY_PRT = 0xBF;		/1* check for pressed key in 3rd row *1/ */
/*	    asm("NOP"); */
/*            colloc = (KEY_PIN & 0x0F); */
/*	    if(colloc != 0x0F) */
/*	    { */
/*		rowloc = 2; */
/*		break; */
/*	    } */

/*	    KEY_PRT = 0x7F;		/1* check for pressed key in 4th row *1/ */
/*	    asm("NOP"); */
/*	    colloc = (KEY_PIN & 0x0F); */
/*	    if(colloc != 0x0F) */
/*	    { */
/*		rowloc = 3; */
/*		break; */
/*	    } */
/*	} */

/*	if(colloc == 0x0E) */
/*	   printf("%c\n",(keypad[rowloc][0]); */
/*	else if(colloc == 0x0D) */
/*	   printf("%c\n",(keypad[rowloc][1]); */
/*	else if(colloc == 0x0B) */
/*	   printf("%c\n",(keypad[rowloc][2]); */
/*	else */
/*	   printf("%c\n",(keypad[rowloc][3]); */
/*} */

/*int main(void) */
/*{ */
/*	LCD_Init(); */
/*	LCD_String_xy(1,0,"Press a key"); */
/*    while(1) */
/*	{ */
/*	    LCD_Command(0xc0); */
/*	    LCD_Char(keyfind());       /1* Display which key is pressed *1/ */
/*	} */
/*} */

/* unsigned char keypad[4][3] = { */
/* 	{'1', '2', '3'}, */
/* 	{'4', '5', '6'}, */
/* 	{'7', '8', '9'}, */
/* 	{'*', '0', '#'} */ 
/* }; */
/* unsigned char row, column; */
/* #include <stdio.h> */
/* #include <string.h> */
/* void print(unsigned char msg[]){ for (int i = 0; i < strlen(msg); ++i) printf("%c", msg[i]);} */
/* int main() { */
	/* unsigned char PINA = 0b1000100; */
	/* column = (PINA & 0x07); */
	/* row = ( PINA >> 3 ); */
	/* int j; */
	/* if (column & 1) { */
	/* 	j = 0; */	
	/* 	if (row & 1) printf("%c\n", keypad[0][j]); */
	/* 	else if ((row >> 1) & 1) printf("%c\n", keypad[1][j]); */
	/* 	else if ((row >> 2) & 1) printf("%c\n", keypad[2][j]); */
	/* 	else if ((row >> 3) & 1) printf("%c\n", keypad[3][j]); */
	/* } */
	/* else if ((column >> 1) & 1) { */
	/* 	j = 1; */
	/* 	if (row & 1) printf("%c\n", keypad[0][j]); */
	/* 	else if ((row >> 1) & 1) printf("%c\n", keypad[1][j]); */
	/* 	else if ((row >> 2) & 1) printf("%c\n", keypad[2][j]); */
	/* 	else if ((row >> 3) & 1) printf("%c\n", keypad[3][j]); */
	/* } */	
	/* else if ((column >> 2) & 1) { */
	/* 	j = 2; */
	/* 	if (row & 1) printf("%c\n", keypad[0][j]); */
	/* 	else if ((row >> 1) & 1) printf("%c\n", keypad[1][j]); */
	/* 	else if ((row >> 2) & 1) printf("%c\n", keypad[2][j]); */
	/* 	else if ((row >> 3) & 1) printf("%c\n", keypad[3][j]); */
	/* } */	
	/* int a = 0; */
	/* if (1 == 1) a = 12; else a = 13; */
	/* printf("%d", a); */
	/* if ( 1 == 1) for (int i = 0; i < 4; ++i) printf(" %d ", i); */ 	
	/* return 0; */
	/* unsigned char msg[] = "This shit is a test! But fucking hell, Right?"; */
	/* unsigned char msg1[] = "This shit is a test! But fucking hell, Right?"; */
	
	/* if (strcmp(msg1, msg) == 0) printf("Yes"); else printf("NO"); */

	/* printf("%d\n", strlen(msg)); */
	/* msg[strlen(msg) - 1] = '\0'; */	
	/* 	msg[strlen(msg) - 1] = '\0'; */	
	/* printf("%d\n", strlen(msg)); */
	/* print(msg); */
	/* unsigned char a[] = "x"; */
	/* unsigned char b[] = "y"; */ 
	/* printf("\n%s\n", strcat(a, b)); */
/* } */


/* #define KEY_PIN */
/* #define KEY_PORT */ 
/* #define KEY_DDR */

/* unsigned char released(void) { */  
    /* key_port = 0xf0; */
    /* _delay_us(delay); */              
    /* if((key_pin & 0xf0) == 0xf0) */
        /* return 1; */
    /* else */
        /* return 0; */
/* } */

/* unsigned char pressed(void) { */
    /* key_port = 0xf0; */
    /* _delay_us(delay); */
    /* if( (key_pin & 0xf0) != 0xf0 ) { // user presses some key */
        /* return 1; */
    /* } */
    /* return 0; */
/* } */

/* char key_finder(void) { */

	/* char table [] = {'1','2','3', */
	/* 				 '4','5','6', */
	/* 				 '7','8','9', */
	/* 				 '*','0','#',}; */ 
    /* unsigned char i, key; */ 
    /* if(key_pressed()){ */
	/* 	presskey = true; */
        /* for(i = 0; i < 4; i++){ */
            /* key_port = ~(1 << i); */ 
            /* _delay_us(delay); */
 
            /* if(((key_pin >> c1) & 1) == 0)     key = table[i*3]; */
 
            /* if(((key_pin >> c2) & 1) == 0)     key = table[i*3+1]; */
 
            /* if(((key_pin >> c3) & 1) == 0)     key = table[i*3+2]; */            
        /* } */              
        /* while(!key_released()); */     
        /* return key; */              
    /* } */
    
    /* else */ 
        /* return 255; */
 
/* } */

/* void key_init(void){ */
    /* KEY_DDR = 0x0f; */
    /* KEY_PORT = 0xf0; */
/* } */


#include <stdio.h>
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
int main() {
unsigned char my_string[100] = "hello";
char new_char = '!';
add_char_to_string(my_string, new_char);
printf("%s", my_string); // Output: "hello!"	
}
