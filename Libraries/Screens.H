/* Libreria que Contiene Esqueletos de Pantallas y Funciones de Animacion */

/* Funcion de Reforzamiento para el Marco, lo Divide por Partes para poder animarlo! */
enum Button DrawButton(Axis x, Axis y, Boolean Status, enum Button btnId)
{
    struct ButtonsStyle *btnStyle = NULL;
    Graph btnLineWidth = 0, btnLineStyle = 0;

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

    (Status)  ? btnLineWidth = Fina   , btnLineStyle = Guiones  :
    (!Status) ? btnLineWidth = Gruesa , btnLineStyle = Continua : False ;

    /* Definiendo Estilo para Marco de Boton */
    FillStyle(Solido, btnStyle[Status].bkColor);
    LineStyle(btnLineStyle, btnLineWidth, btnStyle[Status].lineColor);

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
    switch (btnId)
    {
        case btnInputVector:    return DrawButton(100, 720, Status, btnInputVector);
        case btnCloseVector:    return DrawButton(100, 580, Status, btnCloseVector);
        case btnMonotone:       return DrawButton(100, 615, Status, btnMonotone);
        case btnTrapezoidal:    return DrawButton(100, 650, Status, btnTrapezoidal);
        
        case btnRestore:        return DrawButton(  3,  40, Status, btnRestore);
        case btnExit:           return DrawButton(  1,   1, Status, btnExit);
        
        default:                return NONE;
    }
}

/* Funcion que Realiza Animaciones de Botones */
enum Button HoverButton(Axis x, Axis y)
{
    enum Button static onHover = NONE, onChange = NONE;

    /* Si el Cursor esta sobre uno de los botones y el boton esta desactivado */
    /* Botones Superiores */
    if (x >= 100 && x <= 850 && y >= 720 && y <= 755)
        (x >= 100 && x <= 400 && onHover != btnInputVector) ? onHover = ButtonEvents(True, btnInputVector) :
        (x >= 450 && x <= 550 && onHover != btnCloseVector) ? onHover = ButtonEvents(True, btnCloseVector) :
        (x >= 600 && x <= 850 && onHover != btnMonotone)    ? onHover = ButtonEvents(True, btnMonotone)    :
        (x >= 850 && x <= 900 && onHover != btnTrapezoidal) ? onHover = ButtonEvents(True, btnTrapezoidal) :
        (x >  400 && x <  450 || x > 550 && x < 600)        ? onHover = NONE                               : NONE ;
    /* Boton Lateral Izquierdo */
    else if (x >= 3 && x <= 50 && y >= 40 && y <= 707)
        (onHover != btnRestore)                         ? onHover = ButtonEvents(True, btnRestore) : NONE ;
    /* Botones Lateral Derecho */
    else if (x >= 1 && x <= 1022 && y >= 1 && y <= 22)
        (x >= 1    && x <= 20   && onHover != btnExit)  ? onHover = ButtonEvents(True, btnExit)    :
        (x >  20   && x <  1002)                        ? onHover = NONE                           : NONE ;
    else
        onHover = NONE;

    /* Si se Selecciona otro Boton */
    if (_hoverButton == NONE)
        onChange = NONE;

    if (onHover != onChange)
    {
        ButtonEvents(False, onChange);
        onChange = onHover;
    }

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
    DrawButton( 83, 22, False, btnInputVector);
    DrawButton(240, 22, False, btnCloseVector);
    DrawButton(400, 22, False, btnMonotone);
    DrawButton(560, 22, False, btnTrapezoidal);

    /* Boton Restaurar */
    DrawButton(  0, 230, False, btnRestore);

    /* Exit */
    DrawButton(600, 398, False, btnExit);
}