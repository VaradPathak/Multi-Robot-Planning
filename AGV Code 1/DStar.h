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
	char h;
	char f;
	enum t i;
	char k;
};
struct node n[4][4];

////////////////////initialize all nodes as new///////////////

int r,s;
for(r=0;r<4;r++)
{
	for(s=0;r<4;r++)
	n[r][s].i=neu;
}

//////////////update the cost values////////////////////Insert function////

void modify_cost(void);
void modify_cost(void)
{
	int l,z;
	for(l=0;l<4;l++)						
	{
		for(z=0;z<4;z++)
		hnew[l][z]=h_new(l,z,G[0],G[1]);
		if(i[l][z]==open)							//k(X)= min (k(X), hnew) if t(X) = OPEN
		{
			if(hnew[l][z]<k[l][z])
			k[l][z]=hnew[l][z];
		}
		if(i[l][z]==neu)										//k(x)=hnew if t(x)=neu
		{
			k[l][z]=hnew[l][z];
		}
		if(i[l][z]==closed)									//k(X)=min(h(X),hnew) if t(x)=closed
		{
			if(hnew[l][z]<h[l][z])
			k[l][z]=hnew[l][z];
			i[l][z] =open;
		}
	}
}	

//////////////////////////Sorts the open list according to the values of k(x)//////////min_state function////////

void quicksort(int, int);
void quicksort(int lower, int upper)
{
	int i;
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
	int i,p,q,t;
	p=lower+1;
	q=upper;
	i=open[lower];
	
	while(q>=p)
	{
		while(open[p]<i)
		p++;
		
		while(open[q]>i)
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