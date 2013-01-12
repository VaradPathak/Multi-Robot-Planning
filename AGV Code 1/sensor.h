// Created on 19th February 2008 in Aurangabad, India

// This header file is intellectual property of Aditya Ambadkar and 
// Ajay Kalyankar. As we belive in open source ethics you are free to 
// modify and distribute this file.

// 	INclude this header file, just call 'sense' function and it returns 
//	sensor information. This is developed for 5 sensors, you may extend 
//	it to as many channels as you want


void start_conv(void);
void init_adc(void);
int sense(void);


void start_conv()
{
	ADCSRA|=(1<<ADSC);
	while(ADCSRA&(1<<ADSC));
}

void init_adc()
{
	DDRA=0x00;
	DDRC=0xff;
	ADMUX=(1<<REFS0)|(0x3);
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
}

int sense()
{
    int i=0;
	int s=0;
	
	init_adc();
	
	ADMUX=(1<<REFS0)|(0x0);
   	start_conv();
	i=ADC;	
	
	if(i>150)
		s |= 0b00000001;
	
	ADMUX=(1<<REFS0)|(0x01);
   	start_conv();
	i=ADC;
	if(i>150)
		s |= 0b00000010;
		
	ADMUX=(1<<REFS0)|(0x02);
   	start_conv();
	i=ADC;
	if(i>150)
		s |= 0b00000100;
		
	ADMUX=(1<<REFS0)|(0x03);
   	start_conv();
	i=ADC;
	if(i>150)
		s |= 0b00001000;
		
	ADMUX=(1<<REFS0)|(0x04);
   	start_conv();
	i=ADC;
	if(i>150)
		s |= 0b00010000;
	
	if(i>150)  
		s|=0x1;
	
	//s |= 0xE0;
	return s;
}
