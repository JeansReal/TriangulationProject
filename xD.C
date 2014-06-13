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
/*#include <Dos.h>*/    /* Animaciones>> delay() , sleep() , sound() , nosound() */
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
/* Funcion Para Animar Controles(Botones) */
enum Button DrawButton(Axis x, Axis y, Boolean Status, enum Button btnId);
enum Button ButtonEvents(Boolean Active, enum Button btnId);
enum Button HoverButton(Axis x, Axis y);
/* Funcion Que Contiene el Marco de Trabajo */
void WorkSpace(void);
void UserInterface(void);

enum Boolean test(int x, int y, struct ButtonsStyle *btnStyle);

/** Cuerpo Principal **/
void main(void)
{
    EventHandler Event = NONE;
    Axis x = 320, y = 240;

    InitGraph();

    _activeMovementControl = Mouse;  /* UserControl(); */
    
    UserInterface();
    
    (_activeMovementControl == Mouse) ? mver() : false ;

    do {

        /* Axis Movement, Event Handlers */
        if (_activeMovementControl == Keyboard)
        {
            DrawCursor(x, y);
            Event = getch();
        } else {                          /* Mouse is Active */
            if (mclick() == CLICK)
                Event = CLICK;

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
                    break;

                if (_activeMovementControl == Keyboard)
                    DrawCursor(x, y);           /* Borra el Cursor  */
                
                switch (_hoverButton)
                {
                    case btnInputVector:    ButtonEvents(false, btnInputVector);      break;
                    case btnCloseVector:    ButtonEvents(false, btnCloseVector);      break;
                    case btnMonotone:       ButtonEvents(false, btnMonotone);         break;
                    case btnTrapezoidal:    ButtonEvents(false, btnTrapezoidal);      break;
                    case btnRestore:        ButtonEvents(false, btnRestore);          break;
                    case btnExit:           closegraph();       exit(0);
                }

                /* Realocating Cursor */
                if (_activeMovementControl == Keyboard)
                    x = 320 , y = 240 ;
                else
                    msituar(1, 320, 240);

                _hoverButton = Event =  NONE;
                
            break;
        }

    } while (mclick() != 2);
}