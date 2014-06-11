/* Libreria que Contiene Funciones Graficas del Cursor y Mouse Modo XOR */

enum UserMovementControl UserControl(void)
{
    ControlEje x = mxpos(1), y = mypos(1);
    enum UserMovementControl SelectedControl = NONE;
    
    Relleno(Solido, 53) , setcolor(18) ;
    bar(350, 250, 725, 350) , rectangle(350, 250, 725, 350);

    setcolor(40) , settextstyle(2, 0, 5) ;
    outtextxy(365, 275, "Presione Cualquier Tecla Para Usar el Teclado");
    outtextxy(360, 305, "Realize Cualquier Movimiento Para Usar el Mouse");

    do {
        SelectedControl = ((x != mxpos(1)) || (y!= mypos(1)) || (mclick() == 1) || (mclick() == 2)) ? Mouse : (kbhit()) ? Keyboard : NONE ;
    } while (SelectedControl == NONE);

    return SelectedControl;
}

/* Cursor XOR */
void DrawCursor(ControlEje x, ControlEje y)
{
    Iteracion i = 0;
    
    static short x1, y1;
    Boolean static hacer = NONE;

    if (x1 != x)
    {
        x1 = x;
        hacer = True;
        setcolor(random(17));
        line (x, 10, y, 10);
    }
    if (y1 != y)
    {
        y1 = y;
        hacer = True;
        setcolor(random(17));
        line (x, 50, y, 50);
    }


    if (hacer)
    {   
        PixelXor(x, y);      /* Centro */
        for (i = 1; i <= 10; ++i)
        {
            PixelXor(x, y - i); /* Arriba */
            PixelXor(x + i, y); /* Derecha */
            PixelXor(x, y + i); /* Abajo */
            PixelXor(x - i, y); /* Izquierda */
        }
        hacer = False;
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