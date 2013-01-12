

//#define BAUD_PRESCALE 416	//for 1200 at 8000000
//#define BAUD_PRESCALE 832	//for 600 at 8000000
//#define BAUD_PRESCALE 1666	//for 300 at 8000000
int BAUD_PRESCALE=3332;// 300 baud at 16MHz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <sensor.h>

//defines start
#define NUL 0x7E
#define SOH 0x01
#define SOD 0x02

//defines end
#define EM 0xFE
#define ET 0xFF

//defines CRC
#define PRESET 0Xff
#define POLY 0x1D

// defines acknowldgement
#define ACK 0x50

// defines pid constants
#define kp 20
#define kd 8

//define directions
#define FW 0xB8
#define SL 0xB0
#define SR 0x38
#define HL 0xB4
#define HR 0x78
#define BW 0x74
#define STOP 0xB0

//defines addresses
#define LC1 0x01
#define LC2 0x02
#define SC 0x03
#define A1 0x04
#define A2 0x05
#define A3 0x06

//define next directions
#define NBW 0x00
#define NHR 0x01
#define NHL 0x02
#define NFW 0x03
#define NSTOP 0x04

///////////// variables //////////////////

volatile char ReceivedByte[6]={0};
unsigned char crc_reg;
volatile int j=0,k=0,l=0;

/////////////// function definations /////////////////

void crc8(unsigned char, unsigned char*);
void RFComm(void);
void turnl(void);
void turnr(void);
void init(void);



int main(void)
{
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
  _delay_ms(100);
  PORTD=FW;
  init();
  TCCR1A=0xA1;
  TCCR1B=0x01;
  TCNT1H=0x00;
  TCNT1L=0xFF;
  OCR1AH=0x00; 
  OCR1AL=0x00;
  OCR1BH=0x00; 
  OCR1BL=0x00;
  
  
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
				PORTD=FW;
			}
			if(i==0b000000110)		//soft left
			{	
				t=0;
				j=1;
				PORTD=FW;
			}
			if(i==0b00000010)		//soft left
			{	
				t=0;
				j=1;					
				PORTD=FW;
			}	
			if(i==0b00000001)		//hard left
			{	
				t=0;
				j=3;
				PORTD=FW;
			}
			if(i==0b00001100)		//soft right
			{	
				t=0;
				j=-1;
				PORTD=FW;
			}	
			if(i==0b00001000)		//soft right
			{	
				t=0;
				j=-1;
				PORTD=FW;
			}	
			if(i==0b00010000)		//hard right
			{	
				t=0;
				j=-3;
				PORTD=FW;
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
			
			if(i==0b00011111)	// Intersection
			{	
				l=255;
				r=255;
				PORTD=FW;
				t=1;
			}
			
		}
		else
		{
			PORTD=STOP;		////stop///
			RFComm();
			t=0;
			
		}
		
		OCR1AH=0x00; 
		OCR1AL=r;
		OCR1BH=0x00; 
		OCR1BL=l;
		_delay_ms(1);
		t=t-p;
	}
  
  
}

void RFComm()
{
	while(1)
	{
	if(j==1)
	{
		cli();
		crc_reg=PRESET;
		
		for(k=0;k<5;k++)
		{
			crc8(ReceivedByte[k],&crc_reg);
		}
		
	
		if(crc_reg==ReceivedByte[5])
		{
			
			PORTC=0x00;
			_delay_ms(500);
			PORTC=0xff;
			if (ReceivedByte[2]==A1)
			{
				if (ReceivedByte[3]==NBW)
				{
					turnl();
					turnl();
				}	
				if (ReceivedByte[3]==NHR)
				{
					turnr();
				}
				if (ReceivedByte[3]==NHL)
				{
					turnl();
				}
			    if (ReceivedByte[3]==NFW)
				{
					return;
				} 
				if (ReceivedByte[3]==NSTOP)
				{
					PORTD=STOP;
				}
			}
			
		
		}
	
		else
		{
			
			PORTC=0x0f;
			_delay_ms(500);
			PORTC=0xff;
		}
		
		j=0;
		
		for(l=0;l<6;l++)
		{
			ReceivedByte[l]=0;
		}
		sei();
		
	}	
	
  }
	
	
}


void turnl()
{
	int i;
	PORTD=0x33;
	_delay_ms(500);
	i=sense();
	while(1)
	{
		if(i==0b00001110)
			return;
	}
	
}

void turnr()
{
	
	int i;
	PORTD=0x3c;
	_delay_ms(500);
	i=sense();
	while(1)
	{
		if(i==0b00001110)
			return;
	}
}


ISR(BADISR_vect)
{
	char a=0;
	a=a;

}

ISR(USART_RXC_vect)
{
	static int i;
	
	ReceivedByte[i] = UDR; // Fetch the recieved byte value into the variable "ByteReceived"
 	
	if(ReceivedByte[0]==NUL)
	{
		i++;
		if(i>5)
		{	
		
			j=1;
			i=0;
			
		}
	}
	
	
}

void init()
{ 
	
	
	UBRRH = (unsigned char)(BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRRL = (unsigned char)BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
   
	UCSRB |= (1 << RXEN) ;//| (1 << TXEN);   // Turn on the transmission and reception circuitry
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes
	UCSRB |= (1 << RXCIE); // Enable the USART Recieve Complete interrupt (USART_RXC) 
		
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed


}
 

void crc8(unsigned char in, unsigned char *crc )
{
	int l;

	*crc= *crc ^ in;

	for(l=0;l<8;l++)
	{
		*crc = (*crc & 0x80) ? (*crc << 1) ^ POLY : (*crc << 1); 
	}

	return;
}


