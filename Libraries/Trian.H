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

    setcolor(0);
    drawpoly(nPoints, polygonPoints);

    /* Deallocating Memory */
    ArrayMemoryDestructor(polygonPoints);
    StructMemoryDestructor(PointsOfTheFirstSector);
    StructMemoryDestructor(PointsOfTheSecondSector);

    /* Return Sorted Cloud Of Points */
    return CloudOfPoints;
}

/* Fuction that Calculates an Area Inside a simple triangle */
long Area2(AxisStruct *A, AxisStruct *B, AxisStruct *C)
{
   long area = 0.00;

   area  = (long)(B->x - A->x) * (long)(C->y - A->y);
   area -= (long)(B->y - A->y) * (long)(C->x - A->x);
   
   return area;
}

Boolean InCone(Iteration i, Iteration j, Quantity nPoints, AxisStruct PolygonPoints[])
{
   Iteration i1 = 0, in1 = 0;

   /* Computing Closest Points */
   i1  = (i + 1) % nPoints;
   in1 = (i + nPoints - 1) % nPoints;

   if (LeftOn(&PolygonPoints[in1], &PolygonPoints[i], &PolygonPoints[i1]))
      return (Left(&PolygonPoints[i], &PolygonPoints[j], &PolygonPoints[in1]) && Left(&PolygonPoints[j], &PolygonPoints[i], &PolygonPoints[i1]));
   else
      return !(LeftOn(&PolygonPoints[i], &PolygonPoints[j], &PolygonPoints[i1]) && LeftOn(&PolygonPoints[j], &PolygonPoints[i], &PolygonPoints[in1]));
}

Boolean IntersectProp(AxisStruct *A, AxisStruct *B, AxisStruct *C, AxisStruct *D)
{
    if (Collinear(A, B, C) || Collinear(A, B, D) || Collinear(C, D, A) || Collinear(C, D, B))
        return false;

    return (Xor(Left(A, B, C), Left(A, B, D)) && Xor(Left(C, D, A), Left(C, D, B)));
}

Boolean Between(AxisStruct *A, AxisStruct *B, AxisStruct *C)
{
  if (!Collinear(A, B, C))
       return false;
  if (A->x != B->x)
       return ((A->x <= C->x) && (C->x <= B->x)) || ((A->x >= C->x) && (C->x >= B->x));
  else
       return ((A->y <= C->y) && (C->y <= B->y)) || ((A->y >= C->y) && (C->y >= B->y));
}

Boolean Intersect(AxisStruct *A, AxisStruct *B, AxisStruct *C, AxisStruct *D)
{
   if (IntersectProp(A, B, C, D))
       return true;
   else if (Between(A, B, C) || Between(A, B, D) || Between(C, D, A) || Between(C, D, B))
       return true;
   else
       return false;
}

Boolean Diagonalie(Iteration i, Iteration j, Quantity nPoints, AxisStruct PolygonPoints[])
{
    Iteration k1 = 0, k2 = 0;

    for (k1 = 0; k1 < nPoints; ++k1)
    {
        k2 = (k1 + 1) % nPoints;

        if (!((k1 == i) || (k2 == i) || (k1 == j) || (k2 == j)))
            if (Intersect(&PolygonPoints[i], &PolygonPoints[j], &PolygonPoints[k1], &PolygonPoints[k2]))
                return false;
    }
    
    return true;
}

void ClipEar(Iteration i, Quantity nPoints, AxisStruct PolygonPoints[])
{
    Iteration k = 0;

    for(k = i; k < (nPoints - 1); ++k)
    {
        PolygonPoints[k].x = PolygonPoints[k + 1].x;
        PolygonPoints[k].y = PolygonPoints[k + 1].y;
    }
}

/* Recursive Function that decomposes a Polygon into multiples monotones Polygons */
void MonotoneTriangulation(Quantity nPoints, AxisStruct PolygonPoints[])
{
    Iteration i1 = 0, i2 = 0, i3 = 0;

    if (nPoints > 3)
        for (i1 = 0; i1 < nPoints; ++i1)
        {
            i2 = (i1 + 1) % nPoints;
            i3 = (i1 + 2) % nPoints;

            if (!Diagonal(i1, i3, nPoints, PolygonPoints))
                continue;

            setcolor(random(15));
            line(PolygonPoints[i1].x, PolygonPoints[i1].y, PolygonPoints[i3].x, PolygonPoints[i3].y);

            ClipEar(i2, nPoints, PolygonPoints);

            MonotoneTriangulation(nPoints - 1, PolygonPoints);
            break;
        }
}