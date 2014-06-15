/* Library Containing Functions in XOR Mode for the Cursor and Movement Control for the User */

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

/* Function that Waits an Input From the Keyboard: Return the Input */
EventHandler ReadKey(void)
{
    EventHandler Key;

    while((Key = getch()) != 0)  /* If Input Is Not NULL(Directional) then Check if it is some Custom Key */
        if(Key == ENTER)
            return Key;

    return getch();             /* If Input is NULL(Directional) then Returns this */
}