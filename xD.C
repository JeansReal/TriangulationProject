***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
/*        Profesor>> Grevin Silva           */
***REMOVED***

/* No Incluir Librerias Mas de 1 Vez */
#pragma once

/* Ficheros de Cabezera o Librerias */
#include <StdIo.h>      /* Funciones para salida de datos>> printf() */
#include <Conio.h>      /* Validacion de Control de Teclas>> kbhit() */
#include <Graphics.h>   /* Para Usar El Entorno Grafico de Borland */ 
#include <StdLib.h>     /* Comandos del sistema>> system() , abort() , exit() */
#include <Mouse.h>      /* Funcion para Mostrar Mouse y sus Eventos */

/* Helpers */
#include "Apple/Macro.h"      /* Macros y Constantes */
#include "Apple/Modo.h"       /* Modo Grafico */
#include "Apple/UserMov.h"    /* User Control Movement */
#include "Apple/Screens.h"    /* Funciones de UI */

/* Funciones Prototipo */
/* Funciones Para El Modo Grafico */
void InitGraph(void);
/* Funciones Para El Movimiento del Usuario (Mouse, Cursor) */
enum UserMovementControl UserControl(void);
void DrawCursor(Axis x, Axis y);
int ReadKey(void);
/* Funcion Para Animar Controles(Botones) */
enum Button DrawButton(Axis x, Axis y, Boolean Status, enum Button btnId);
enum Button ButtonEvents(Boolean Status, enum Button btnId);
enum Button HoverButton(Axis x, Axis y);
/* Funcion Que Contiene el Marco de Trabajo */
void WorkSpace(void);
void UserInterface(void);

void ClosePolygon(Quantity nPoints, struct pointtype Points[]);

/** Cuerpo Principal **/
void main(void)
{
    Axis x = 320, y = 240, xClick = 0, yClick = 0;
    EventHandler Event = NONE;
    Boolean clickPress = false;

    struct pointtype Points[50];
    static Quantity nPoints = 0;

    InitGraph();

    _activeMovementControl = Mouse;  /* UserControl(); */
    
    UserInterface();
    
    (_activeMovementControl == Mouse) ? mver() : DrawCursor(x, y) ;

    do {
        /* Axis Movement, Event Handlers */
        if (_activeMovementControl == Keyboard)
        {
            Event = ReadKey();
            DrawCursor(x, y);
        } else {                          /* Mouse is Active */

            if (mclick() == CLICK)        /* If Click is Pressed */
            {
                if (!clickPress)          /* Si no ha presionado click */
                {
                    clickPress = true;    /* activate flag and capture click positions */
                    xClick = mxpos(1);
                    yClick = mypos(1);
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

        if (IsOutsideWorkArea(x, y))
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

                    gotoxy(1,nPoints + 1);
                    printf("%d %d", Points[nPoints].x, Points[nPoints].y);
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
    int temp[40] = {0};
    int higher = 0;
    int higherpos = 0;

    /* Ordenar de Ascendentemente los Puntos */
    for(i = 0; i < nPoints; i++)
        for(j = nPoints - 1; j > i; j--)
            if(Points[j - 1].x > Points[j].x)
            {
                tempa = Points[j - 1].x;
                tempb = Points[j - 1].y;

                Points[j - 1].x = Points[j].x;
                Points[j - 1].y = Points[j].y;

                Points[j].x = tempa;
                Points[j].y = tempb;
            }

    /* Obtener el Punto mas Alto en el eje Y */
    for(i = 0, higher = Points[0].y; i < nPoints; ++i)
        if(higher < Points[i].y)
        {
            higher = Points[i].y;
            higherpos = i;
        }

    /* Just printing Number to see Order :D */
    gotoxy(1,1);
    for (i = 0; i < nPoints ; i++)
        printf("%d %d\n", Points[i].x, Points[i].y);

    /* Asignar Punto mas alto como punto de inicio */
    temp[0] = Points[higherpos].x;
    temp[1] = Points[higherpos].y;

    /* Asignar los demas puntos tomando como referencia
       los puntos menores al punto x de inicio */
    for (i = 2, j = 0; j < nPoints; j++)
    {
        if (j == higherpos)
            j++;

        if (Points[j].x < temp[0])
        {
            temp[i] = Points[j].x;
            temp[i + 1] = Points[j].y;
            i+=2;
        }
    }

    /* Asignar los demas puntos tomando como referencia
       los puntos mayores al punto x de inicio */
    for (j = 0; j < nPoints; j++)
    {
        if (j == higherpos)
            j++;

        if (Points[j].x > temp[0])
        {
            temp[i] = Points[j].x;
            temp[i + 1] = Points[j].y;
            i+=2;
        }
    }
    
    /* Manually check if last lines intersect */
    printf("%d", temp[i - 1]);
    if (temp[i - 1] > 1 )
    {

    }

    temp[i] = Points[higherpos].x;
    temp[i + 1] = Points[higherpos].y;

    for (i = 0, j = 0; temp[i] != 0 ; i+=2, j++)
    {                            
        gotoxy(9,1 + j);
        printf("%d %d", temp[i], temp[i + 1]);
    }

    drawpoly(nPoints + 1, temp);
}