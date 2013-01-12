/////////////////////tag a node////////////////////////////

enum t
{
	closed, open, neu 
};

/////////////////////map the whole grid///////////////////

struct node
{
	//char g;
	char hnew;
	char h,x,y,temp;
	char f;
	enum t i;
	char k;
};
struct node n[16];
char *open[16];
int r,s;

s=0;
for (y=0;y<16;y++)
{
	if(n[y].i==open)
	{
		n[y].temp=n[y].k;
	}
	else 
		n[y].temp=0xff;
	open[y]=n+y;
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



////////////////////initialize all nodes as new///////////////


for(r=0;r<16;r++)
{
	n[r].i=neu;
}

//////////////update the cost values////////////////////

void modify_cost(void);
void modify_cost(void)
{
	int l;
	for(l=0;l<16;l++)						
	{
		hnew[l]=h_new(n[l].x,n[l].y,G[0],G[1]);
		if(i[l]==open)							//k(X)= min (k(X), hnew) if t(X) = OPEN
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

void quicksort(int, int);
void quicksort(int lower,int upper)
{
	int i;
	lower=0;
	upper=15;
	if(upper>lower)
	{
		i=split(lower,upper);
		quicksort(lower,i-1);
		quicksort(i+1,upper);
	}
}
int split(int,int);
int split(int lower, int upper)
{
	int i,p,q;
	char *t;
	p=lower+1;
	q=upper;
	i=(*(open[lower])).temp;
	
	while(q>=p)
	{
		while((*(open[p]).temp)<i)
		p++;
		
		while((*(open[q]).temp)>i)
		q--;
		
		if(q>p)
		{
			t=open[p];
			open[p]=open[q];
			open[q]=t;
		}
	}
	
	t=open[lower];
	open[lower]=open[q];
	open[q]=t;
	
	return q;
}

//////////////path cost function calculates the Manhatten dist between X and G//////////////////////

char h_new(char, char, char, char);			
char h_new(char x1, char x2, char g1, char g2)
{
	unsigned char p,q;
	char d;
	p=g1-x1;
	q=g2-x2;
	d=p+q;
	return d;
}


