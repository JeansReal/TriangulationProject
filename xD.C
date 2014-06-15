***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
/*         Techer >> Grevin Silva           */
***REMOVED***

/* Include Source Files Only Once in Compilation */
#pragma once

/* Header Files and Libraries */
#include <StdIo.h>      /* Functions for Data Output>> printf() */
#include <Conio.h>      /* Check Controls Keys>> kbhit() */
#include <Graphics.h>   /* Borland Graphic Environment */ 
#include <StdLib.h>     /* System Commands>> system() , abort() , exit() */
#include <Mouse.h>      /* Function to Show Mouse and Events>> mver() */

/* Helpers */
#include "Helper/Macro.h"      /* Macros and Constants */
#include "Helper/Mode.h"       /* Graphic Mode (GUI) */
#include "Helper/UserMov.h"    /* User Control Movement (UX) */
#include "Helper/Screens.h"    /* UI Funtions */

/* Prototype Functions */
/* Functions For Graphic Mode */
void InitGraph(void);
/* Functions for User Movement (Mouse, Cursor) */
enum UserMovementControl UserControl(void);
void DrawCursor(Axis x, Axis y);
EventHandler ReadKey(void);
/* Function to Animate Controls(Buttons) */
enum Button DrawButton(Axis x, Axis y, Boolean Status, enum Button btnId);
enum Button ButtonEvents(Boolean Status, enum Button btnId);
enum Button HoverButton(Axis x, Axis y);
/* Functions that Contains the full GUI */
void WorkSpace(void);
void MainFrame(void);


void ClosePolygon(Quantity nPoints, struct pointtype Points[]);

/** Main Body **/
void main(void)
{
    Axis x = 320, y = 240, xClick = 0, yClick = 0;
    EventHandler Event = NONE;
    Boolean clickPress = false;

    struct pointtype Points[50];
    static Quantity nPoints = 0;

    InitGraph();

    _activeMovementControl = Mouse;  /* UserControl(); */
    
    MainFrame();
    
    (_activeMovementControl == Mouse) ? mver() : DrawCursor(x, y) ;

    do {
        /* Axis Movement, Event Handlers */
        if (_activeMovementControl == Keyboard)
        {
            Event = ReadKey();
            DrawCursor(x, y);
        } else {                          /* Mouse is Active */

            if (mclick() == CLICK)        /* If the User is Pressing Click */
            {
                if (!clickPress)          /* If the User has not Pressed Click */
                {
                    clickPress = true;    /* Activate Flag(clickPress) and Capture Click Position */
                    xClick = mxpos(1);
                    yClick = mypos(1);

                    xClick += yClick;
                    yClick += xClick;
                }
            }
            else if (clickPress)          /* if the click is released */
            {
                Event = CLICK;
                clickPress = false;
            }

            x = mxpos(1);
            y = mypos(1);
        }

        if (IsOutsideWorkSpace(x, y))
		   _hoverButton = HoverButton(x, y);

        switch (Event)
        {
            case UP:    y -= CanMoveUp(y)    break;
            case DOWN:  y += CanMoveDown(y)  break;
            case RIGHT: x += CanMoveRight(x) break;
            case LEFT:  x -= CanMoveLeft(x)  break;

            case ENTER: case CLICK:
                if (_hoverButton == NONE)
                {
                    if (nPoints > 50) exit(1);

                    Points[nPoints].x = mxpos(1);
                    Points[nPoints].y = mypos(1);

                    setcolor(4);
                    settextstyle(0, 0, 1);
                    mocultar();

                    outtextxy(Points[nPoints].x, Points[nPoints].y, "x");
                    
                    mver();

                    /*gotoxy(1,nPoints + 1);
                    printf("%d %d", Points[nPoints].x, Points[nPoints].y);*/
                    nPoints++;

                } else {                        /* If a Button Was Selected */
                    switch (_hoverButton)
                    {
                        case btnInputVector:    ButtonEvents(false, btnInputVector);   break;
                        
                        case btnCloseVector:
                            ButtonEvents(false, btnCloseVector);
                            ClosePolygon(nPoints, Points);
                        break;

                        case btnMonotone:       ButtonEvents(false, btnMonotone);      break;
                        case btnTrapezoidal:    ButtonEvents(false, btnTrapezoidal);   break;
                        case btnRestore:        WorkSpace(); ButtonEvents(false, btnRestore);       break;
                        case btnExit:           closegraph();       exit(0);
                    }

                    /* Realocating Cursor */
                    (_activeMovementControl == Keyboard) ? x = 320 , y = 240 : msituar(1, 320, 240) ;
                }

                _hoverButton = Event = NONE;
            break;
        }

        if (_activeMovementControl == Keyboard) /* Redraws Cursor For more UX! */
            DrawCursor(x, y);

    } while (mclick() != 2);
}

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