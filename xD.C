/* Include Source Files Only Once in Compilation */
#pragma once

/* Header Files and Libraries */
#include <StdIo.h>      /* Functions for Data Output>> printf() */
#include <Conio.h>      /* Check Controls Keys>> kbhit() */
#include <Graphics.h>   /* Borland Graphic Environment */ 
#include <StdLib.h>     /* System Commands>> system() , abort() , exit() */
#include <Mouse.h>      /* Function to Show Mouse and Events>> mver() */
#include <String.h>     /* For Filling a Block of Memory>> memset() */
#include <Math.h>       /* TODO Comment */
#include <Dos.h>        /* TODO Comment */

/* Helpers */
#include "Helper/Macro.h"   /* Macros and Constants */
#include "Helper/Mode.h"    /* Graphic Mode */
#include "Helper/UI.h"      /* (GUI) Funtions */
#include "Helper/UX.h"      /* User Control Movement (UX) */
#include "Helper/Trian.h"   /* Triangulation Methods and Helpers */

/* Prototype Functions */
/* Functions For Graphic Mode */
void InitGraphicMode(void);
/* Functions that Brings to Life the GUI */
enum Button DrawButton(Axis x, Axis y, Boolean status, enum Button btnId);
enum Button DrawButtonEvent(Boolean status, enum Button btnId);
/* Funtion that Draw the Cursor */
void DrawCursor(Axis x, Axis y);
/* Functions that Draws the Full GUI */
void DrawWorkSpace(void);
void DrawMainFrame(void);
/* Functions that Animate the Button */
enum Button HoverButton(Axis x, Axis y);
/* Functions for User Movement (Mouse, Cursor) */
enum UserMovementControl UserControl(void);
EventHandler ReadKey(void);
/* Functions Containing Triangulation Methods and Custom Helpers for Methods */
/* Helpers */
/* Error Message */
void OnMemoryError(void);
/* Memory Allocator for Array of Points of a Polygon */
Graph *ArrayMemoryConstructor(Quantity requestedPoints);
/* Memory Allocator for Structure of a Point */
AxisStruct *StructMemoryConstructor(Quantity requestedPoints);
/* Destroy the Memory Allocated for an Array */
void ArrayMemoryDestructor(Graph PointsCloudMemory[]);
/* Destroy Memory Allocated for a Structure of Points */
void StructMemoryDestructor(AxisStruct *PointsMemory);
/* Function that Create A Polygon using a Cloud of Points */
AxisStruct *CreatePolygon(Quantity nPoints, AxisStruct CloudOfPoints[]);
/* Function that Triangulate a Polygon using Monotonal Algorithm */
void MonotoneTriangulation();
/* Calculates Area Inside a Triangle */
long Area2(AxisStruct *A, AxisStruct *B, AxisStruct *C);
Boolean InCone(Iteration i, Iteration j, Quantity nPoints, AxisStruct PolygonPoints[]);
Boolean IntersectProp(AxisStruct *A, AxisStruct *B, AxisStruct *C, AxisStruct *D);
Boolean Between(AxisStruct *A, AxisStruct *B, AxisStruct *C);
Boolean Intersect(AxisStruct *A, AxisStruct *B, AxisStruct *C, AxisStruct *D);
Boolean Diagonalie(Iteration i, Iteration j, Quantity nPoints, AxisStruct PolygonPoints[]);
void ClipEar(Iteration i, Quantity nPoints, AxisStruct PolygonPoints[]);
/* Function that Descomposes an polygon into monotones polygons */
void MonotoneTriangulation(Quantity nPoints, AxisStruct PolygonPoints[]);

void MsgBox(Axis x, Axis y, const String Message, Color BackgroundColor, Color TextColor)
{    
    Axis xLeft  = x - textheight(Message); /* strlen() in Text Mode */
    Axis xRight = x + ((textheight(Message) * 3) * 640) / 100;

    setcolor(TextColor);
    FillStyle(Solido, BackgroundColor);
    bar(xLeft, y - 20, xRight, y + 20);

    outtextxy(x, y, Message);
}

/** Main Body **/
void main(void)
{
    Axis x = 320, y = 240, xClick = 0, yClick = 0;
    EventHandler Event = NONE;
    Boolean clickPress = false;

    AxisStruct *Points = StructMemoryConstructor(100);
    static Quantity nPoints = 0;

    InitGraphicMode();

    _activeMovementControl = UserControl();
    
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

                    if (nPoints >= 100)
                    {
                        /* Add Some Workers */
                    }

                    if (_activeMovementControl == Mouse)
                    {
                        Points[nPoints].x = mxpos(1);
                        Points[nPoints].y = mypos(1);
                    } else {
                        Points[nPoints].x = x;
                        Points[nPoints].y = y;
                    }

                    mocultar();

                    FillStyle(Solido, 11);
                    LineStyle(Continua, Fina, 12);
                    fillellipse(Points[nPoints].x, Points[nPoints].y, 3, 3);

                    mver();

                    nPoints++; /* Move in the Index */
                } else {                        /* If a Button Was Selected */
                    switch (_hoverButton)
                    {
                        case btnInputPoints:
                            DrawButtonEvent(false, btnInputPoints);
                        break;
                        
                        case btnClosePolygon:
                            DrawButtonEvent(false, btnClosePolygon);
                            Points = CreatePolygon(nPoints, Points);
                        break;

                        case btnMonotone:
                            DrawButtonEvent(false, btnMonotone);
                            MonotoneTriangulation(nPoints, Points);
                        break;

                        case btnTrapezoidal:
                            DrawButtonEvent(false, btnTrapezoidal);
                            /* Throws some Exception :( */
                        break;

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