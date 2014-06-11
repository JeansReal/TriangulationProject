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

        if (kbhit())
            SelectedControl = Keyboard;

        if ((x != mxpos(1)) || (y!= mypos(1)) || (mclick() == 1) || (mclick() == 2))
            SelectedControl = Mouse;

    } while (SelectedControl == NONE);

    return SelectedControl;
}

/* Cursor XOR */
void DrawCursor(ControlEje x, ControlEje y)
{
    PixelXor(x, y);      /* Centro */
    PixelXor(x, y - 10); /* Arriba */
    PixelXor(x + 10, y); /* Derecha */
    PixelXor(x, y + 10); /* Abajo */
    PixelXor(x - 10, y); /* Izquierda */
}