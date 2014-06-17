#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

#define X 0
#define Y 1
#define DIM 2
#define PMAX 1000

typedef enum {FALSE,TRUE} bool;

void PointAssign(int [],int []);
void Triangulate(int,int [][2]);
void TriRecurse(int,int [][2],int []);
void ClipEar(int,int,int [][2],int []);

bool LeftOn(int [],int [],int []);
bool Between(int [],int [],int []);
bool Collinear(int [],int [],int []);
bool InCone(int,int,int,int [][2]);
bool Diagonal(int,int,int,int [][2]);
bool Diagonalie(int,int,int,int [][2]);
bool Intersect(int [],int [],int [],int []);
bool Left(int [],int [],int []);
bool IntersectProp(int [],int [],int [],int []);
bool Xor(bool,bool);

int ReadPoints(int [][2]);
long Area2(int [],int [],int []);

void main(void)
{
	  int P[PMAX][2],n;
	  clrscr();
	  n = ReadPoints(P);
	  Triangulate(n,P);
} 

/**************************************************************/
int ReadPoints(int P[][2])
{
   int n = 0;
   printf("DIGITE LAS ENTRADAS DEL POLIGONO \n");
   printf("VERTICE[i] x y \n");
   while(n<10)
   {
	 scanf("%d%d",&P[n][0],&P[n][1]);
	 printf("PUNTO %3d:[%4d,%4d]\n",n,P[n][0],P[n][1]);
	 ++n;
   }
   if(n<=PMAX)
		  printf("\n n = %dVERTICES LEIDOS\n",n);
   else
		  printf("CANTIDAD DE PUNTOS FUERA DE RANGO");
   printf("\n[PRESIONE UNA TECLA PARA CONTINUAR]\n");
   getch();
   return(n);
}
/**************************************************************/
long Area2(int a[],int b[],int c[])
{
   long area;
   area = (long)(b[0]-a[0])*(long)(c[1]-a[1]);
   area-= (long)(b[1]-a[1])*(long)(c[0]-a[0]);
   return(area);
}
/*************************************************************/
bool Left(int a[],int b[],int c[])
{
  return Area2(a,b,c)>0;
}
/*************************************************************/
bool LeftOn(int a[],int b[],int c[])
{
  return(Area2(a,b,c)>=0);
}
/*************************************************************/
bool Collinear (int a[],int b[],int c[])
{
  return(Area2(a,b,c)==0);
}
/*************************************************************/
bool IntersectProp(int a[],int b[],int c[],int d[])
{
  if(Collinear(a,b,c)||Collinear(a,b,d)||Collinear(c,d,a)||Collinear(c,d,b))
	  return FALSE;
  return(Xor(Left(a,b,c),Left(a,b,d))&&Xor(Left(c,d,a),Left(c,d,b)));
}
/**************************************************************/
bool Between(int a[],int b[],int c[])
{
  if(!Collinear(a,b,c))
	   return FALSE;
  if(a[X]!=b[X])
	   return((a[X]<=c[X])&&(c[X]<=b[X]))||((a[X]>=c[X])&&(c[X]>=b[X]));
  else
	   return((a[Y]<=c[Y])&&(c[Y]<=b[Y]))||((a[Y]>=c[Y])&&(c[Y]>=b[Y]));
}
/*************************************************************/
bool Intersect(int a[],int b[],int c[],int d[])
{
   if(IntersectProp(a,b,c,d))
	   return TRUE;
   else
   if(Between(a,b,c)||Between(a,b,d)||Between(c,d,a)||Between(c,d,b))
	   return TRUE;
   else
	   return FALSE;
}
/***************************************************************/
bool Diagonalie(int i,int j,int n,int P[][2])
{
   int k,k1;
   for(k=0;k<n;k++)
	   {
		 k1=(k+1)%n;
		 if(!((k==i)||(k1==i)||(k==j)||(k1==j)))
			  if(Intersect(P[i],P[j],P[k],P[k1]))
				  return FALSE;
	   }
	   return TRUE;
}
/****************************************************************/
bool InCone(int i,int j,int n,int P[][2])
{
   int i1,in1;
   i1=(i+1)%n;
   in1=(i+n-1)%n;

   if(LeftOn(P[in1],P[i],P[i1]))
	  return(Left(P[i],P[j],P[in1])&& Left(P[j],P[i],P[i1]));
   else
	  return(!(LeftOn(P[i],P[j],P[i1])&& LeftOn(P[j],P[i],P[in1])));
}
/******************************************************************/
bool Diagonal(int i,int j,int n,int P[][2])
{
   return(InCone(i,j,n,P)&& Diagonalie(i,j,n,P));
}
/********************************************************************/
void Triangulate(int n,int P[][2])
{
   int Pt[PMAX][2];
   int labels[PMAX],poly[2*PMAX+2],i;
   int adap=DETECT,modo,j=0;

   clrscr();
   for(i=0;i<n;i++)
   {
	 PointAssign(Pt[i],P[i]);
		 labels[i]=i;
		 poly[j]=P[i][0];
		 poly[++j]=P[i][1];
		 j++;
   }
   poly[j]=P[0][0];
   poly[j+1]=P[0][1];

   initgraph(&adap,&modo,""); 

   drawpoly(n+1,poly);

   TriRecurse(n,P,labels);

  getch();
  getch();
 /*  restorecrtmode();*/
}
/******************************************************************/
void ClipEar(int i,int n,int P[][2],int labels[])
{
  int k;
  for(k=i;k<(n-1);k++)
   {
	 PointAssign(P[k],P[k+1]);
	 labels[k]=labels[k+1];
   }
}

/*******************************************************************/
void TriRecurse(int n,int P[][2],int labels[])
{
  int x,y,x1,y1,i,i1,i2,t1,t2;

  if(n>3)
   for(i=0;i<n;i++)
	 {
	   i1=(i+1)%n;
	   i2=(i+2)%n;

		 if(Diagonal(i,i2,n,P))
		 {
				 x=P[i][0];
				 y=P[i][1];

				 x1=P[i2][0];
				 y1=P[i2][1];

         setcolor(0);
				 line(x,y,x1,y1);

				 t1= (P[i][0]+P[i1][0]+P[i2][0])/3;
				 t2= (P[i][1]+P[i1][1]+P[i2][1])/3;

				 setfillstyle(SOLID_FILL, 4);
				 floodfill(t1,t2,BLACK);

				 ClipEar(i1,n,P,labels);

				 TriRecurse(n-1,P,labels);
				 break;
		 }
	  }
}

/******************************************************************/
bool Xor(bool x,bool y)
{
  return(!x^!y);
}
/*******************************************************************/
void PointAssign(int a[],int b[])
{
   int i;
   for(i=0;i<DIM;i++)
   a[i]=b[i];
}