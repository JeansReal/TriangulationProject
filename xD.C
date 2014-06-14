***REMOVED***
***REMOVED***
/*              Jeans Real                  */
/*              Kristel Aburto              */
***REMOVED***
***REMOVED***

/* No Incluir Librerias Mas de 1 Vez */
#pragma once

/* Ficheros de Cabezera o Librerias */
#include <StdIo.h>      /* Funciones para salida de datos>> printf() */
#include <Conio.h>      /* Validacion de Control de Teclas>> kbhit() */
#include <Graphics.h>   /* Para Usar El Entorno Grafico de Borland */ 
#include <StdLib.h>     /* Comandos del sistema>> system() , abort() , exit() */
#include <Mouse.h>      /* Funcion para Mostrar Mouse y sus Eventos */

/* Libreria Personalizada */
#include "Apple/Macro.h"      /* Macros */
#include "Apple/Modo.h"       /* Modo Grafico */
#include "Apple/UserMov.h"    /* Funciones Movimiento */
#include "Apple/Screens.h"    /* Funciones de User Interface(UI) */

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

/** Cuerpo Principal **/
void main(void)
{
    EventHandler Event = NONE;
    Axis x = 320, y = 240;

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
            Event = (mclick() == CLICK) ? CLICK : NONE ;

            x = mxpos(1);
            y = mypos(1);
        }

        /* Si el Cursor esta Fuera del Area de Trabajo */
        if (IsOutsideWorkArea(x, y))
		   _hoverButton = HoverButton(x, y);

        switch (Event)
        {
            case UP:    y -= CanMoveUp(y)    break;
            case DOWN:  y += CanMoveDown(y)  break;
            case RIGHT: x += CanMoveRight(x) break;
            case LEFT:  x -= CanMoveLeft(x)  break;

            case ENTER: case CLICK:
                if (_hoverButton == NONE)       /* If No Button Is Selected */
                {
                    /* TODO Save Points */
                } else {                        /* If a Button Was Selected */
                    switch (_hoverButton)
                    {
                        case btnInputVector:    ButtonEvents(false, btnInputVector);   break;
                        case btnCloseVector:    ButtonEvents(false, btnCloseVector);   break;
                        case btnMonotone:       ButtonEvents(false, btnMonotone);      break;
                        case btnTrapezoidal:    ButtonEvents(false, btnTrapezoidal);   break;
                        case btnRestore:        ButtonEvents(false, btnRestore);       break;
                        case btnExit:           closegraph();       exit(0);
                    }

                    /* Realocating Cursor */
                    (_activeMovementControl == Keyboard) ? x = 320 , y = 240 : msituar(1, 320, 240) ;

                    _hoverButton = Event = NONE;
                }
            break;

            default:
                if (_activeMovementControl == Keyboard) /* Redraws Cursor For more UX! */
                    DrawCursor(x, y);
            break;
            
        }


    } while (mclick() != 2);
}