/* Library Containing Functions for Event Handlers and Movement Control for the User */

/* Function to Make Animated Buttons: Return the Actual Button Selected if Any */
enum Button HoverButton(Axis x, Axis y)
{
    Graph pixelColor = getpixel(x - 1, y - 1);  /* Get the Closest Pixel and not the Actual */
    enum Button static onHover = NONE, onChange = NONE;

    /* If The Cursor|Mouse is On a Button and this is Disabled, Revalidation on the same onHover: avoids redraw */
    if (IsInsideButton(x, y))
    {
        if ((x >= 8) && (x <= 635) && (y >= 3) && (y <= 41))                                    /* Command Buttons */   
            (x >=   8 && x <= 159 && onHover != btnInputPoints)  ? onHover = DrawButtonEvent(true, btnInputPoints) :
            (x >= 166 && x <= 317 && onHover != btnClosePolygon) ? onHover = DrawButtonEvent(true, btnClosePolygon) :
            (x >= 324 && x <= 475 && onHover != btnMonotone)     ? onHover = DrawButtonEvent(true, btnMonotone)    :
            (x >= 482 && x <= 633 && onHover != btnTrapezoidal)  ? onHover = DrawButtonEvent(true, btnTrapezoidal) : NONE ;
        else if ((x <= 32) && (y >= 111) && (y <= 350))                                         /* Left Button */
            (onHover != btnRestore)                              ? onHover = DrawButtonEvent(true, btnRestore)     : NONE ;
        else if ((x >= 530) && (y >= 368) && (y <= 440))                                        /* Right Button */
            if ((pixelColor != 15) && (pixelColor != 6) && (pixelColor != 0))       /* Is Outside WorkSpace Rectangle */
                (onHover != btnExit)                             ? onHover = DrawButtonEvent(true, btnExit)        : NONE ;
    } else
        onHover = NONE;

    /* If a Button Was Clicked or the Actual State has Changed */
    if (onHover != onChange)
    {
        if (_hoverButton == NONE) /* If there is no button selected there is no change */
            onChange = NONE;

        if (onChange != NONE)     /* If a button was selected redraw in new state */
            DrawButtonEvent(false, onChange);

        onChange = onHover;
    }

    return onHover;
}

/* Function that Allows User to Select Custom Movement Control: Return Selected Control */
enum UserMovementControl UserControl(void)
{
    Axis x = mxpos(1), y = mypos(1);
    enum UserMovementControl SelectedControl = NONE;
    
    FillStyle(Solido, 2) , setcolor(6) ;
    bar(150, 200, 525, 300) , rectangle(150, 200, 525, 300);

    setcolor(4) , settextstyle(2, 0, 5) ;
    outtextxy(165, 225, "Presione Cualquier Tecla Para Usar el Teclado");
    outtextxy(160, 255, "Realize Cualquier Movimiento Para Usar el Mouse");

    do {            /* While the User does not Perform any Action */
        SelectedControl = ((x != mxpos(1)) || (y!= mypos(1)) || (mclick() == 1) || (mclick() == 2)) ? Mouse : (kbhit()) ? Keyboard : NONE ;
    } while (SelectedControl == NONE);

    return SelectedControl;
}

/* Function that Waits an Input From the Keyboard: Return the Input */
EventHandler ReadKey(void)
{
    EventHandler Key;

    while((Key = getch()) != 0)  /* If Input Is Not NULL(Directional) then Check if it is some Custom Key */
        if(Key == ENTER)
            return Key;

    return getch();             /* If Input is NULL(Directional) then Returns this */
}