//////////////////function declearation///////////////////
int split(int,int);
void modify_cost(void);
void get_kmin(void);
void quicksort(int, int);
char h_new(char, char, char, char);
void process_state(void);
/////////////////////tag a node////////////////////////////

enum t
{
	closed, open, neu 
};
char X;
char S[2]={0,0};
char G[2]={0,0};

/////////////////////map the whole grid///////////////////

struct node
{
	//char g;
	char hnew;
	char h,x,y,temp;
	char f;
	enum t i;
	char k;
	struct node *backptr;
};
struct node n[16];
struct node *openlist[16];
int r,s,y;
void init(void);
void init()
{
	n[0].x=0;n[0].y=0;
	n[1].x=1;n[1].y=0;
	n[2].x=2;n[2].y=0;
	n[3].x=3;n[3].y=0;
	n[4].x=0;n[4].y=1;
	n[5].x=1;n[5].y=1;
	n[6].x=2;n[6].y=1;
	n[7].x=3;n[7].y=1;
	n[8].x=0;n[8].y=2;
	n[9].x=1;n[9].y=2;
	n[10].x=2;n[10].y=2;
	n[11].x=3;n[11].y=2;
	n[12].x=0;n[12].y=3;
	n[13].x=1;n[13].y=3;
	n[14].x=2;n[14].y=3;
	n[15].x=3;n[15].y=3;


		
	for(p=0;p<16;p++)
	{
		n[p].i=neu;
	}
	
}

////////////////////get_min function////////////////////////

void get_kmin()
{
	for (y=0;y<16;y++)
	{
		if(n[y].i==open)
		{
			n[y].temp=n[y].k;
		}
		else 
		n[y].temp=0xff;
		openlist[y]=&n[y];
	}
	quicksort(0,15);
}


//////////////update the cost values////////////////////Insert function////


void modify_cost(void)
{
	int l;
	for(l=0;l<16;l++)						
	{
		n[l].hnew=h_new(n[l].x,n[l].y,G[0],G[1]);
		if(n[l].i==open)							//k(X)= min (k(X), hnew) if t(X) = OPEN
		{
			if(n[l].hnew<n[l].k)
			n[l].k=n[l].hnew;
		}
		if(n[l].i==neu)										//k(x)=hnew if t(x)=neu
		{
			n[l].k=n[l].hnew;
		}
		if(n[l].i==closed)									//k(X)=min(h(X),hnew) if t(x)=closed
		{
			if(n[l].hnew<n[l].h)
			n[l].k=n[l].hnew;
			n[l].i=open;
		}
	}
}	

//////////////////////////Sorts the open list according to the values of k(x)//////////min_state function////////

void quicksort(int lower,int upper)
{
	int i;
	if(upper>lower)
	{
		i=split(lower,upper);
		quicksort(lower,i-1);
		quicksort(i+1,upper);
	}
}

int split(int lower, int upper)
{
	int i,p,q;
	struct node *t,*u,*v,*w;
	p=lower+1;
	q=upper;
	u=openlist[lower];
	v=openlist[p];
	w=openlist[q];
	
	i=(*u).temp;
	
	while(q>=p)
	{
		while(((*v).temp)<i)
		p++;
		
		while(((*w).temp)>i)
		q--;
		
		if(q>p)
		{
			t=openlist[p];
			openlist[p]=openlist[q];
			openlist[q]=t;
		}
	}
	
	t=openlist[lower];
	openlist[lower]=openlist[q];
	openlist[q]=t;
	
	return q;
}

//////////////path cost function calculates the Manhatten dist between X and G//////////////////////
char h_new(char x1, char x2, char g1, char g2)
{
	unsigned char p,q;
	char d;
	p=g1-x1;
	q=g2-x2;
	d=p+q;
	return d;
}

void process_state()
{
	int j;
	get_kmin();
	for(j=0;j<16;j++)
	{
		if(openlist[0]==&n[j])
		break;
	}
	
}


















































/*void openlist(int);

struct listnode {
	char *ptr;
	struct listnode *nxtptr;
};

typedef struct listnode LISTNODE;
typedef listnode *LISTNODEPTR;
void insert (LISTNODEPTR * ,char );
char delit (LISTNODEPTR * ,char );
int isemplty(LISTNODEPTR);

void openlist()
{
	LISTNODEPTR startptr=NULL;
	int j;
	for(j=0;j<16;j++)
	{
		if(n[j].i==open)
		{
			insert(&startptr,j);
			
		}
		
	}



}

void insert(LISTNODEPTR *sptr, int j)
{
	LISTNODEPTR newptr, prevptr, currptr;
	newptr=malloc(sizeof(LISTNODE));
	if(newptr!=NULL)
	{
		newptr->ptr=n+j;
		newptr->nxtptr=NULL;
		prevptr=NULL;
		currptr=*sptr;
		
		while(currptr !=NULL && n[j].k > currptr->((*ptr).k))
		{
			
		}
	}
	


}*/
