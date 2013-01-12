
#define UART_BAUD 300
//#define BAUD_PRESCALE 416	//for 1200 at 8000000
//#define BAUD_PRESCALE 832	//for 600 at 8000000
#define BAUD_PRESCALE 1666	//for 300 at 8000000

#include <avr/io.h>
#include <util/delay.h>
//#include <uart.h>
//#include <avr/interrupt.h>
//#include <a2d.h>
#include <sensor.h>

#define kp 20
#define kd 8

char X[2]={0,0};
char S[2]={0,0};
char G[2]={0,0};
char absdir;
char mission_accomplished=0;


void RFComm(void);
char DStar(void);

int main(void)
{
	//LineFollowerCode
  int i;
  char l=255;
  char r=255;  
  int j=0;
  int k=0;
  int t=0;
  int p=0;
  DDRD=0xFF;
  DDRC=0xFF;
  PORTC=0xFF;
  
  
  PORTC=0x00;
  _delay_ms(100);
  PORTC=0xFF;
  /*_delay_ms(1000);
  PORTC=0x00;
  _delay_ms(1000);
  PORTC=0xFF;
  _delay_ms(1000);
  */
  PORTD=0x35;
  
  TCCR1A=0xA1;
  TCCR1B=0x01;
  TCNT1H=0x00;
  TCNT1L=0xFF;
  OCR1AH=0x00; 
  OCR1AL=0x00;
  OCR1BH=0x00; 
  OCR1BL=0x00;
  
  if(mission_accomplished==0)
  {
	while(1)
	{
		if(t<=0)
		{	
			p=t;
			i=sense();
			PORTC=i;
			
			k=j;
		
			if(i==0b00000100)		//straight
			{	
				t=0;
				j=0;
				PORTD=0x35;
			}
			if(i==0b000000110)		//soft left
			{	
				t=0;
				j=1;
				PORTD=0x35;
			}
			if(i==0b00000010)		//soft left
			{	
				t=0;
				j=1;					
				PORTD=0x35;
			}	
			if(i==0b00000001)		//hard left
			{	
				t=0;
				j=3;
				PORTD=0x35;
			}
			if(i==0b00001100)		//soft right
			{	
				t=0;
				j=-1;
				PORTD=0x35;
			}	
			if(i==0b00001000)		//soft right
			{	
				t=0;
				j=-1;
				PORTD=0x35;
			}	
			if(i==0b00010000)		//hard right
			{	
				t=0;
				j=-3;
				PORTD=0x35;
			}
			
			k=j-k;			// D control
		
			if(j<=0)
			{
				r=210+(kp*j)+(kd*k); //decrease right speed
				l=210-(kp*j)+(kd*k); // increase left speed	
			}
			else if(j>0)
			{
				r=210+(kp*j)+(kd*k);	//increase right speed
				l=210-(kp*j)+(kd*k);	//decrease left speed
			}	
			if(i==0b00001111) // hard left
			{	
				t=0;
				l=255;
				r=255;
				PORTD=0x33;
			}	
			if(i==0b00000111)	// hard left
			{	
				t=0;
				l=255;
				r=255;
				PORTD=0x33;
			}	
			if(i==0b00000011)	// hard left	
			{	
				t=0;
				l=255;
				r=255;
				PORTD=0x33;
			}
			if(i==0b00011110) // hard right
			{	
				t=0;
				l=255;
				r=255;
				PORTD=0x3C;
			}
			if(i==0b00011000)	// hard right
			{	
				t=0;
				l=255;
				r=255;
				PORTD=0x3C;
			}
			if(i==0b00011100)	//hard right
			{	
				t=0;
				l=255;
				r=255;
				PORTD=0x3C;
			}	
			if(i==0b00011111)	// Intersection
			{	
				l=255;
				r=255;
				PORTD=0x35;
				t=1;
			}
			if(i==0x00)
			{		
				t=0;
				if(j<0)			//hard right
				{
					l=255;
					r=255;
					PORTD=0x3C;		
				}
				else if(j>0)	//hard left
				{
					l=255;
					r=255;
					PORTD=0x33;
				}
			}
		}
		else
		{
			RFComm();
			DStar();
		}
		
		OCR1AH=0x00; 
		OCR1AL=r;
		OCR1BH=0x00; 
		OCR1BL=l;
		
		DDRD=0xFF;
		
		_delay_ms(1);
		t=t-p;
	}
  }
  else
  RFComm();								////////////////return the next goal position///////////////////////
}

void RFComm()
{
	return;
}
char DStar()
{
	return(1);
}