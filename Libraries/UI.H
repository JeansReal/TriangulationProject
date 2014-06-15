/* Library that Contains Screens And Funtions in XOR Mode for the Cursor */

/* Function that Draws a Determinated Button: Return it Self */
enum Button DrawButton(Axis x, Axis y, Boolean status, enum Button btnId)
{
    struct ButtonsStyle *btnStyle = NULL;

    /* Select Button Style Attributes */
    switch (btnId)
    {
        case btnInputPoints:   case btnClosePolygon:
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

    /* Sets Style for Button OutLine */
    FillStyle(Solido, btnStyle[status].bkColor);
    LineStyle(Continua, Gruesa, btnStyle[status].lineColor);

    /* Draws the Button Desing Shape */
    (btnId >= btnInputPoints && btnId <= btnTrapezoidal) ? fillellipse(x, y, 75, 19) :
    (btnId == btnRestore) ? fillellipse(x, y, 32, 120) :
    (btnId == btnExit)    ? sector(x + 25, y + 40, 0, 180, 95, 70) : NONE ;
    
    /* Sets the Color of the Button Label */
    setcolor(btnStyle[status].lblColor);

    /* Determinate Position of Label and Text Style According Button Shape */
    (btnId >= btnInputPoints && btnId <= btnTrapezoidal) ? settextstyle(2, 0, 5) , y -= 8 , x -= 56 :
    (btnId == btnRestore) ? settextstyle(1, 1, 3) , y -= 33 :
    (btnId == btnExit)    ? settextstyle(1, 0, 8) , x -= 18 , y -= 44 : NONE ;

    /* Draws the Label of the Button */
    switch (btnId)
    {
        case btnInputPoints:    outtextxy(x, y, "Ingresar Puntos");    break;
        case btnClosePolygon:   outtextxy(x, y, "Cerrar Poligono");    break;
        case btnMonotone:       outtextxy(x, y, "Trian. Monotoma");    break;
        case btnTrapezoidal:    outtextxy(x, y, "Tri. Trapezoidal");   break;
        case btnRestore:        outtextxy(x, y, "E S C");              break;
        case btnExit:           outtextxy(x, y, "S");                  break;
    }

    return btnId;
}

/* Funtion That Draw a Button in Runtime: Returns Button Id */
enum Button DrawButtonEvent(Boolean status, enum Button btnId)
{
    if (btnId == NONE) /* Avoid Nesting */
        return NONE;

    if (_activeMovementControl == Mouse)
        mocultar();

    switch (btnId)
    {
        case btnInputPoints:    DrawButton( 83,  22, status, btnInputPoints);   break;
        case btnClosePolygon:   DrawButton(240,  22, status, btnClosePolygon);  break;
        case btnMonotone:       DrawButton(400,  22, status, btnMonotone);      break;
        case btnTrapezoidal:    DrawButton(560,  22, status, btnTrapezoidal);   break;
        case btnRestore:        DrawButton(  0, 230, status, btnRestore);       break;
        case btnExit:           DrawButton(600, 398, status, btnExit);          break;
    }

    if (_activeMovementControl == Mouse)
        mver();

    return btnId;
}

/* Funtion that Draws XOR Cursor */
void DrawCursor(Axis x, Axis y)
{
    Iteration i;
    
    PixelXor(x, y);      /* Center */

    for (i = 1; i <= 10; ++i)
    {
        PixelXor(x, y - i); /* Up */
        PixelXor(x + i, y); /* Right */
        PixelXor(x, y + i); /* Down */
        PixelXor(x - i, y); /* Left */
    }
}

/* Function that Contains the WorkSpace */
void DrawWorkSpace(void)
{
    FillStyle(Solido, 15) , LineStyle(Continua, Gruesa, 6) ;

    moveto(520, 430) , lineto( 50, 430) ;
    lineto( 50,  50) , lineto(590,  50) ;
    lineto(590, 360) ;

    arc(590, 430, 90, 180, 70);

    floodfill(320, 240, 6);
}

/* Function that contains the Main Frame */
void DrawMainFrame(void)
{
    /* Set Background */
    FillStyle(Solido, 7) , bar(0, 0, 640, 440) ;

    /* Draws New WorkSpace */
    DrawWorkSpace();

    /* Status Bar */
    FillStyle(Solido, 8) , bar(0, 440, 640, 480) ;

    /* Draws All Buttons */
    DrawButton( 83,  22, false, btnInputPoints);
    DrawButton(240,  22, false, btnClosePolygon);
    DrawButton(400,  22, false, btnMonotone);
    DrawButton(560,  22, false, btnTrapezoidal);
    DrawButton(  0, 230, false, btnRestore);
    DrawButton(600, 398, false, btnExit);
}