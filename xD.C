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

/** Cuerpo Principal **/
void main(void)
{
    EventHandler Evento = 0;
    Axis x = 140, y = 540;

    InitGraph();

    _activeMovementControl = Keyboard;  /* UserControl(); */
    
    UserInterface();

    (_activeMovementControl == Mouse) ? mver() : False ;

    do {
        if (_activeMovementControl == Keyboard)
            DrawCursor(x, y);

        /* Movimiento de Los Ejes, Manejador de Eventos */
        Evento = getch();
        switch (Evento)
        {
            case UP:    y -= CanMoveUp(y)    break;
            case DOWN:  y += CanMoveDown(y)  break;
            case RIGHT: x += CanMoveRight(x) break;
            case LEFT:  x -= CanMoveLeft(x)  break;

            case ENTER:
                DrawCursor(x, y);                   /* Borra el Cursor */
                
                if (_hoverButton != NONE)      		/* Si selecciona un boton */
                {
                    switch (_hoverButton)           /* Si Esta Seleccionando Algun Boton */
                    {
                        case btnInputVector: 	ButtonEvents(False, btnInputVector);      break;
                        case btnCloseVector:    ButtonEvents(False, btnCloseVector);      break;
                        case btnMonotone:       ButtonEvents(False, btnMonotone);         break;
                        case btnTrapezoidal:    ButtonEvents(False, btnTrapezoidal);      break;
                        case btnRestore:        ButtonEvents(False, btnRestore);          break;
                        case btnExit:           closegraph();       exit(0);
                    }


					x = 475 , y = 373 ;

                    /* Desactiva el Boton */
                    if (_hoverButton >= btnInputVector && _hoverButton <= btnTrapezoidal)
                        ButtonEvents(False, _hoverButton);

                    _hoverButton = NONE;
                }
            break;
        }


        /* Si el Cursor esta Fuera del Area de Trabajo */
        if (IsOutsideWorkArea(x, y))
		   _hoverButton = HoverButton(x, y);

    } while (mclick() != 1);
}