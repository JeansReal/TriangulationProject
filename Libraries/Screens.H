/* Libreria que Contiene Esqueletos de Pantallas y Funciones de Animacion */

/* Funcion de Reforzamiento para el Marco, lo Divide por Partes para poder animarlo! */
enum Button DrawButton(Axis x, Axis y, Boolean Status, enum Button btnId)
{
    struct ButtonsStyle *btnStyle = NULL;

    /* Selecciona el Estilo del Boton */
    switch (btnId)
    {
        case btnInputVector:   case btnCloseVector:
        case btnMonotone:      case btnTrapezoidal:
            btnStyle = btnCommandsStyle;
        break;

        case btnRestore:
            btnStyle = btnRestoreStyle;
        break;

        case btnExit:
            btnStyle = btnExitStyle;
        break;
    }

    /* Definiendo Estilo para Marco de Boton */
    FillStyle(Solido, btnStyle[Status].bkColor);
    LineStyle(Continua, Gruesa, btnStyle[Status].lineColor);

    (btnId >= btnInputVector && btnId <= btnTrapezoidal) ? fillellipse(x, y, 75, 19) :
    (btnId == btnRestore) ? fillellipse(x, y, 32, 120) :
    (btnId == btnExit)    ? sector(x + 25, y + 40, 0, 180, 95, 70) : NONE ;
    
    /* Define Color de la Etiqueta del Boton */
    setcolor(btnStyle[Status].lblColor);

    /* Calcular Posicion de Etiqueta Segun Tipo de Boton */
    (btnId >= btnInputVector && btnId <= btnTrapezoidal) ? settextstyle(2, 0, 5) , y -= 8 , x -= 56 :
    (btnId == btnRestore) ? settextstyle(1, 1, 3) , y -= 33 :
    (btnId == btnExit)    ? settextstyle(1, 0, 8) , x -= 18 , y -= 44 : NONE ;

    switch (btnId)
    {
        case btnInputVector:    outtextxy(x, y, "Ingresar Puntos");    break;
        case btnCloseVector:    outtextxy(x, y, "Cerrar Poligono");    break;
        case btnMonotone:       outtextxy(x, y, "Trian. Monotoma");    break;
        case btnTrapezoidal:    outtextxy(x, y, "Tri. Trapezoidal");   break;
        case btnRestore:        outtextxy(x, y, "E S C");              break;
        case btnExit:           outtextxy(x, y, "S");                  break;
    }

    return btnId;
}

/* Funcion que Retorna el Evento del Boton */
enum Button ButtonEvents(Boolean Status, enum Button btnId)
{
    if (_activeMovementControl == Mouse)
        mocultar();

    switch (btnId)
    {
        case btnInputVector:    return DrawButton( 83,  22, Status, btnInputVector);
        case btnCloseVector:    return DrawButton(240,  22, Status, btnCloseVector);
        case btnMonotone:       return DrawButton(400,  22, Status, btnMonotone);
        case btnTrapezoidal:    return DrawButton(560,  22, Status, btnTrapezoidal);
        case btnRestore:        return DrawButton(  0, 230, Status, btnRestore);
        case btnExit:           return DrawButton(600, 398, Status, btnExit);

        default:                return NONE;
    }
}

enum Boolean test(int x, int y, struct ButtonsStyle *btnStyle)
{
    int bkPixel = getpixel(x - 1, y);

    if (bkPixel == btnStyle[0].bkColor || bkPixel == btnStyle[0].lineColor || bkPixel == btnStyle[0].lblColor)
    {
        gotoxy(1,1);
        printf("%d %d ", bkPixel, btnStyle[0].bkColor);
        return true;
    }

    return false;
}

/* Funcion que Realiza Animaciones de Botones */
enum Button HoverButton(Axis x, Axis y)
{
    enum Button static onHover = NONE, onChange = NONE;

    /* Si el Cursor esta sobre uno de los botones Superiores y el boton esta desactivado
       Revalidation on the same onHover Button avoids redraw on this and it's a optimized method */
    if ((x >= 8) && (x <= 635) && (y >= 3) && (y <= 41))    /* Botones Superiores */
        (x >=   8 && x <= 159 && onHover != btnInputVector && test(x,y,btnCommandsStyle)) ? onHover = ButtonEvents(true, btnInputVector) :
        (x >= 166 && x <= 317 && onHover != btnCloseVector && test(x,y,btnCommandsStyle)) ? onHover = ButtonEvents(true, btnCloseVector) :
        (x >= 324 && x <= 475 && onHover != btnMonotone)   && test(x,y,btnCommandsStyle)  ? onHover = ButtonEvents(true, btnMonotone)    :
        (x >= 482 && x <= 633 && onHover != btnTrapezoidal && test(x,y,btnCommandsStyle)) ? onHover = ButtonEvents(true, btnTrapezoidal) :
        (getpixel(x - 1, y) == 7) ? onHover = NONE : NONE ;
    else if (x >= 3 && x <= 50 && y >= 50 && y <= 300)  /* Boton Lateral Izquierdo */
        (onHover != btnRestore)                   ? onHover = ButtonEvents(true, btnRestore)     : NONE ;
    else if (x >= 592 && y >= 403 && y <= 440)          /* Boton Lateral Derecho */
        (onHover != btnExit)                      ? onHover = ButtonEvents(true, btnExit)        : NONE ;
    else
        onHover = NONE;

    /* Si se Selecciona otro Boton */
    if (_hoverButton == NONE)
        onChange = NONE;

    if (onHover != onChange)
    {
        ButtonEvents(false, onChange);
        onChange = onHover;
    }

    if (_activeMovementControl == Mouse)
        mver();

    return onHover;
}

void WorkSpace(void)
{
    FillStyle(Solido, 15) , LineStyle(Continua, Gruesa, 0) ;

    moveto(520, 430) , lineto( 50, 430) ;
    lineto( 50,  50) , lineto(590,  50) ;
    lineto(590, 360) ;

    arc(590, 430, 90, 180, 70);

    floodfill(320, 240, 0);
}

/* Funcion que Contiene el Marco Principal */
void UserInterface(void)
{
    /* Fondo */
    FillStyle(Solido, 7) , bar(0, 0, 640, 440) ;

    WorkSpace();

    /* Status Bar */
    FillStyle(Solido, 8) , bar(0, 440, 640, 480) ;

	/* Botones de Comandos de Triangulacion */
    DrawButton( 83, 22, false, btnInputVector);
    DrawButton(240, 22, false, btnCloseVector);
    DrawButton(400, 22, false, btnMonotone);
    DrawButton(560, 22, false, btnTrapezoidal);

    /* Boton Restaurar */
    DrawButton(  0, 230, false, btnRestore);

    /* Exit */
    DrawButton(600, 398, false, btnExit);
}