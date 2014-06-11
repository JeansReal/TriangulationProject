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
#include <Dos.h>        /* Animaciones>> delay() , sleep() , sound() , nosound() */
/*#include <Alloc.h>      /* Asignacion de Memoria Dinamica>> malloc() , free() */
#include <StdLib.h>     /* Comandos del sistema>> system() , abort() , exit() */
#include <Math.h>       /* Funciones para Calculos de Figuras Geometricas>> DrawEllipse() */
#include <String.h>     /* Funcion Para Llenar Bloque de Memoria>> memset() */
#include <mouse.h>      /* Funcion para Mostrar Mouse y sus Eventos */

/* Libreria Personalizada */
#include "Apple/Macro.h"      /* Macros */
#include "Apple/Modo.h"       /* Modo Grafico */
#include "Apple/XorFunc.h"    /* Funciones XOR */
#include "Apple/Screens.h"

/* Funciones Prototipo */

/* Funciones Para El Modo Grafico */
void InitGraph(void);
int huge HighLevelXGA(void);
/* Funciones de la Interfaz Grafica */

/* Funcion para Hablitar el Movimiento del Cursor */
Boolean IsOutsideWorkArea(ControlEje x, ControlEje y);
Boolean CanMoveLeft(ControlEje x);
Boolean CanMoveRight(ControlEje x);
Boolean CanMoveUp(ControlEje y);
Boolean CanMoveDown(ControlEje y);
/* Funcion Para Animar Controles(Botones) */
enum Button DrawButton(ControlEje x, ControlEje y, Boolean Status, enum Button btnId);
enum Button ButtonEvents(Boolean Active, enum Button btnId);
enum Button HoverButton(ControlEje x, ControlEje y);

/* Funcion Que Contiene el Marco de Trabajo */
void WorkSpace(void);

/* Funciones Para Figuras en Modo XOR */
void DrawCursor(ControlEje x, ControlEje y);

/** Cuerpo Principal **/
void main(void)
{
    Direccional Tecla = 0;
    ControlEje x = 140, y = 540;

    InitGraph();

    WorkSpace();    

	do {
        DrawCursor(x, y);

        /* Movimiento de Los Ejes, Manejador de Eventos */
        Tecla = getch();
        switch (Tecla)
        {
            case ARRIBA:    y   -= (CanMoveUp(y))    ? 5 : False ;                break;
            case ABAJO:     y   += (CanMoveDown(y))  ? 5 : False ;                break;
            case DERECHA:   x   += (CanMoveRight(x)) ? 5 : False ;                break;
            case IZQUIERDA: x   -= (CanMoveLeft(x))  ? 5 : False ;                break;

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

                    /* Desactiva el Boton y Activa La Figura si alguna fue Seleccionada */
                    /*if (_hoverButton >= btnLine && _hoverButton <= btnPolygon)*/
                        /*_activeShape = ButtonEvents(False, _hoverButton);*/

                    _hoverButton = NONE;
                }
            break;

            case ESC:   exit(0);
        }


        /* Si el Cursor esta Fuera del Area de Trabajo o El Cursor esta en un SubMenu */
        if (IsOutsideWorkArea(x, y))
		   _hoverButton = HoverButton(x, y);

    } while (True);
}