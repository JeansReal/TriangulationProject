/* Library that Contains Screens And Funtions for Event Handlers */

/* Function that Draws a Determinated Button: Return it Self */
enum Button DrawButton(Axis x, Axis y, Boolean Status, enum Button btnId)
{
    struct ButtonsStyle *btnStyle = NULL;

    /* Select Button Style Attributes */
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

    /* Sets Style for Button OutLine */
    FillStyle(Solido, btnStyle[Status].bkColor);
    LineStyle(Continua, Gruesa, btnStyle[Status].lineColor);

    /* Draws the Button Desing Shape */
    (btnId >= btnInputVector && btnId <= btnTrapezoidal) ? fillellipse(x, y, 75, 19) :
    (btnId == btnRestore) ? fillellipse(x, y, 32, 120) :
    (btnId == btnExit)    ? sector(x + 25, y + 40, 0, 180, 95, 70) : NONE ;
    
    /* Sets the Color of the Button Label */
    setcolor(btnStyle[Status].lblColor);

    /* Determinate Position of Label and Text Style According Button Shape */
    (btnId >= btnInputVector && btnId <= btnTrapezoidal) ? settextstyle(2, 0, 5) , y -= 8 , x -= 56 :
    (btnId == btnRestore) ? settextstyle(1, 1, 3) , y -= 33 :
    (btnId == btnExit)    ? settextstyle(1, 0, 8) , x -= 18 , y -= 44 : NONE ;

    /* Draws the Label of the Button */
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

/* Funtion That Draws a Button in Runtime: Returns Button Id */
enum Button ButtonEvents(Boolean status, enum Button btnId)
{
    if (btnId == NONE) /* Avoid Nesting */
        return NONE;

    if (_activeMovementControl == Mouse)
        mocultar();

    switch (btnId)
    {
        case btnInputVector:    DrawButton( 83,  22, status, btnInputVector);   break;
        case btnCloseVector:    DrawButton(240,  22, status, btnCloseVector);   break;
        case btnMonotone:       DrawButton(400,  22, status, btnMonotone);      break;
        case btnTrapezoidal:    DrawButton(560,  22, status, btnTrapezoidal);   break;
        case btnRestore:        DrawButton(  0, 230, status, btnRestore);       break;
        case btnExit:           DrawButton(600, 398, status, btnExit);          break;
    }

    if (_activeMovementControl == Mouse)
        mver();

    return btnId;
}
    
/* Function to Make Animated Buttons: Return the Actual Button Selected if Any */
enum Button HoverButton(Axis x, Axis y)
{
    Graph pixelColor = getpixel(x - 1, y - 1);  /* Get the Closest Pixel and not the Actual */
    enum Button static onHover = NONE, onChange = NONE;

    /* If The Cursor|Mouse is On a Button and this is Disabled, Revalidation on the same onHover: avoids redraw */
    if (IsInsideButton(x, y))
    {
        if ((x >= 8) && (x <= 635) && (y >= 3) && (y <= 41))                                    /* Command Buttons */   
            (x >=   8 && x <= 159 && onHover != btnInputVector) ? onHover = ButtonEvents(true, btnInputVector) :
            (x >= 166 && x <= 317 && onHover != btnCloseVector) ? onHover = ButtonEvents(true, btnCloseVector) :
            (x >= 324 && x <= 475 && onHover != btnMonotone)    ? onHover = ButtonEvents(true, btnMonotone)    :
            (x >= 482 && x <= 633 && onHover != btnTrapezoidal) ? onHover = ButtonEvents(true, btnTrapezoidal) : NONE ;
        else if ((x <= 32) && (y >= 111) && (y <= 350))                                         /* Left Button */
            (onHover != btnRestore)                             ? onHover = ButtonEvents(true, btnRestore)     : NONE ;
        else if ((x >= 530) && (y >= 368) && (y <= 440))                                        /* Right Button */
            if ((pixelColor != 15) && (pixelColor != 6) && (pixelColor != 0))       /* Is Outside WorkSpace Rectangle */
                (onHover != btnExit)                            ? onHover = ButtonEvents(true, btnExit)        : NONE ;
    } else
        onHover = NONE;

    /* If a Button Was Clicked or the Actual State has Changed */
    if (onHover != onChange)
    {
        if (_hoverButton == NONE) /* If there is no button selected there is no change */
            onChange = NONE;

        if (onChange != NONE)     /* If a button was selected redraw in new state */
            ButtonEvents(false, onChange);

        onChange = onHover;
    }

    return onHover;
}

/* Function that Contains the WorkSpace */
void WorkSpace(void)
{
    FillStyle(Solido, 15) , LineStyle(Continua, Gruesa, 6) ;

    moveto(520, 430) , lineto( 50, 430) ;
    lineto( 50,  50) , lineto(590,  50) ;
    lineto(590, 360) ;

    arc(590, 430, 90, 180, 70);

    floodfill(320, 240, 6);
}

/* Function that contains the Main Frame */
void MainFrame(void)
{
    /* Set Background */
    FillStyle(Solido, 7) , bar(0, 0, 640, 440) ;

    /* Draws New WorkSpace */
    WorkSpace();

    /* Status Bar */
    FillStyle(Solido, 8) , bar(0, 440, 640, 480) ;

    /* Draws All Buttons */
    DrawButton( 83,  22, false, btnInputVector);
    DrawButton(240,  22, false, btnCloseVector);
    DrawButton(400,  22, false, btnMonotone);
    DrawButton(560,  22, false, btnTrapezoidal);
    DrawButton(  0, 230, false, btnRestore);
    DrawButton(600, 398, false, btnExit);
}