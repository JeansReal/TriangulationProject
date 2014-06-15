/* Library Containing Functions for Triangulation Methods */

/* Function that Closes a Polygon Using Only a Cloud of Points */
void ClosePolygon(Quantity nPoints, struct pointtype Points[])
{
    int i,j;
    int tempa;
    int tempb;
    int *temp = (int *) calloc(nPoints * 2, sizeof(temp));

    int higher = Points[0].y;
    int lower = Points[0].y;
    int middle = 0;

    int separation = 0;

    int temp1x[30] = {0};
    int temp1y[30] = {0};
    int temp2x[30] = {0};
    int temp2y[30] = {0};
 
    /* Obtener el Punto mas Alto y el mas Bajo en el eje Y */
    for(i = 0; i < nPoints; ++i)
    {
        if(higher < Points[i].y)
            higher = Points[i].y;

        if (lower > Points[i].y)
            lower = Points[i].y;
    }

    /* Getting Middle Distance Between this two Points */
    middle = ((higher - lower) / 2);
    middle += lower;

    setcolor(4);

    line(0, higher, getmaxx(), higher);
    line(0, lower, getmaxx(), lower);
    line(0, middle, getmaxx(), middle);

    setcolor(0);

    /* Spliting Cuadrants */

    /* First Cuadrant */
    for (i = 0, j = 0, separation = 0; i < nPoints; ++i)
    {
        if (Points[i].y <= middle)
        {
            temp1x[j] = Points[i].x;
            temp1y[j] = Points[i].y;
            j++;
            separation++;
        }
    }

    /* Second Cuadrante */
    for (i = 0, j = 0; i < nPoints; ++i)
    {
        if (Points[i].y >= middle)
        {
            temp2x[j] = Points[i].x;
            temp2y[j] = Points[i].y;
            j++;
        }
    }

    /* Ordenar de Ascendentemente los Puntos del Primer Cuadrante */
    for (i = 0; i < separation; i++)
        for (j = separation - 1; j > i; j--)
        {
            if (temp1x[j - 1] > temp1x[j])
            {
                tempa = temp1x[j - 1];
                tempb = temp1y[j - 1];

                temp1x[j - 1] = temp1x[j];
                temp1y[j - 1] = temp1y[j];

                temp1x[j] = tempa;
                temp1y[j] = tempb;
            }
        }

    /* Ordenar de Descendentemente los Puntos del Segundo Cuadrante */
    for (i = 0; i < nPoints - separation; i++)
        for (j = nPoints - separation - 1; j > i; j--)
        {
            if (temp2x[j - 1] < temp2x[j])
            {
                tempa = temp2x[j - 1];
                tempb = temp2y[j - 1];

                temp2x[j - 1] = temp2x[j];
                temp2y[j - 1] = temp2y[j];

                temp2x[j] = tempa;
                temp2y[j] = tempb;
            }
        }


    /*gotoxy(1,6);
    for (i = 0; i < separation; ++i)
        printf("\n%d %d", temp1x[i], temp1y[i]);

    gotoxy(1,10);
    for (i = 0; i < nPoints - separation; ++i)
        printf("\n%d %d", temp2x[i], temp2y[i]);*/

    /* Uniendo los Dos Arreglos */
    for (i = 0, j = 0; j < separation; i+=2, j++)
    {
        temp[i]     = temp1x[j];
        temp[i + 1] = temp1y[j];
    }

    for (j = 0; j < nPoints - separation; i+=2, j++)
    {
        temp[i]     = temp2x[j];
        temp[i + 1] = temp2y[j];
    }


    /*temp[i]     = temp1x[0];
    temp[i + 1] = temp1y[0];*/


    /*for (i = 0, j = 0; temp[i] != 0 ; i+=2, j++)
    {                            
        gotoxy(9,1 + j);
        printf("%d %d", temp[i], temp[i + 1]);
    }*/



    drawpoly(nPoints + 1, temp);

    free(temp);
    temp = NULL;
}