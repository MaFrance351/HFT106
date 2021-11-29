#include <REG52.H>                /* special function register declarations   */
                                  /* for the intended 8051 derivative         */
#include <stdio.h>                /* prototype declarations for I/O functions */

#ifdef MONITOR51                         /* Debugging with Monitor-51 needs   */
char code reserve [3] _at_ 0x23;         /* space for serial interrupt if     */
#endif                                   /* Stop Exection with Serial Intr.   */
                                         /* is enabled                        */

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/
void delay(void) {
unsigned long n;
	for(n = 0; n < 100; n++);;
}
char s[16];
char symbols[4][4] = {{'E', '0', 'R', 'C'},
											{'9', '8', '7', 'B'},
											{'6', '5', '4', 'A'},
											{'3', '2', '1', 'Z'}};
char symbolsP0[4] =   {'L', 'K', 'J', 'I'};
void lcdSend(int isCommand, unsigned char toLCD) {
	P3 &= ~(1 << 7);
    if(isCommand == 0) P3 |= (1 << 6);
	else if(isCommand == 1) P3 &= ~(1 << 6);
    delay();
	P2 = toLCD;
	P3 |= (1 << 5);
	delay();
	P3 &= ~(1 << 5);
	delay();
}
void lcdCommand(unsigned char cmd) {
    lcdSend(1, cmd);
}

void lcdChar(const char chr) {
    lcdSend(0, chr);
}

void lcdString(const char* str) {
   while(*str != '\0') { //*str != '\0'
        lcdChar(*str);
        str++;
    }
}
void main (void) {
int n1, i, j, k;  
  TMOD |= 0x10;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    //TH0   = 0xFF;                /* TH1:  reload value for 1200 baud @ 16MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
  //  TI    = 1;                  /* TI:   set TI to send first char of UART    */

   lcdCommand(0x38);
   lcdCommand(0x01);
   lcdCommand(0x06);
   lcdCommand(0x0C);
	/*
	while(1) {
   lcdCommand(0x80); 
	P1 = 0x0F;
n1 = P1;
//	s = "";
	sprintf(s, "%X", n1);
	lcdString(s);
	for(i = 0; i > 1000; i++) {
	delay();
	}
}
	*/
	while(1) {
	P1 = 0x0F;
		P0 |= (1 << 7);
	for(i = 4; i < 8; i++) {
		for(j = 4; j < 8; j++) P1 |= (1 << j);
		P1 &= ~(1 << i);
		for(k = 0; k < 4; k++) {
			if(((P1 >> k) & 1) == 0 ) {
				P3 &= ~(1 << 4);
				n1 = P1;
			sprintf(s, "%X", n1);
				lcdCommand(0x80); 
				lcdString("Scanc0de: ");
	lcdString(s);
				lcdCommand(0xC0);
				lcdString("Key: ");
				lcdChar(symbols[i-4][k]);
				for(j = 0; j < 30; j++)	delay();
			}
			else {
				P3 |= (1 << 4);
			}
		}
	}
	P0 &= ~(1 << 7);
		for(i = 0; i < 4; i++) {
			if(((P1 >> i) & 1) == 0 ) {
				P3 &= ~(1 << 4);
				n1 = P1;
			sprintf(s, "%X", n1);
				lcdCommand(0x80); 
				lcdString("Scanc0de: ");
	lcdString(s);
				lcdCommand(0xC0);
				lcdString("Key: ");
				lcdChar(symbolsP0[i]);
				for(j = 0; j < 30; j++)	delay();
			}
			else {
				P3 |= (1 << 4);
			}
	}
}
   //lcdString("NEDOPC.ORG");
	/*
	TH1 = 0;
	while(1) {
	if(TH1 > 254) {
		P3 &= ~(1 << 4);
		delay();
		TH1 = 0;
		P3 |= (1 << 4);
	}
	}
	*/
}


