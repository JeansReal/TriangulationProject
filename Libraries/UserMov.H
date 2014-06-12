/* Libreria que Contiene Funciones Graficas del Cursor y Mouse Modo XOR */

enum UserMovementControl UserControl(void)
{
    Axis x = mxpos(1), y = mypos(1);
    enum UserMovementControl SelectedControl = NONE;
    
    FillStyle(Solido, 2) , setcolor(6) ;
    bar(150, 200, 525, 300) , rectangle(150, 200, 525, 300);

    setcolor(4) , settextstyle(2, 0, 5) ;
    outtextxy(165, 225, "Presione Cualquier Tecla Para Usar el Teclado");
    outtextxy(160, 255, "Realize Cualquier Movimiento Para Usar el Mouse");

    do {
        SelectedControl = ((x != mxpos(1)) || (y!= mypos(1)) || (mclick() == 1) || (mclick() == 2)) ? Mouse : (kbhit()) ? Keyboard : NONE ;
    } while (SelectedControl == NONE);

    return SelectedControl;
}

/* Cursor XOR */
void DrawCursor(Axis x, Axis y)
{
    Iteration i = 0;
    
    PixelXor(x, y);      /* Centro */

    for (i = 1; i <= 10; ++i)
    {
        PixelXor(x, y - i); /* Arriba */
        PixelXor(x + i, y); /* Derecha */
        PixelXor(x, y + i); /* Abajo */
        PixelXor(x - i, y); /* Izquierda */
    }
}