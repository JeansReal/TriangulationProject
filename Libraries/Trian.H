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
        memset(PointsCloudMemory, 0, requiredMemory);
    else
        OnMemoryError();

    /* Return A Pointer to the Clean Memory Allocation */
    return PointsCloudMemory;
}

/* Function that Destroy Array Memory Allocated for the Cloud of Points */
void ArrayMemoryDestructor(Graph PointsCloudMemory[])
{
    /* If Array Memory was Passed Correctly */
    if (PointsCloudMemory != NULL)
        free(PointsCloudMemory) , PointsCloudMemory = NULL ;
}

/* Function that allocs Necessary Amount of memory to contains Points Coordinates */
AxisStruct *StructMemoryConstructor(Quantity requestedPoints)
{
    AxisStruct *PointsMemory = NULL;
    Quantity requiredMemory = (requestedPoints * sizeof(AxisStruct));

    PointsMemory = (AxisStruct *) malloc(requiredMemory);

    /* Allocate memory Was Successful */
    if (PointsMemory != NULL)
        memset(PointsMemory, 0, requiredMemory);
    else
        OnMemoryError();

    /* Return A Pointer to the Clean Memory Allocation */
    return PointsMemory;
}

/* Function that Destroy Memory Allocated for Points Coordinates */
void StructMemoryDestructor(AxisStruct *PointsMemory)
{
    /* If Structure was Passed Correctly */
    if (PointsMemory != NULL)
        free(PointsMemory) , PointsMemory = NULL ;
}

/* Function that Closes a Polygon Using Only a Cloud of Points */
void ClosePolygon(Quantity nPoints, AxisStruct CloudOfPoints[])
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

    /* Joining Both Sectors into one Array */
    for (i = 0, j = 0; j < nPointsOfTheFirstSector; i += 2, j++)
    {
        polygonPoints[i]     = PointsOfTheFirstSector[j].x;
        polygonPoints[i + 1] = PointsOfTheFirstSector[j].y;
    }
    for (j = 0; j < nPointsOfTheSecondSector; i += 2, j++)
    {
        polygonPoints[i]     = PointsOfTheSecondSector[j].x;
        polygonPoints[i + 1] = PointsOfTheSecondSector[j].y;
    }

    /* Closing Polygon */
    polygonPoints[i]     = PointsOfTheFirstSector[0].x;
    polygonPoints[i + 1] = PointsOfTheFirstSector[0].y;

    drawpoly(nPoints, polygonPoints);

    /* Deallocating Memory */
    ArrayMemoryDestructor(polygonPoints);
    StructMemoryDestructor(PointsOfTheFirstSector);
    StructMemoryDestructor(PointsOfTheSecondSector);
}