/* Library Containing Functions for Triangulation Methods */

/* Function that Warns for a Error on Runtime */
void OnMemoryError(void)
{
    closegraph();
    system("CLS");
    textcolor(4) , cputs("Error al Asignar Memoria Necesaria Para los Puntos\n\r");
    system("Pause") , abort() ;
}

/* Function that Allocs the Necessary Amount of Memory to Process the Cloud of Points */
Graph *ArrayMemoryConstructor(Quantity requestedPoints)
{
    Graph *PointsCloudMemory = NULL;
    Quantity requiredMemory = requestedPoints * sizeof(Graph) ;

    PointsCloudMemory = (Graph *) malloc(requiredMemory);

    /* Allocate memory Was Successful */
    if (PointsCloudMemory != NULL)
        memset((Graph *)PointsCloudMemory, 0, requiredMemory);
    else
        OnMemoryError();

    /* Return A Pointer to the Clean Memory Allocation */
    return PointsCloudMemory;
}

/* Function that allocs Necessary Amount of Memory to contains Points Coordinates */
AxisStruct *StructMemoryConstructor(Quantity requestedPoints)
{
    AxisStruct *PointsMemory = NULL;
    Quantity requiredMemory = (requestedPoints * sizeof(AxisStruct));

    PointsMemory = (AxisStruct *) malloc(requiredMemory);

    /* Allocate memory Was Successful */
    if (PointsMemory != NULL)
        memset((AxisStruct *)PointsMemory, 0, requiredMemory);
    else
        OnMemoryError();

    /* Return A Pointer to the Clean Memory Allocation */
    return PointsMemory;
}

/* Function that Destroy Array Memory Allocated for the Cloud of Points */
void ArrayMemoryDestructor(Graph PointsCloudMemory[])
{
    /* If Array Memory was Passed Correctly */
    if (PointsCloudMemory != NULL)
        free(PointsCloudMemory) , PointsCloudMemory = NULL ;
}

/* Function that Destroy Memory Allocated for Points Coordinates */
void StructMemoryDestructor(AxisStruct *PointsMemory)
{
    /* If Structure was Passed Correctly */
    if (PointsMemory != NULL)
        free(PointsMemory) , PointsMemory = NULL ;
}

/* Function that Closes a Polygon Using Only a Cloud of Points: and Return this but Sorted */
AxisStruct *CreatePolygon(Quantity nPoints, AxisStruct CloudOfPoints[])
{
    Axis x = 0, y = 0;
    Iteration i = 0, j = 0, k = 0;

    Axis yHighest = CloudOfPoints[0].y;
    Axis yLowest  = CloudOfPoints[0].y;
    Axis yAverageDistance = 0;
    
    Graph *polygonPoints = NULL;
    
    AxisStruct *PointsOfTheFirstSector  = NULL;
    AxisStruct *PointsOfTheSecondSector = NULL;
    
    Quantity nPointsOfTheFirstSector  = 0;
    Quantity nPointsOfTheSecondSector = 0;
    
    /* Get Highest and Lowest value on the Cloud of Points */
    for (i = 0; i < nPoints; ++i)
        if (yHighest <= CloudOfPoints[i].y)
            yHighest = CloudOfPoints[i].y;
        else if (yLowest >= CloudOfPoints[i].y)
            yLowest = CloudOfPoints[i].y;

    /* Getting Middle Distance Between this two Points */
    yAverageDistance = (((yHighest - yLowest) / 2) + yLowest);

    /* Getting Number of Points for Each Sector */
    for (i = 0; i < nPoints; ++i)
        (CloudOfPoints[i].y <= yAverageDistance) ? nPointsOfTheFirstSector++ : nPointsOfTheSecondSector++ ;

    /* Allocking Memory to Process Sectors of the Cloud of Points */
    PointsOfTheFirstSector  = StructMemoryConstructor(nPointsOfTheFirstSector);
    PointsOfTheSecondSector = StructMemoryConstructor(nPointsOfTheSecondSector);
    
    /* Splitting Cuadrants */
    for (i = 0, j = 0, k = 0; i < nPoints; ++i)
        if (CloudOfPoints[i].y <= yAverageDistance) /* Splitting First Quadrant */
        {
            PointsOfTheFirstSector[j].x = CloudOfPoints[i].x;
            PointsOfTheFirstSector[j].y = CloudOfPoints[i].y;
            j++;
        } else {                                    /* Splitting Second Quadrant */
            PointsOfTheSecondSector[k].x = CloudOfPoints[i].x;
            PointsOfTheSecondSector[k].y = CloudOfPoints[i].y;
            k++;
        }

    /* Sort Ascending Points of the First Sector */
    for (i = 0; i < nPointsOfTheFirstSector; i++)
        for (j = nPointsOfTheFirstSector - 1; j > i; j--)
            if (PointsOfTheFirstSector[j - 1].x > PointsOfTheFirstSector[j].x)
            {
                x = PointsOfTheFirstSector[j - 1].x;
                y = PointsOfTheFirstSector[j - 1].y;

                PointsOfTheFirstSector[j - 1].x = PointsOfTheFirstSector[j].x;
                PointsOfTheFirstSector[j - 1].y = PointsOfTheFirstSector[j].y;

                PointsOfTheFirstSector[j].x = x;
                PointsOfTheFirstSector[j].y = y;
            }

    /* Sort Descending Points of the Second Sector */
    for (i = 0; i < nPointsOfTheSecondSector; i++)
        for (j = nPointsOfTheSecondSector - 1; j > i; j--)
            if (PointsOfTheSecondSector[j - 1].x < PointsOfTheSecondSector[j].x)
            {
                x = PointsOfTheSecondSector[j - 1].x;
                y = PointsOfTheSecondSector[j - 1].y;

                PointsOfTheSecondSector[j - 1].x = PointsOfTheSecondSector[j].x;
                PointsOfTheSecondSector[j - 1].y = PointsOfTheSecondSector[j].y;

                PointsOfTheSecondSector[j].x = x;
                PointsOfTheSecondSector[j].y = y;
            }

    /* Increase by 1 the Number of Points to store Coordinates of the end of polygon */
    nPoints += 1;
    polygonPoints = ArrayMemoryConstructor(nPoints * 2);

    /* Joining Both Sectors into one Array and Saving Sorted Cloud of Points */
    for (i = 0, j = 0, k = 0; j < nPointsOfTheFirstSector; i += 2, ++j, ++k)
    {
        /* Jonining First Sector to Array */
        polygonPoints[i]     = PointsOfTheFirstSector[j].x;
        polygonPoints[i + 1] = PointsOfTheFirstSector[j].y;

        /* Resaving Sorted Cloud of Points */
        CloudOfPoints[k].x = PointsOfTheFirstSector[j].x;
        CloudOfPoints[k].y = PointsOfTheFirstSector[j].y;
    }
    for (j = 0; j < nPointsOfTheSecondSector; i += 2, ++j, ++k)
    {
        polygonPoints[i]     = PointsOfTheSecondSector[j].x;
        polygonPoints[i + 1] = PointsOfTheSecondSector[j].y;

        /* Resaving Sorted Cloud of Points */
        CloudOfPoints[k].x = PointsOfTheSecondSector[j].x;
        CloudOfPoints[k].y = PointsOfTheSecondSector[j].y;
    }

    /* Closing Last Coordinates of the Polygon */
    polygonPoints[i]     = PointsOfTheFirstSector[0].x;
    polygonPoints[i + 1] = PointsOfTheFirstSector[0].y;

    setcolor(6);
    drawpoly(nPoints, polygonPoints);

    /* Deallocating Memory */
    ArrayMemoryDestructor(polygonPoints);
    StructMemoryDestructor(PointsOfTheFirstSector);
    StructMemoryDestructor(PointsOfTheSecondSector);

    /* Return Sorted Cloud Of Points */
    return CloudOfPoints;
}


#define X 0
#define Y 1
#define DIM 2
#define PMAX 1000


void PointAssign(int [],int []);
void Triangulate(int,int [][2]);
void TriRecurse(int,int [][2],int []);
void ClipEar(int,int,int [][2],int []);

Boolean LeftOn(int [],int [],int []);
Boolean Between(int [],int [],int []);
Boolean Collinear(int [],int [],int []);
Boolean InCone(int,int,int,int [][2]);
Boolean Diagonal(int,int,int,int [][2]);
Boolean Diagonalie(int,int,int,int [][2]);
Boolean Intersect(int [],int [],int [],int []);
Boolean Left(int [],int [],int []);
Boolean IntersectProp(int [],int [],int [],int []);
Boolean Xor(Boolean x, Boolean y);

long Area2(int [],int [],int []);


void MonotoneTriangulation(Quantity nPoints, AxisStruct CloudOfPoints[])
{
    Iteration i = 0;
    int P[PMAX][2];

    for (i = 0; i < nPoints; ++i)
    {
        P[i][X] = CloudOfPoints[i].x;
        P[i][Y] = CloudOfPoints[i].y;
    }

    for (i = 0; i < nPoints; ++i)
    {   
        gotoxy(9,1 + i);
        printf("%d %d\n", P[i][X], P[i][Y]);
    }

    Triangulate(nPoints, P);
}



long Area2(int a[],int b[],int c[])
{
   long area;
   area = (long)(b[0]-a[0])*(long)(c[1]-a[1]);
   area-= (long)(b[1]-a[1])*(long)(c[0]-a[0]);
   return(area);
}

Boolean Left(int a[],int b[],int c[])
{
  return Area2(a,b,c)>0;
}

Boolean LeftOn(int a[],int b[],int c[])
{
  return(Area2(a,b,c)>=0);
}

Boolean Collinear (int a[],int b[],int c[])
{
  return(Area2(a,b,c)==0);
}

Boolean IntersectProp(int a[],int b[],int c[],int d[])
{
  if(Collinear(a,b,c)||Collinear(a,b,d)||Collinear(c,d,a)||Collinear(c,d,b))
      return false;
  return(Xor(Left(a,b,c),Left(a,b,d))&&Xor(Left(c,d,a),Left(c,d,b)));
}

Boolean Between(int a[],int b[],int c[])
{
  if(!Collinear(a,b,c))
       return false;
  if(a[X]!=b[X])
       return((a[X]<=c[X])&&(c[X]<=b[X]))||((a[X]>=c[X])&&(c[X]>=b[X]));
  else
       return((a[Y]<=c[Y])&&(c[Y]<=b[Y]))||((a[Y]>=c[Y])&&(c[Y]>=b[Y]));
}

Boolean Intersect(int a[],int b[],int c[],int d[])
{
   if(IntersectProp(a,b,c,d))
       return true;
   else
   if(Between(a,b,c)||Between(a,b,d)||Between(c,d,a)||Between(c,d,b))
       return true;
   else
       return false;
}

Boolean Diagonalie(int i,int j,int n,int P[][2])
{
   int k,k1;
   for(k=0;k<n;k++)
       {
         k1=(k+1)%n;
         if(!((k==i)||(k1==i)||(k==j)||(k1==j)))
              if(Intersect(P[i],P[j],P[k],P[k1]))
                  return false;
       }
       return true;
}

Boolean InCone(int i,int j,int n,int P[][2])
{
   int i1,in1;
   i1=(i+1)%n;
   in1=(i+n-1)%n;

   if(LeftOn(P[in1],P[i],P[i1]))
      return(Left(P[i],P[j],P[in1])&& Left(P[j],P[i],P[i1]));
   else
      return(!(LeftOn(P[i],P[j],P[i1])&& LeftOn(P[j],P[i],P[in1])));
}

Boolean Diagonal(int i,int j,int n,int P[][2])
{
   return(InCone(i,j,n,P)&& Diagonalie(i,j,n,P));
}

void Triangulate(int n,int P[][2])
{
   int Pt[PMAX][2];
   int labels[PMAX], i = 0;
   int j = 0;

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

   TriRecurse(n,P,labels);

}

void ClipEar(int i,int n,int P[][2],int labels[])
{
  int k;
  for(k=i;k<(n-1);k++)
   {
     PointAssign(P[k],P[k+1]);
     labels[k]=labels[k+1];
   }
}

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

         setfillstyle(SOLID_FILL, 1);

         /*floodfill(t1, t2, 0);*/

         ClipEar(i1,n,P,labels);

         TriRecurse(n-1,P,labels);
         break;
         }
      }
}

Boolean Xor(Boolean x,Boolean y)
{
  return(!x^!y);
}

void PointAssign(int a[],int b[])
{
   int i;
   for(i=0;i<DIM;i++)
   a[i]=b[i];
}