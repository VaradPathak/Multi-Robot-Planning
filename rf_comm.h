 #include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<dos.h>

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

//defines addresses
#define LC1 0x01
#define LC2 0x02
#define SC 0x03
#define A1 0x04
#define A2 0x05
#define A3 0x06

//define directions
#define BW 0x00
#define HR 0x01
#define HL 0x02
#define FW 0x03
#define STOP 0x04

//define crane instructions
#define REQ 0x00
#define REQ_FF 0x01
#define NO_REQ 0x02
#define AGV_LOADED 0x03
#define AGV_UNLOADED 0x04

void portinit(void);
void write(char);
void read(void);

// defines acknowldgement
#define ACK 0x06

void crc8(unsigned char, unsigned char*);
void RFcomm(char , char);
void crane_comm(char,char);  
char szBuff[6] = {0};
HANDLE hSerial;
DCB dcbSerialParams = {0};
DWORD dwBytesRead = 0;


void RFcomm(char add, char dir)
{
	unsigned char crc_reg,i=0,j=0,k=0;
	unsigned char bit[5]={NUL,SOD,add,dir,ET};
//	unsigned char ack[5]={NUL,SOD,ACK,ACK,ET};	// CRC is 1a
	
	portinit();
	crc_reg=PRESET;
	for(i=0;i<5 ;i++)	// for 5 bytes
	{
		crc8(bit[i],&crc_reg);
		printf("bit-- %x  CRC-- %x \n",bit[i], crc_reg);
	}
	
	for(j=0;j<5;j++)
	{
		for(i=0;i<5;i++)
		{
			write(bit[i]); 
		}
		write(crc_reg);
	}	
	
	printf("END of AGV comm \n");
	CloseHandle(hSerial); 
	return;
	
}
void crane_comm(char add,char data)
{
	unsigned char bit[5]={NUL,SOD,add,data,ET};
	unsigned char crc_reg,i=0,j=0,k=0;
	portinit();
	for(i=0;i<5;i++)
	{
		write(bit[i]); 
	}
	
	read();	
	printf("END of Crane comm \n");
	CloseHandle(hSerial);
	return;

}


void portinit()
{
	
	printf("initializing the ports \n ");
	hSerial = CreateFile("COM1",
	GENERIC_READ | GENERIC_WRITE,
	0,
	0,
	OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL,
	0);
	if(hSerial==INVALID_HANDLE_VALUE)
	{
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{
		printf("error 1  \n");					//serial port does not exist. Inform user.
		}
		else 
		printf("success 1");
		printf("error 2  \n");					//serial port does not exist. Inform user.
	}
	else 
		printf("success 2  \n");
	
	
	// setting the port parameters like start-stop bits and baude etc.
	
	
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) 
	{
	printf("error 3  \n");					//serial port does not exist. Inform user.
	}
	else 
		printf("success 3   \n");
	dcbSerialParams.BaudRate=CBR_300;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	if(!SetCommState(hSerial, &dcbSerialParams))
	{
	printf("error 4  \n");					//serial port does not exist. Inform user.
	}
	else
		printf("success 4  \n");

	///////////// Time Outs //////////////////////

	COMMTIMEOUTS timeouts={0};
	//timeouts.ReadIntervalTimeout=50;	//specifes how long (in milliseconds) to wait between receiving characters before timing out.		
	
	//timeouts.ReadTotalTimeoutConstant=10000;	//species how long to wait (in milliseconds) before returning.
	
	//timeouts.ReadTotalTimeoutMultiplier=10;	//species how much additional time to wait (in milliseconds) before returning for each byte that was requested in the read operation.
	//timeouts.WriteTotalTimeoutConstant=50;	// do the same thing, just for writes instead of reads.
	//timeouts.WriteTotalTimeoutMultiplier=10;	// do the same thing, just for writes instead of reads.
	
	if(!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("Time Out Error \n");//error occureed. Inform user
	}

}

void write(char i)
{
	//printf("Enter Your Input: ");
	//scanf(" %c %c", &szBuff[0], &szBuff[1]);
	//printf("szbuff= %c",szBuff[0]);

	if(!WriteFile(hSerial, &i, 1, &dwBytesRead, NULL))
	{
			printf("error 6  \n");					//serial port does not exist. Inform user.
	}
	else
			printf("success 6  \n");

}


void read()
{
	
	if(!ReadFile(hSerial, szBuff, 2, &dwBytesRead, NULL))
	{
	printf("error 5  \n");					//serial port does not exist. Inform user.
	}
	else
	{	printf("success 5  \n" );
		printf("\ndwBytesRead- %d \n", dwBytesRead);
		
	}
		
}


void crc8(unsigned char in, unsigned char *crc )
{
	int i;

	*crc= *crc ^ in;

	for(i=0;i<8;i++)
	{
		*crc = (*crc & 0x80) ? (*crc << 1) ^ POLY : (*crc << 1); 
	}

	return;
}
