/* Libreria que Contiene Funciones Graficas del Cursor y Mouse Modo XOR */

enum UserMovementControl UserControl(void)
{
    ControlEje x = mxpos(1), y = mypos(1);
    enum UserMovementControl SelectedControl = NONE;
    
    Relleno(Solido, 2) , setcolor(6) ;
    bar(150, 200, 525, 300) , rectangle(150, 200, 525, 300);

    setcolor(4) , settextstyle(2, 0, 5) ;
    outtextxy(165, 225, "Presione Cualquier Tecla Para Usar el Teclado");
    outtextxy(160, 255, "Realize Cualquier Movimiento Para Usar el Mouse");

    do {
        SelectedControl = ((x != mxpos(1)) || (y!= mypos(1)) || (mclick() == 1) || (mclick() == 2)) ? Mouse : (kbhit()) ? Keyboard : NONE ;
    } while (SelectedControl == NONE);

    exit(1);

    return SelectedControl;
}

/* Cursor XOR */
void DrawCursor(ControlEje x, ControlEje y)
{
    Iteracion i = 0;
    
    PixelXor(x, y);      /* Centro */

    for (i = 1; i <= 10; ++i)
    {
        PixelXor(x, y - i); /* Arriba */
        PixelXor(x + i, y); /* Derecha */
        PixelXor(x, y + i); /* Abajo */
        PixelXor(x - i, y); /* Izquierda */
    }

}

/* Verifica si Esta Fuera del Marco de Trabajo */
Boolean IsOutsideWorkArea(ControlEje x, ControlEje y)
{
    if (x > 55 && x < 895 && y > 41 && y < 707)
        return False;
    else
        return True;
}

/* Verifica si Puede Moverse a los extremos del Area de Trabajo */
Boolean CanMoveLeft(ControlEje x)
{
    if (x > Limit[_activeLimit].x1)
        return True;
    else
        return False;
}

Boolean CanMoveRight(ControlEje x)
{
    if (x < Limit[_activeLimit].x2)
        return True;
    else
        return False;
}

Boolean CanMoveUp(ControlEje y)
{
    if (y > Limit[_activeLimit].y1)
        return True;
    else
        return False;
}

Boolean CanMoveDown(ControlEje y)
{
    if (y < Limit[_activeLimit].y2)
        return True;
    else
        return False;
}