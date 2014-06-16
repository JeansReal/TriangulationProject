***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***
***REMOVED***

/* Include Source Files Only Once in Compilation */
#pragma once

/* Header Files and Libraries */
#include <StdIo.h>      /* Functions for Data Output>> printf() */
#include <Conio.h>      /* Check Controls Keys>> kbhit() */
#include <Graphics.h>   /* Borland Graphic Environment */ 
#include <StdLib.h>     /* System Commands>> system() , abort() , exit() */
#include <Mouse.h>      /* Function to Show Mouse and Events>> mver() */
#include <String.h>     /* For Filling a Block of Memory>> memset() */

/* Helpers */
#include "Helper/Macro.h"   /* Macros and Constants */
#include "Helper/Mode.h"    /* Graphic Mode */
#include "Helper/UI.h"      /* (GUI) Funtions */
#include "Helper/UX.h"      /* User Control Movement (UX) */
#include "Helper/Trian.h"   /* Triangulation Methods */

/* Prototype Functions */
/* Functions For Graphic Mode */
void InitGraphicMode(void);
/* Functions that Brings to Life the GUI */
enum Button DrawButton(Axis x, Axis y, Boolean status, enum Button btnId);
enum Button DrawButtonEvent(Boolean status, enum Button btnId);
/* Funtion that Draw the Cursor */
void DrawCursor(Axis x, Axis y);
/* Functions that Draws the full GUI */
void DrawWorkSpace(void);
void DrawMainFrame(void);
/* Functions that Animate the Button */
enum Button HoverButton(Axis x, Axis y);
/* Functions for User Movement (Mouse, Cursor) */
enum UserMovementControl UserControl(void);
EventHandler ReadKey(void);
/* Functions Containing Triangulation Methods and Custom Helpers for Methods */
void ClosePolygon(Quantity nPoints, struct pointtype CloudOfPoints[]);

/** Main Body **/
void main(void)
{
    Axis x = 320, y = 240, xClick = 0, yClick = 0;
    EventHandler Event = NONE;
    Boolean clickPress = false;

    AxisStruct CloudOfPoints[50];
    Quantity nPoints = 0;

    InitGraphicMode();

    _activeMovementControl = Mouse;  /* UserControl(); */
    
    DrawMainFrame();
    
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

                    CloudOfPoints[nPoints].x = mxpos(1);
                    CloudOfPoints[nPoints].y = mypos(1);

                    setcolor(4);
                    settextstyle(0, 0, 1);
                    mocultar();

                    outtextxy(CloudOfPoints[nPoints].x, CloudOfPoints[nPoints].y, "x");
                    
                    mver();

                    gotoxy(1,nPoints + 1);
                    printf("%d %d", CloudOfPoints[nPoints].x, CloudOfPoints[nPoints].y);
                    nPoints++;

                } else {                        /* If a Button Was Selected */
                    switch (_hoverButton)
                    {
                        case btnInputPoints:    DrawButtonEvent(false, btnInputPoints);   break;
                        
                        case btnClosePolygon:
                            DrawButtonEvent(false, btnClosePolygon);
                            ClosePolygon(nPoints, CloudOfPoints);
                        break;

                        case btnMonotone:       DrawButtonEvent(false, btnMonotone);      break;
                        case btnTrapezoidal:    DrawButtonEvent(false, btnTrapezoidal);   break;
                        case btnRestore:        DrawWorkSpace(); DrawButtonEvent(false, btnRestore);       break;
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