void init(void);
void poll(char,char);
void agv(char);
char distance(char, char, char, char);
void clock(void);
void anti(void);
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
#define STATUS 0x05


// current AGV directions
#define W 3
#define S 2
#define E 1
#define N 0

enum t
{
	ocq,free 
};

struct node
{
	enum t i;
	
};
struct node n[4][4];
struct agv
{
	char next_dir,current_dir;
	char x,y,gx,gy;
	enum t p;	
};
struct agv a[3];


void init()
{
	// set all nodes as free
	// set all agvs as free
	//set current dir as North
}

void poll(char add,char data)
{
	crane_comm(add,data);
	
	if (szBuff[3]==REQ)
	{
		//check free AGV
		//if free then assign new goal to AGV
		//notify crane 
	}
	else if(szBuff[3]==NO_REQ)
	{
		//take no action
	}
	else if(szBuff[3]==AGV_LOADED)
	{
		//assign new goal as SC
		//change the tag as busy

	}
	else if(szBuff[3]==AGV_UNLOADED)
	{
		//change the tag as free
		//if no req is there then send the agv to buffer area
		// else assign new goal
	}
}


agv(char add)
{
		char cx,cy,g[3],h[3],f[3],t;
		cx=a[add]->x;
		cy=a[add]->y
		
			/////////////////for NORTH direction//////////////////	
			
		if(a[add]->current_dir==N)	
		{
			if ( cx+1 <=3 && cx+1 >=0 && n[cx+1][cy]->i==free)
			{
				h[0]=distance(cx+1,cy,a[add]->gx,a[add].gy);
				g[0]=5;
				f[0]=g[0]+h[0];
			}
			else
			{
				f[0]=0xff;			
			}

			if ( cx-1 <=3 && cx-1 >=0 && n[cx-1][cy]->i==free)
			{
				h[1]=distance(cx-1,cy,a[add]->gx,a[add].gy);
				g[1]=5;
				f[1]=g[1]+h[1];
			}
			else
			{
				f[1]=0xff;			
			}
			if ( cy+1 <=3 && cy+1 >=0 && n[cx][cy+1]->i==free)
			{
				h[2]=distance(cx,cy+1,a[add]->gx,a[add].gy);
				g[2]=0;
				f[2]=g[2]+h[2];
			}
			else
			{
				f[2]=0xff;			
			}			
		}
		
	
		/////////////////for EAST direction//////////////////
		
		else if(a[add]->current_dir==E)				
		{
			if ( cx+1 <=3 && cx+1 >=0 && n[cx+1][cy]->i==free)
			{
				h[0]=distance(cx+1,cy,a[add]->gx,a[add].gy);
				g[0]=0;
				f[0]=g[0]+h[0];
			}
			else
			{
				f[0]=0xff;			
			}

			if ( cy+1 <=3 && cy+1 >=0 && n[cx][cy+1]->i==free)
			{
				h[1]=distance(cx,cy+1,a[add]->gx,a[add].gy);
				g[1]=5;
				f[1]=g[1]+h[1];
			}
			else
			{
				f[1]=0xff;			
			}
			if ( cy-1 <=3 && cy-1 >=0 && n[cx][cy-1]->i==free)
			{
				h[2]=distance(cx,cy-1,a[add]->gx,a[add].gy);
				g[2]=5;
				f[2]=g[2]+h[2];
			}
			else
			{
				f[2]=0xff;			
			}			
		}

		/////////////////for SOUTH direction//////////////////
		
		else if(a[add]->current_dir==S)				
		{
			if ( cx-1 <=3 && cx-1 >=0 && n[cx-1][cy]->i==free)
			{
				h[0]=distance(cx-1,cy,a[add]->gx,a[add].gy);
				g[0]=5;
				f[0]=g[0]+h[0];
			}
			else
			{
				f[0]=0xff;			
			}

			if ( cx+1 <=3 && cx+1 >=0 && n[cx+1][cy]->i==free)
			{
				h[1]=distance(cx+1,cy,a[add]->gx,a[add].gy);
				g[1]=5;
				f[1]=g[1]+h[1];
			}
			else
			{
				f[1]=0xff;			
			}
			if ( cy-1 <=3 && cy-1 >=0 && n[cx][cy-1]->i==free)
			{
				h[2]=distance(cx,cy-1,a[add]->gx,a[add].gy);
				g[2]=0;
				f[2]=g[2]+h[2];
			}
			else
			{
				f[2]=0xff;			
			}			
		}


		/////////////////for WEST direction//////////////////
		
		else if(a[add]->current_dir==W)				
		{
			if ( cx-1 <=3 && cx-1 >=0 && n[cx-1][cy]->i==free)
			{
				h[0]=distance(cx-1,cy,a[add]->gx,a[add].gy);
				g[0]=0;
				f[0]=g[0]+h[0];

			}
			else
			{
				f[0]=0xff;			
			}

			if ( cy-1 <=3 && cy-1 >=0 && n[cx][cy-1]->i==free)
			{
				h[1]=distance(cx,cy-1,a[add]->gx,a[add].gy);
				g[1]=5;
				f[1]=g[1]+h[1];
			}
			else
			{
				f[1]=0xff;			
			}
			if ( cy+1 <=3 && cy+1 >=0 && n[cx][cy+1]->i==free)
			{
				h[2]=distance(cx,cy+1,a[add]->gx,a[add].gy);
				g[2]=5;
				f[2]=g[2]+h[2];
			}
			else
			{
				f[2]=0xff;			
			}			
		}

		

}

void anti()
{
   if(dir==0)
   dir=4;
   dir--;
}

void clock()
{
   dir++;
   if(dir>3)
   dir=0;
}


char distance(char x1, char y1, char gx1, char gy1)
{
	unsigned char p,q;
	char d;
	p=gx1-x1;
	q=gy1-y1;
	d=p+q;
	return (d*5);
}

void main()
{
	while(1)
	{
		poll(LC1,STATUS);
		poll(LC2,STATUS);
		poll(SC,STATUS);
		agv(0);
		agv(1);
		agv(2);
	}


}